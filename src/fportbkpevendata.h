/***************************************************************************
                             fportbkpevendata.h
                             ------------------
    begin                : sam nov 2 2002
    copyright            : (C) 1992-2008 by Fabian José Padilla
    email                : fjp@evenja.com
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

#ifndef FPORTBKPEVENDATA_H
#define FPORTBKPEVENDATA_H

#include "fport.h"

namespace evenja {

/** Inherited from Fport to secure the FevenData, when software "forget" to manage them... Better than a "garbage collector".

  function : secure the use of evenData send to evenPrg or evenDoor.  
             if the inherited from evenPrg and evenDoor forget to send the
             evenData then this backup class will save it.

  description : receive an evenData, secure the evenData and give it to the inherited class.

  @author Fabian Padilla
*/

class FportBkpEvenData : public Fport
{
private:
  /** Backup of the evenDatas that need to be sends by sendEvenData */
  FevenData* evenDataBkp;

protected: // Protected attributes

public: 
  /** Constructor. */
	FportBkpEvenData();

	/** Destructor. */
  ~FportBkpEvenData();

  /** Methods to enable all ports to sends evenData to a port */
  void sendEvenData( FevenData* evenData, Fport* portDestination = 0);

  /** Methods to enable all ports to sends system evenData to a port */
  void sendEvenDataSys( FevenData* evenData, Fport* portDestination = 0);

// -----------------------------------------------------
// Virtuals
// -----------------------------------------------------

  /** Methods called by Fstarter */
  virtual long justDoIt( FevenData* evenData);
	
  /** Methods to enable all ports to free an evenData */
  virtual void setFreeEvenData( FevenData* evenData);
  
};

}	// namespace evenja

#endif
