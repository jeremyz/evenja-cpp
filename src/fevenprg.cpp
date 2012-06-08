/***************************************************************************
                             fevenprg.cpp
                             ------------
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

#include "fevenprg.h"

namespace evenja {

FevenPrg::FevenPrg() : FportBkpEvenData()
{
  evenDataB = 0;
}

FevenPrg::~FevenPrg() {}

/** \param[in] evenData FevenData to send.
  \return No return value. */	
void FevenPrg::sendEvenData( FevenData* evenData)
{
  if( evenDataB == evenData)  // If send then, NO PROBLEMO
    evenDataB = 0;

  FportBkpEvenData::sendEvenData( evenData);
}

/** \param[in] evenData FevenData to send system evenData.
	\return No return value. */
void FevenPrg::sendEvenDataSys( FevenData* evenData)
{
// If a received data is send then no error at the end of the "receive_evenData" ;)
  if( evenDataB == evenData)
    evenDataB = 0;

  FportBkpEvenData::sendEvenDataSys( evenData);
}

/** \param[in] evenData FevenData to be just worked.
	\retval RET_OK No problemo.
	\retval RET_MEMORYSPACE No more memory space. */
long FevenPrg::justDoIt( FevenData* evenData)
{
	//  if( ( evenDataB = evenData->removeEvenDataB()))
	//    evenData->addEvenDataB( evenDataB);
		
	long ret =  FportBkpEvenData::justDoIt( evenData);
		
	// XXXXXXXXXXXXXXXX
	/*  if( evenDataB) // The evenPrg have forget to send a data ???
	 { // Yes, then evenja send it to error
	 evenDataB->definePortAction( ACT_ERROR);
	 sendEvenData( evenDataB);
	 } */
		
	return ret;
}
	
}   //namespace evenja

