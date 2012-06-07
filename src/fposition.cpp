/***************************************************************************
                             fposition.cpp
                             -------------
    begin                : sam nov 2 2002
    copyright            : (C) 1992-2008 by Fabian José Padilla
    email                : fjp@evenja.org
 ***************************************************************************/

/******************************************************************************
 *   Copyright (C) 1992-2012 Fabian José Padilla                                   *
 *                                                                            *
 *  This program is free software: you can redistribute it and/or modify      *
 *  it under the terms of the GNU Affero General Public License as            *
 *  published by the Free Software Foundation, either version 3 of the        *
 *  License, or (at your option) any later version.                           *
 *                                                                            *
 *  This program is distributed in the hope that it will be useful,           *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU Affero General Public License for more details.                       *
 *                                                                            *
 *  You should have received a copy of the GNU Affero General Public License  *
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.     *
 ******************************************************************************/

#include <string.h>

#include "returncodes.h"
#include "evenjastrings.h"
#include "fposition.h"

namespace evenja {

Fposition::Fposition() : FstringHash()
{
  nbLevel = 0;
  positionActived = false;
  resetPosition();
}

Fposition::~Fposition()
{
  resetPosition();
}

/** \return No return value. */
void Fposition::resetPosition()
{
  if( positionActived)
  {
    computer.setString( TXT_NULL);
  
    for( long i = 0; i < nbLevel; i++)
      delete ( FstringHash*) getRoom( i);

    nbLevel = 0;
  
    port.setString( TXT_NULL);
    action.setString( TXT_NULL);
    unitWaitTime = ACT_WAIT_NOTHING;
    waitTime = 0;

    positionActived = false;
  }
}

/** \param[in] positionString Url like position, example : "www.revena.com/room1/door2:destination1Data". 
  \retval RET_OK Position OK. 
  \retval RET_STRING2LONG Position string to long. */
long Fposition::setPosition( char* positionString)
{
  if( strlen( positionString) < MAX_STRING)
  {
    char bufferWork[ MAX_STRING];
    char bufferRooms[ MAX_STRING];
    strcpy( bufferWork, positionString);

    resetPosition();

    nbLevel = 0;      // reset level counter

    setString( positionString);    // set the hash for the full name position string 

    char* ptrWorkStart = bufferWork;
    char* ptrWorkEnd = strchr( ptrWorkStart, TREE_SEPARATOR);
    char* ptr;
    if( ptrWorkEnd)  // if slash then may be a computer and differents rooms
    {
      *ptrWorkEnd = 0;

      ptr = strchr( ptrWorkStart, '.');
      if( ptr) // Is it a computer in the routing process ?
      { // yes then take the name of the computer ex.: www.revena.com
        computer.setString( ptrWorkStart);

        ptrWorkStart = ptrWorkEnd;
        ptrWorkStart++;
        ptrWorkEnd = strchr( ptrWorkStart, TREE_SEPARATOR);
      }

// import the room levels
      *bufferRooms = 0; // reset the buffer pointer
      while( ptrWorkEnd) // Until nothing is found do...
      {
        *ptrWorkEnd = 0;

        rooms.add( new FstringHash());   // create the name

        if( nbLevel)                    // if not the only level (0) then add slash at the end of the previous room
          strcat( bufferRooms, "/");
        strcat( bufferRooms, ptrWorkStart);       // Concat all the rooms routing

        ( ( FstringHash*) rooms.get( nbLevel))->setString( bufferRooms);
        nbLevel++;

        ptrWorkStart = ptrWorkEnd;
        ptrWorkStart++;
        ptrWorkEnd = strchr( ptrWorkStart, '/');        
      }
    }

// After the rooms there is a port and may be an action.
    ptr = strchr( ptrWorkStart, ':');  // Is it a specific action ?
    if( ptr) // yes then take the port and after the action
    {
      *ptr = 0;
      port.setString( ptrWorkStart);

      ptrWorkStart = ++ptr;

      ptr = strchr( ptrWorkStart, ','); // it is a wait time ?
      if( ptr) // yes, then take the time and after take the unit
      {
        *ptr = 0;
        action.setString( ptrWorkStart);

        ptr++;
        waitTime = 0;
        while( *ptr >= '0' && *ptr <= '9')
        {
          waitTime = ( waitTime * 10) + ( *ptr - '0');
          ptr++;
        }

        unitWaitTime = *ptr;  // Take the unit of the wait time
      }
      else
      {
        action.setString( ptrWorkStart);
        waitTime = 0;
        unitWaitTime = ACT_WAIT_NOTHING;
      }
    }
    else // No information, then take only the port and set action to normal action
    {
      port.setString( ptrWorkStart);
      action.setString( ACT_NORMAL);
      waitTime = 0;
      unitWaitTime = ACT_WAIT_NOTHING;
    }

    positionActived = true;

    return RET_OK;
  }
  else
    return RET_STRING2LONG;
}

/** \return If the evenData need to go to another computer return the computer name, otherwise the FstringHash returned will contain NULL string. */
FstringHash* Fposition::getComputer()
{
  return &computer;
}

/** \param[in] level Level of the tree of rooms.
  \retval NULL This level not exist.
  \retval any_FstringHash The room name for destination or source at a specific level. */
FstringHash* Fposition::getRoom( long level)
{
  if( level < nbLevel)    // If nbLevel smaller than level asked for then don't answer.
    return ( FstringHash*) rooms.get( level);
  else
    return NULL;
}

/** \return Number of levels in the rooms tree. */
long Fposition::getNbLevel()
{
  return nbLevel;
}

/** \return The port of the position (source or destination). This means an evenDoor or a evenBoard. */
FstringHash* Fposition::getPort()
{
  return &port;
}

/** \return The action of the position (source or destination). */
FstringHash* Fposition::getAction()
{
  return &action;
}

/** \return The amount of waiting time (unit time is another get function) */
long Fposition::getWaitTime()
{
  return waitTime;
}

/** \return The unit time y,n,d,h,m,s or x */
char Fposition::getUnitWaitTime()
{
  return unitWaitTime; 
}

/** \param[in] pos Original Fposition to copy all informations from.
  \return No return value. */
void Fposition::copyFrom( Fposition* pos)
{
  resetPosition();

  computer.copyFrom( pos->getComputer());

  for( long i = 0; i < pos->getNbLevel(); i++)
  {
    rooms.add( new FstringHash());   // create the name
    ( ( FstringHash*) rooms.get( nbLevel))->copyFrom( pos->getRoom( nbLevel));
    nbLevel++;
  }

  port.copyFrom( pos->getPort());
  
  action.copyFrom( pos->getAction());

  waitTime = pos->getWaitTime();

  unitWaitTime = pos->getUnitWaitTime();
  
  positionActived = true;        
}

}   // namespace evenja
