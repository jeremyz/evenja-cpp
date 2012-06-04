/***************************************************************************
                             flist.cpp
                             ---------
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

#include <string.h>
#include <stdlib.h>
 
#include "flist.h"
#include "returncodes.h"

namespace evenja {

Flist::Flist()
{
  nbElements = 0;
  resizeBuffer( START_ELEMENTS);
}

Flist::~Flist()
{
  free( firstElement);
}

/** \param[in] nbElementsToAdd	Number of available elements to add in the list.
  \retval RET_OK No problemo.
  \retval RET_MEMORYSPACE No more memory space. */
long Flist::resizeBuffer( long nbElementsToAdd)
{
  long newNbElements = nbElements + nbElementsToAdd;

  long bufferSize = newNbElements * sizeof( void*);
  void* bufferStart = (FstringHash*) malloc( bufferSize);

  if( !bufferStart) // if null returned then no more memory HAAAAAA HELP
    return RET_MEMORYSPACE;

  memset( bufferStart, NULL, bufferSize); // Mister proper...clean up ;)

  if( nbElements)         // is it the first size of the list ?
  {                       // No, then copy old data to new buffer
    memcpy( bufferStart, (void*) firstElement, ( nbElements * sizeof( void*)));
    free( firstElement);  // And free old buffer
  }

  firstElementFree = ( ( void**) bufferStart) + nbElements;

  nbElements = newNbElements;
  firstElement = ( void**) bufferStart;
  lastElement = firstElement + newNbElements;

  return RET_OK;
}

/** \return No return value. */
void Flist::reset()
{
  firstElementFree = firstElement;
}
  
/** \param[in] ptr Add an object pointer at the end of the list.
  \retval RET_OK No problemo.
  \retval RET_MEMORYSPACE No more memory space. */
long Flist::add( void* ptr)
{
  long ret = RET_OK;

  if( firstElementFree >= lastElement) // Is the table full ?
    ret = resizeBuffer( INC_ELEMENTS); // ...Resize the buffer of pointers

  if( ret == RET_OK)  // if all OK, then really add
  {
    *firstElementFree = ptr;
    firstElementFree++;
  }

  return ret;
}

/** \param[in] idx Position index to insert the object.
	\param[in] ptr Object pointer to insert.
	\retval RET_OK No problemo.
  \retval RET_MEMORYSPACE No more memory space. */
long Flist::insert( long idx, void* ptr)
{
  long ret = RET_OK;
  
  void** elementIdx = ( ( void**) firstElement) + idx;

  if( firstElementFree >= lastElement) // Is the table full ?
    ret = resizeBuffer( INC_ELEMENTS); // ...Resize the buffer of pointers

  if( ret == RET_OK)  // if all OK, then really add
  {
    // Move the end of the list to creat place for the new element
    memmove( ( elementIdx + 1), elementIdx, ( ( firstElementFree - elementIdx) * sizeof( void*)));

    *elementIdx = ptr;
    firstElementFree++;    
  }

  return ret;  
}

/** \param[in] idx Position index to read the object pointer.
  \retval RET_NOTEXIST Pointer to the RET_NOTEXIST value. 
  \retval other_pointer_value : The asked pointer. */
void* Flist::get( long idx)
{
  void** elementIdx = ( ( void**) firstElement) + idx;

  return get( elementIdx);
}

/** \param[in] pos Pointer to the pointer of the object to read.
  \retval RET_NOTEXIST Pointer to the RET_NOTEXIST value. 
  \retval other_pointer_value The asked pointer. */
void* Flist::get( void** pos)
{
  if( pos >= firstElement && pos < firstElementFree) // is it in the list space ? 
    return *pos;
  else
    return ( char*) RET_NOTEXIST;
}

/** \param[in] idx Position index of the object to remove from the list. Replace the previous pointer in the list with NULL.
  \retval RET_NOTEXIST Pointer to the RET_NOTEXIST value. 
  \retval other_pointer_value The asked pointer. */
void* Flist::remove( long idx)
{
  void** elementIdx = ( ( void**) firstElement) + idx;

  return remove( elementIdx);
}

/** \param[in] pos Position of the pointer of the object to remove from the list. Replace the previous pointer in the list with NULL.
  \retval RET_NOTEXIST Pointer to the RET_NOTEXIST value. 
  \retval other_pointer_value The asked pointer. */
void* Flist::remove( void** pos)
{
  void* ptr = NULL;

  if( pos >= firstElement && pos < firstElementFree) // is it in the list space ?
  {
    ptr = *pos;  // get the data from the list

    if( --firstElementFree != pos) // if it is not the last ?
      *pos = *firstElementFree;    // copy the last data to where the removed data was taken.

    *firstElementFree = NULL;         // and clean the last data

    return ptr;
  }
  else
    return ( char*) RET_NOTEXIST;    
}

/** \retval RET_NOTEXIST Pointer to the RET_NOTEXIST value. 
  \retval other_pointer_value The asked pointer. */
void* Flist::removeFifo()
{
  void* ptr = NULL;

  if( firstElement < firstElementFree)  // Something in the list ?
  {
    ptr = *firstElement;                // get the first

    // move all the list 
    memmove( firstElement, ( firstElement + 1), ( ( ( firstElementFree - firstElement) - 1) * sizeof( void*)));

    *firstElementFree-- = NULL;            // clean the last

    return ptr;
  }
  else
    return ( char*) RET_NOTEXIST;
}

/** \retval RET_NOTEXIST Pointer to the RET_NOTEXIST value. 
  \retval other_pointer_value The asked pointer. */
void* Flist::removeStack()
{
  void* ptr = NULL;

  if( firstElement < firstElementFree)  // Something in the list ?
  {
    firstElementFree--;                 // change to the last

    ptr = *firstElementFree;            // take the last data

    *firstElementFree = NULL;              // clean the last

    return ptr;
  }
  else
    return ( char*) RET_NOTEXIST;

}

/** \return Number of elements. */
long Flist::getCount()
{
  return ( firstElementFree - firstElement);
}

}   // namespace evenja

