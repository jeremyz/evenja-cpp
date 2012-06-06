/***************************************************************************
                             fportlisthash.h
                             ---------------
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

#ifndef FPORTLISTHASH_H
#define FPORTLISTHASH_H

#include "fport.h"
#include "flisthash.h"

namespace evenja {

/** Inherited from Fport to add a listHash.

  function : maintain a list of single evenDatas ( single by the linkValue) in
             Inherited classes :
							 FevenBoard : to merge and or maintain a list of evenDatas
               Frouter : to send the evenDatas to the right destinations.
 
  description : Work as Fport. I know this class is "empty", but it is needed for the evendoor implementation.
 
  @author Fabian Padilla
*/

class FportListHash : public Fport 
{

protected: // Protected attributes

  /** List of inherited class from FstringHash ( found them faster). */
  FlistHash listHash;

public: 
	/** Constructor. */
	FportListHash();
	
	/** Destructor. */
	~FportListHash();
};

}	// namespace evenja

#endif
