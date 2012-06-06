/***************************************************************************
                        flisttree.h
                        -----------
 begin                : sam mai 29 2010
 copyright            : (C) 2010 by Fabian José Padilla
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

#ifndef _LISTTREE_H
#define _LISTTREE_H

#include "flist.h"

namespace evenja {
  
/** List sorted by an external function.

  function : Access as fast as possible the elements of the list (using tree like redblack methods, but on a single list).
 
  description :
  - insertTree : Insert an object in the list directly in the right place in the list
  - searchTree ; Search an object in the tree (if another object with the same value exist).
 
  @author Fabian Padilla.
  I don't use templates with iterators, because many people don't know enough about templates.
  And this code need to be easily read by anyone. Another version will be optimized with new C++ 1x, in 2012 (may be ;).
   
*/

class FlistTree :public Flist
{
  /** Pointer to the compare function to decide if value of objA is higher, lower or equal to value of objB.
   \retval 0 ObjA's value is EQUAL to objB's value.
   \retval 1 ObjA's value is HIGHER to objB's value.
   \retval -1 ObjA's value is LOWER to objB's value. */
  long (*cmpFnct)( void* objA, void* objB, void* extra);
	
  /**  Pointer to extra parameters, used to have a special behavior inside the compare function (*cmp). */
  void* extra;

private :
  /** Internal and real search method, used recursively (FP: I like). */
	long searchTree( void* dataToAdd, long* posWork, long* posMax);
	
public:
  /*! Constructor. */
	FlistTree( long (*cmp)( void*, void*, void*), void* extra);
	
  /** Insert an object in the list directly in the right place in the list. */
	void insertTree( void* dataToAdd);

  /** Search an object in the tree (if another object with the same value exist). */
	long searchTree( void* dataToSearch);

};

}

#endif
