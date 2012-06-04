/***************************************************************************
                             flist.h
                             -------
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

#ifndef FLIST_H
#define FLIST_H

#include "fstringhash.h"

namespace evenja {

/** List that manage a table of pointer.

  function : maintain a list of pointer.

  description : pointers (or other 32bit values) can be
  - added
  - returned by giving the idx in the list
  - returned by giving the idx in the list and removed from them
  - FIFO : older returned and removed from the list, by FisrtInfirstOut order
  - FILO : First in last out, last added will be the first to be taken

  @author Fabian Padilla.
  I don't use templates with iterators, because many people don't know enough about templates.
  And this code need to be easily read by anyone. Another version will be optimized with new C++ 1x, in 2012 (may be ;).

*/

class Flist 
{

protected : // Protected attributes

  /** First element in the list, the begin of the malloc pointer's buffer too. */
  void** firstElement;

  /** Last element that can be used in the list. */
  void** lastElement;

  /** Maximum mumber of elements available in the current list. */
  long nbElements;                  

  /** First element that can be used to add a new value. */
  void** firstElementFree;        

  // Protected methods

  /** Change the size and increase the list size ( numbers of pointer void*). */
  long resizeBuffer( long nbElementsToAdd);

  /** Get from the list. With **pos. */
  void* get( void** pos);

  /** Remove from the list. With **pos. */
  void* remove( void** pos);

public:

  /** Constructor, init buffer list. */ 
  Flist();

  /** Destructor, delete the buffer, but not the content pointed by. */
  ~Flist();
	
  /** Reset, clean all the list by resetting internal pointers. */
  void reset();
  
  /** Add an element in the list, at the end of it. */
  long add( void* ptr);
  
  /** Insert an element in the list, at a specific place. */
  long insert( long idx, void* ptr);
  
  /** Get from the list. With idx. */
  void* get( long idx);

  /** Remove from the list. With idx. */
  void* remove( long idx);

  /** Remove from the list. First In First Out. */
  void* removeFifo();
  
  /** Remove from the list. First In Last Out as a Stack. */
  void* removeStack();
  
  /** Get count (number of elements in the listi). */
  long getCount();
  
};

} // namespace

#endif

