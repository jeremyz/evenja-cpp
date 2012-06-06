/***************************************************************************
                             fconditionlink.h
                             ----------------
    begin                : ven 2 oct 2009
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

#ifndef FCONDITIONLINK_H
#define FCONDITIONLINK_H

#include "fstringhash.h"

namespace evenja {

/** function : Contain stringhash informations to define conditional links between a source and a destination.
 
   description : If concatenation of [typeFields]'s values are equal to [value],
   		then the [destination] will apply with the evenData's linkValue defined by [fields].
 
   @author Fabian Padilla
*/

class FconditionLink
{
public: // Variable are all public.
	
	/** Where the specialLink will apply. */
  FstringHash source;
	
// -----------------------------------------------------
// Condition of application of conditionalLink
// -----------------------------------------------------

  /** List of fields to generate a temporary value that need to be equal to [value] to apply the conditionLink. */
  FstringHash typeFields;

  /** Value to compare with concatened [typeFields]'s values, to apply or not a conditionLink. */
  FstringHash value;

// -----------------------------------------------------
// When conditionLink apply, then ...
// -----------------------------------------------------

  /** EvenData's fields to generate the linkValue for the rest of the room (if conditionLink apply). */
  FstringHash fields;
  
  /** EvenData's destination, when conditionLink apply. */
  FstringHash destination;

public:
	
	/** Constructor withour parameters. */
	FconditionLink();
	
	/** Constructor, with the only parameters of the class. */
  FconditionLink( char* linkSource, char* linkTypeFieldsNames, char* linkValue, char* linkFieldsNames, char* linkDestination);

	/** Destructor. */
  ~FconditionLink();

};

}	// namespace evenja

#endif

