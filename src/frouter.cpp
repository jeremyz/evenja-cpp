/***************************************************************************
                             frouter.cpp
                             -----------
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

#include "frouter.h"
#include "fevenboard.h"
#include "fevendoor.h"
#include "fevenprg.h"
#include "evenjastrings.h"
#include "returncodes.h"
#include "globalvars.h"

// -------------------------------------------------
// IMPORT YOUR INCLUDES HEADERS
// -------------------------------------------------

// -------------------------------------------------

namespace evenja {

// --------------------------------------------------------------------------
Frouter::Frouter() : FportListHash() {}

Frouter::~Frouter() {}

#define IMPORT_PORTS(AAA,BBB,CCC)                                 \
    if( !Find( AAA, false))                                       \
    {                                                             \
      do {                                                        \
        pushCurrent();                                            \
        getClassInfos( &classInfo);                               \
        if( ( !strcasecmp( classInfo.type.getString(), BBB))      \
            || ( !classInfo.type.getLen() && !*BBB))              \
        {                                                         \
          Fport *childRoom = new CCC();                           \
          if( classInfo.conf.getLen())                            \
            childRoom->start( this, classInfo.conf.getString());  \
          else                                                    \
            childRoom->start( this, current);                     \
          Fport* ptr = ( Fport*) listHash.addOrGet( childRoom);   \
          if( ptr)                                                \
          {                                                       \
            delete childRoom;                                     \
            return RET_PORTEXIST;                                 \
          }                                                       \
        }                                                         \
        popCurrent();                                             \
      }while( FindNext( AAA, false) == RET_OK);                   \
    }

#define IMPORTS_DATAS(AAA,BBB,CCC)                                \
    if( !Find( AAA, false))                                       \
    {                                                             \
      do {                                                        \
        pushCurrent();                                            \
        getClassInfos( &classInfo);                               \
        if( ( !strcasecmp( classInfo.type.getString(), BBB))			\
            || ( !classInfo.type.getLen() && !*BBB))              \
        {                                                         \
          FevenData *evenData = ( FevenData*) new CCC();          \
					setFreeEvenData( evenData);															\
				}                                                         \
        popCurrent();                                             \
      }while( FindNext( AAA, false) == RET_OK);                   \
    }

/** \param[out] classInfo Return the configuration information of the class.
  \retval RET_OK No problemo.
  \retval RET_NOTEXIST No node with information found. */
long Frouter::getClassInfos( FclassInfos* classInfo)
{
  long ret = RET_OK;
	
  pushCurrent();
  if( gotoChildren() == RET_OK)
  {
    if( Find( XML_CLASS) == RET_OK)
			classInfo->type.setString( getNodeContent());
		else
			classInfo->type.setString( ( char*)"");			

    if( Find( XML_CONF) == RET_OK)
			classInfo->conf.setString( getNodeContent());
		else
			classInfo->conf.setString( ( char*)"");

    if( Find( XML_LIB) == RET_OK)
			classInfo->lib.setString( getNodeContent());
		else
			classInfo->lib.setString( ( char*)"");

    if( Find( XML_DEBUG) == RET_OK)
			classInfo->debug.setString( getNodeContent());
		else
			classInfo->debug.setString( ( char*)"");
  }
  else
    ret = RET_NOTEXIST;

  popCurrent();

  return ret;
}

/** \param[out] conditionLink Return the configuration information of the conditional link.
	 \retval RET_OK No problemo.
	 \retval RET_NOTEXIST No node with information found. */
long Frouter::getLinkInfos( FconditionLink* conditionLink)
{
  long ret = RET_OK;

  pushCurrent();
  if( gotoChildren() == RET_OK)
  {
    if( Find( XML_LNKSOURCE) == RET_OK)
			conditionLink->source.setString( getNodeContent());
		else
			conditionLink->source.setString( ( char*)"");

    if( Find( XML_LNKTYPE) == RET_OK)
			conditionLink->typeFields.setString( getNodeContent());
		else
			conditionLink->typeFields.setString( ( char*)"");
		
    if( Find( XML_LNKVALUE) == RET_OK)
			conditionLink->value.setString( getNodeContent());
		else
			conditionLink->value.setString( ( char*)"");
		
    if( Find( XML_LNKFIELDS) == RET_OK)
				conditionLink->fields.setString( getNodeContent());
		else
			conditionLink->fields.setString( ( char*)"");

    if( Find( XML_LNKDEST) == RET_OK)
			conditionLink->destination.setString( getNodeContent());
		else
			conditionLink->destination.setString( ( char*)"");
  }
  else
    ret = RET_NOTEXIST;

  popCurrent();

  return ret;
}


/** \retval RET_OK No problemo, room created.
  \retval RET_NOINFOS No configuration informations to process. */
