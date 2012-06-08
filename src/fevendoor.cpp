/***************************************************************************
                             fevendoor.cpp
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

#include "fevendoor.h"
#include "globalvars.h"
#include "returncodes.h"
#include "fconditionlink.h"

namespace evenja {

FevenDoor::FevenDoor() : FportBkpEvenData() {}

FevenDoor::~FevenDoor()
{
  while( list.getCount())
    delete ( FconditionLink*) list.remove( ( long) 0);
}

/** \param[in] evenData FevenData to send.
	 \return No return value. */	
void FevenDoor::sendEvenData( FevenData* evenData)
{
  FconditionLink* spDestToDo = 0;
  bool allEvenData = false;

  /** Check if the destination address is define */
  if( evenData->haveDestination())
    return FportBkpEvenData::sendEvenData( evenData);

/** In the futur, will be moved to the Fport.
    This version in done to explain with simplicity evenja to a maximum of peoples */
  for( long i = 0; i < list.getCount(); i++)
  {
    FconditionLink* spDest = ( FconditionLink*) list.get( i);

    // If nothing in the string then OK to send all evenData to the dest
    allEvenData = !(*spDest->typeFields.getString());

    // Set the fields to check value correctly
    if( !allEvenData)
      evenData->setLinkFieldsNames( ( char*) spDest->typeFields.getString());

    if( allEvenData || evenData->equals( &spDest->value)) // is the same value
    {
      if( spDestToDo)
      {
        FevenData* evenDataToDo = getFreeEvenData();
        evenDataToDo->copyFrom( evenData);

        evenDataToDo->setSource( ( char*) getString());
        evenDataToDo->setLinkFieldsNames( ( char*) spDestToDo->fields.getString());

        evenDataToDo->resetDestinations();
        evenDataToDo->addDestination(  ( char*) spDestToDo->destination.getString());

        FportBkpEvenData::sendEvenData( evenDataToDo);
      }

      spDestToDo = spDest;
    }
  }

  if( spDestToDo)  // Something to send
  {
     evenData->setSource( ( char*) getString());
     evenData->setLinkFieldsNames( ( char*) spDestToDo->fields.getString());

     evenData->resetDestinations();
     evenData->addDestination(  ( char*) spDestToDo->destination.getString());

     FportBkpEvenData::sendEvenData( evenData);
   }
   else // Otherwise it means that the data go back to available datas
     parent->setFreeEvenData( evenData);

}

/** \param[in] evenData FevenData to be just worked in system jobs.
	 \retval RET_OK No problemo.
	 \retval RET_MEMORYSPACE No more memory space. */
long FevenDoor::justDoItSys( FevenData* evenData)
{
	long ret = RET_OK;
		
	if( evenData->getCurrentDestination()->getAction()->equals( &gvActionSysAddDest))
		ret = list.add ( new FconditionLink( evenData->getData( XML_LNKSOURCE),
																				 evenData->getData( XML_LNKTYPE),
																				 evenData->getData( XML_LNKVALUE),
																				 evenData->getData( XML_LNKFIELDS),
																				 evenData->getData( XML_LNKDEST)));
	
	setFreeEvenData( evenData);
	
	return ret;
}

}   // namespace evenja
