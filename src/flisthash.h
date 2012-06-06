/***************************************************************************
                             flisthash.h
                             -----------
    begin                : dim nov 3 2002
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

#ifndef FLISTHASH_H
#define FLISTHASH_H

#include "flisttree.h"
#include "fstringhash.h"

namespace evenja {

/** Special list that manage a list of FstringHash and inherited classes with only there own Hash value.

  function : maintain a list of SINGLE FstringHash ( single value define by HashValue of the name)

  description :
  - search : search for an existing FstringHash with the same hashValue
  - addOrGet and addOrRemove methods to manage the SINGLE FstringHash list.

  @author Fabian Padilla.
  I don't use templates with iterators, because many people don't know enough about templates.
  And this code need to be easily read by anyone. Another version will be optimized with new C++ 1x, in 2012 (may be ;).
    
*/  

class FlistHash : public FlistTree
{

protected : // Protected attributes


protected: // Protected methods

  /** Search the position of the same hashvalue. Return the position (pointer of the pointer) of FstringHash found in the list or if not found, NULL. */
  FstringHash** SearchPos( evenja::FstringHash* ptr);

public: 
	FlistHash();
	~FlistHash();

  /** Search if same name (stringhash) exist*/
  FstringHash* Search( evenja::FstringHash* ptr);  
  
  /** If the same name exist in the list then get the previus from the list.
  If the same name not exist, then add and return NULL. */
  FstringHash* addOrGet( evenja::FstringHash* ptr);

  /** If the same name exist in the list, then remove the stringHash from the list and return the pointer.
  if the same name not exist in the list, then add to the list. */
  FstringHash* addOrRemove( evenja::FstringHash* ptr);
  
};

} // namespace

#endif

