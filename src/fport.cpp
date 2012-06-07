/***************************************************************************
                             fport.cpp
                             ---------
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

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "fport.h"
#include "returncodes.h"

namespace evenja {

// Some static informations for all ports, this means for every management of evenData
Flist Fport::listMsg;
Flist Fport::listMsgSys;
FlistHash Fport::freeEvenData;

Fport::Fport() : Fconfig()
{
  parent = 0;
  viewer = 0;
}

Fport::~Fport()
{}

/** \param[in] parentPort Set the parent of this port.  
  \param[in] fileNameString Filename in XML format to load a XML doc tree.
	\retval RET_OK No problemo.
	\retval RET_FILENAME2LONG Path and filename are longer than the MAX_PATH.
	\retval RET_CANNOTACCESS Error accessing the XML tree.
	\retval RET_NONODESELECTED Nothing found, content free.
	\retval RET_NONAME No name field in the first node.
	\retval RET_NOTEXIST First node not exist. */
long Fport::start( Fport* parentPort, char* fileNameString)
{
  parent = parentPort;
  return Fconfig::startXml( fileNameString);
}

/** \param[in] parentPort Set the parent of this port.
  \param[in] node Start a new XML tree with a node of another XML tree. The new XML tree start at the branch with this node parameter.
	\retval RET_OK No problemo.
	\retval RET_NONODESELECTED Nothing found, content free.
	\retval RET_NONAME No name field in the xml tree.
	\retval RET_NOTEXIST First node not exist. */
long Fport::start( Fport* parentPort, void* node)
{
  parent = parentPort;
  return Fconfig::startXml( node);
}

/** \param[in] port Set the debug (viewer) class inherited from Fviewer.
  \retval RET_OK No problemo. */
long Fport::setViewer( Fport *port)
{
  viewer = port;

  return RET_OK;
}

/** \param[in] evenData FevenData to be just worked.
   \retval RET_OK No problemo. */
long Fport::justDoIt( FevenData* evenData)
{
  long ret = RET_OK;
  
  // if a viewer exist then send evenData to it. To make the informations available.
  if( viewer)
    ret = viewer->receive_evenData( evenData);

  if( ret == RET_OK)
    ret = receive_evenData( evenData); // use the virtual to go to the existing high inherited class instance

  return ret;    
}

/** \param[in] evenData FevenData to be just worked in system jobs.
   \retval RET_OK No problemo. */
long Fport::justDoItSys( FevenData* evenData)
{
  setFreeEvenData( evenData);
  return RET_OK;
}

/** \param[in] evenData FevenData to send.
	\param[in] portDestination Fport where to send the FevenData.
  \return No return value. */
void Fport::sendEvenData( FevenData* evenData, Fport* portDestination)
{
// -------------------------------------------------------------------------------
// SEND THE MESSAGE IN THE QUEUE TO PRODUCE THE ASYNC PROCESS ;) :))
// -------------------------------------------------------------------------------
  if( portDestination)
    evenData->setActivePort( portDestination);
  else if( parent) // if parent exist
     evenData->setActivePort( parent); // .. use it
  else
     evenData->setActivePort( this);   // ... otherwise it is the starter and ...

  listMsg.add( evenData);  
// -------------------------------------------------------------------------------
}

/** \param[in] evenData FevenData to send system evenData.
	 \param[in] portDestination Fport where to send the system FevenData.
	 \return No return value. */
	void Fport::sendEvenDataSys( FevenData* evenData, Fport* portDestination)
{
// -------------------------------------------------------------------------------
// SEND THE MESSAGE IN THE QUEUE TO PRODUCE THE ASYNC PROCESS ;) :))
// -------------------------------------------------------------------------------
  if( portDestination)
    evenData->setActivePort( portDestination);
  else if( parent) // if parent exist
     evenData->setActivePort( parent); // .. use it
  else
     evenData->setActivePort( this);   // ... otherwise it is the starter and ...

  listMsgSys.add( evenData);
// -------------------------------------------------------------------------------
}

/** \param[in] evenData Free the FevenData. Put them to a list of free FevenData... can be used soon ;).
  \return No return value. */
void Fport::setFreeEvenData( FevenData* evenData)
{
  evenData->reset();
  FstringHash* foundIsA = freeEvenData.Search( evenData->isA());
   
  if( foundIsA)  // if found then add the evenData in the specific list (by isA)
  {
    while( evenData->getCountEvenDataB()) // Make available the evenDataB too
      ( ( FevenData*) foundIsA)->addEvenDataB( evenData->removeEvenDataB());  

    ( ( FevenData*) foundIsA)->addEvenDataB( evenData);
  }
  else		// If not found then add an evenData with is own list of free evenDatas
  {
    ( ( FstringHash*) evenData)->copyFrom( evenData->isA());  
	freeEvenData.add( evenData);  
  }
}

/** \param[in] isA Type of the FevenData.
   \retval RET_NOTEXIST This type of FevenData is not available. A least ONE FevenData of the type need to be freed first.
	 \retval FevenData_pointer An available FevenData. */
FevenData* Fport::getFreeEvenData( FstringHash* isA)
{
  FevenData* retData = NULL;
  
  FevenData* evenDataRoot = ( FevenData*) freeEvenData.Search( isA);
  
  if( evenDataRoot) // Found the evenData type (isA)
  {
    retData = evenDataRoot->removeEvenDataB();
    if( ( ( long) retData) == RET_NOTEXIST) // Not found an Instance
      retData = evenDataRoot->createInstance();
    retData->reset();
  }
  else
    retData = ( FevenData*) RET_NOTEXIST;
  
  return retData;
}
	
/** \retval RET_OK No problemo.
	 \retval RET_CANNOTEND Cannot save the xml file. */
long Fport::end()
{
  return Fconfig::endXml();
}

/** DO NOT MODIFY, USED BY THE EVENDOOR LIBRARY. FUTUR IMPLEMENTATION. */
long Fport::evendoor_condition( FevenData* evenData, Fport* port)
{
  return RET_NOTIMPLEMENTED;
}

}   //namespace evenja

