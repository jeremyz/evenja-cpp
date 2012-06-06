/***************************************************************************
                             fportbkpevendata.cpp
                             --------------------
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

#include "fportbkpevendata.h"

namespace evenja {

FportBkpEvenData::FportBkpEvenData() : Fport()
{
  evenDataBkp = 0;
}

FportBkpEvenData::~FportBkpEvenData() {}

/** \param[in] evenData FevenData to send.
  \param[in] portDestination	Fport where to send the FevenData.
	\return No return value. */
void FportBkpEvenData::sendEvenData( FevenData* evenData, Fport* portDestination)
{
// If a received data is send then no error at the end of the "receive_evenData" ;)
  if( evenDataBkp == evenData)
    evenDataBkp = 0;

  Fport::sendEvenData( evenData, portDestination);
}

/** \param[in] evenData FevenData to send.
 \param[in] portDestination	Fport where to send the FevenData.
 \return No return value. */
void FportBkpEvenData::sendEvenDataSys( FevenData* evenData, Fport* portDestination)
{
// If a received data is send then no error at the end of the "receive_evenData" ;)
  if( evenDataBkp == evenData)
    evenDataBkp = 0;

  Fport::sendEvenDataSys( evenData, portDestination);
}
	
/** \param[in] evenData FevenData to be just worked.
  \retval RET_OK No problemo. */
long FportBkpEvenData::justDoIt( FevenData* evenData)
{
	// Backup the evenData send to the main evenData manager
	evenDataBkp = evenData;
	
	long ret = Fport::justDoIt( evenData);
	
	if( evenDataBkp)
	{
		evenDataBkp->setPortAction( ACT_ERROR);
		sendEvenData( evenDataBkp);
	}
	
	return ret;
}

/** \param[in] evenData FevenData to make available for another need.
	\return No return value. */
void FportBkpEvenData::setFreeEvenData( FevenData* evenData)
{
// If a received data is freed then no error at the end of the "receive_evenData" ;)
  if( evenDataBkp == evenData)
	evenDataBkp = 0;
	
  Fport::setFreeEvenData( evenData);
}  

}   // namespace evenja
