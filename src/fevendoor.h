/***************************************************************************
                             fevendoor.h
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

#ifndef FEVENDOOR_H
#define FEVENDOOR_H

#include "fportbkpevendata.h"

namespace evenja {

/** Door of the room.

  function : evenDoor of the room. Connect the room to external world.
             To a specific prototcol and data format.

  description : evenDoor would convert a specific data format to the internal
                evenData format and the evenData format to the external data format.

  @author Fabian Padilla
*/

class FevenDoor : public FportBkpEvenData
{

protected: // Protected attributes

  /** List of special destination, with condition.
      In the futur, will be moved to the Fport.
      This version in done to explain with simplicity evenja to a maximum of peoples. */
  Flist list;

public:
	
	/** Constructor. */
	FevenDoor();

	/** Destructor. */
  ~FevenDoor();

  /** Methods to sends evenDatas to a port */
  void sendEvenData( FevenData* evenData);

// -----------------------------------------------------
// Virtuals
// -----------------------------------------------------
	
  /** Methods called by Fstarter */
  virtual long justDoItSys( FevenData* evenData);
	
};

}	// namespace evenja

#endif