long Frouter::createRoom()
{
  FclassInfos classInfo;
  FconditionLink conditionLink;
  FstringHash strH;

  Fport* port;

  resetCurrent();
  if( !gotoChildren())
  {
// --------------------------------------------------
// IMPORT PORTS
// --------------------------------------------------
    IMPORT_PORTS( XML_ROOM, "", Frouter)
    IMPORT_PORTS( XML_BOARD, "", FevenBoard)

// --------------------------------------------------
// IMPORTS a default evenData
// --------------------------------------------------
    setFreeEvenData( new FevenData());							

// --------------------------------------------------
// IMPORT DATAS to enable an easy creation of evenData instances
// --------------------------------------------------

// --------------------------------------------------
// IMPORT YOUR OWN PORTS
// --------------------------------------------------

		
// --------------------------------------------------
// --------------------------------------------------

// --------------------------------------------------
// IMPORT LINK VALUES BETWEEN evenData, evenDoor AND ports
// --------------------------------------------------
    if( !Find( XML_LNK, false))
    {
      do {
        pushCurrent();
        getLinkInfos( &conditionLink);
        if( conditionLink.source.getLen())
        {
          strH.setString( conditionLink.source.getString());
          port = ( Fport*) listHash.Search( &strH);
          if( port)
          {
            FevenData* data = getFreeEvenData();

            // Set the value to transmit to the door
            data->setData( XML_LNKSOURCE, conditionLink.source.getString());
            data->setData( XML_LNKTYPE, conditionLink.typeFields.getString());
            data->setData( XML_LNKVALUE, conditionLink.value.getString());
            data->setData( XML_LNKFIELDS, conditionLink.fields.getString());
            data->setData( XML_LNKDEST, conditionLink.destination.getString());

            // Set the SYSTEM action
            data->setPortAction( ACT_SYS_ADDDEST, conditionLink.source.getString());

            // Send to the evenDoor
            sendEvenDataSys( data, port);
          }
        }
        popCurrent();
      }while( FindNext( XML_LNK, false) == RET_OK);
    }
    return RET_OK;
  }
  else
    return RET_NOINFOS;
}

// ------------------- MACROS FOR start methods
#define STARTPORT( AAA)											 \
  long ret = Fport::start( parentPort, AAA); \
  if( ret)																	 \
    return ret;															 \
  else																			 \
    return createRoom();

/** \param[in] parentPort Set the parent of this port.
	\param[in] fileNameString Filename in XML format to load a XML doc tree.
	\retval RET_OK No problemo.
	\retval RET_FILENAME2LONG Path and filename are longer than the MAX_PATH.
	\retval RET_CANNOTACCESS Error accessing the XML tree.
	\retval RET_NONODESELECTED Nothing found, content free.
	\retval RET_NONAME No name field in the first node.
	\retval RET_NOTEXIST First node not exist.
  \retval RET_NOINFOS No configuration informations to process. */
long Frouter::start( Fport *parentPort, char *fileNameString)
{
  STARTPORT( fileNameString)
}

/** \param[in] parentPort Set the parent of this port.
	\param[in] node Start a new XML tree with a node of another XML tree. The new XML tree start at the branch with this node parameter.
	\retval RET_OK No problemo.
	\retval RET_NONODESELECTED Nothing found, content free.
	\retval RET_NONAME No name field in the xml tree.
	\retval RET_NOTEXIST First node not exist.
  \retval RET_NOINFOS No configuration informations to process.*/
long Frouter::start( Fport *parentPort, void *node)
{
  STARTPORT( node)
}

/** \param[in] evenData FevenData to route to another port.
	\retval RET_OK No problemo. Now allways OK ;). */
long Frouter::receive_evenData( FevenData* evenData)
{
  Fport* port;

  port = ( Fport*) listHash.Search( evenData->getCurrentDestination()->getPort());
  if( port != RET_OK)
  {   // ... then send to it the evenData
    // Now it send the evenData by sndMsg, but normally this will change after the realeas of V3.0
//    sendEvenData( evenData, port);
//    return RET_OK;
    // ...this will work well too, but it is another principle
    return ( ( Fport*) port)->justDoIt( evenData);
  }
  else
  {   // ... ERREUR NO DESTINATION, then go to error
    evenData->setPortAction( ACT_ERROR);
    return RET_KO;
  }
}

/** \param[in] evenData FevenData to be just worked.
  \retval RET_OK No problemo. */
long Frouter::justDoIt( FevenData* evenData)
{
// First check if the evenData as ended is work.
  if( evenData->getCurrentDestination()->getAction()->equals( &gvActionEnd)
    || evenData->getCurrentDestination()->getAction()->equals( &gvActionError)) // TODO Do a real error management
  {
    setFreeEvenData( evenData);
    return RET_OK;
  }
  else
    return Fport::justDoIt( evenData);
}

/** \retval RET_OK No problemo.
  \retval RET_CANNOTEND Cannot save the xml file. */
long Frouter::end()
{
  // Close the room
  for( long i = 0; i < listHash.getCount(); i++)
    ( ( Fport*) listHash.get( i))->end();

  return Fconfig::endXml();
}

}   //namespace evenja
