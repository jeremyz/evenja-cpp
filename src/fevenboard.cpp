/***************************************************************************
                             fevenboard.cpp 
                             --------------
    begin                : sam nov 2 2002
    copyright            : (C) 1992-2008 by Fabian José Padilla
    email                : fjp@evenja.org
 ***************************************************************************/

/******************************************************************************
 *   Copyright (C) 2012 Fabian José Padilla                                   *
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

#include "fevenboard.h"

#include "returncodes.h"
#include "globalvars.h"

namespace evenja {

FevenBoard::FevenBoard() : FportListHash() {}

FevenBoard::~FevenBoard() {}

/** \param[in] evenData FevenData to make an action with.
  \retval RET_OK No problemo. Now allways OK ;). */
long FevenBoard::receive_evenData( FevenData* evenData)
{
  FstringHash* action = evenData->getCurrentDestination()->getAction();
  
  // A single action here (this is a bug), then goto next destination or error
  if( action->equals( &gvActionOneDataDestination))
  {
    if( evenData->selectNextDestination() != RET_OK)
      evenData->setPortAction( ACT_ERROR);
  }
  else // Not a single data then merge with may be an existing data a go
  {
    FevenData * dataPresent = ( FevenData*) listHash.addOrRemove( evenData);

    if( dataPresent) // Check if another evenData was waiting
    { // Yes then merge evenData and dataPresent
      //
      if( action->equals( &gvActionFollowDestination))
      {
        FevenData* provData = dataPresent;
        dataPresent = evenData;
        evenData = provData;
      }

      evenData->addEvenDataB( dataPresent);

      if( evenData->selectNextDestination() != RET_OK)
        evenData->setPortAction( ACT_ERROR);

      // Then send the evenData
      sendEvenData( evenData);
    }
    else
    { // No other evenData waiting then check if it is a wait
      if( action->equals( &gvActionWait))
      {
        //TODO IMPLEMENTATION OF THE WAIT
      }
    }
  }

  return RET_OK;
}

}   // namespace evenja
