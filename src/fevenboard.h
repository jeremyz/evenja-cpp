/***************************************************************************
                             fevenboard.h
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

#ifndef FEVENBOARD_H
#define FEVENBOARD_H

#include "fportlisthash.h"

namespace evenja {

/** evenBoard will wait for another evenData in this evenBoard.

  function : merge informations having the same linkValue.

  description : receive an evenData and check if another evenData with the same linkValue
                is already in the list. Then Apply the ACTION to marge them together
                and send to somewhere.

  @author Fabian Padilla
*/

class FevenBoard : public FportListHash
{
public:
	/** Constructor. */
  FevenBoard();
	
	/** Destructor. */
  ~FevenBoard();

  /** Receive the evenData and execute the action. */
  virtual long receive_evenData( FevenData* evenData);
};

}	// namespace evenja

#endif

