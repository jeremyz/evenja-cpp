/***************************************************************************
                        flisttree.cpp
                        -------------
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

#include "flisttree.h"
#include "returncodes.h"

namespace evenja {

// -----------------------------------------------------
/** \param[in] *cmp Pointer to function to compare objA & objB. Function will receive 3 parameters ( void* objA, void* objB, void* extra).
    \param[in] *extraA Pointer to extra parameters, used to have a special behavior inside the compare function (*cmp). */
FlistTree::FlistTree( long (*cmp)( void*, void*, void* extra), void* extraA) : Flist()
{
	cmpFnct = cmp;
	extra = extraA;
}
// -----------------------------------------------------
/** \param[in] *dataToAdd Pointer to an object to add in the listTree.
    \param[in] *posMin Pointer to the minimum position in the listTree to search for.
    \param[in] *posMax Pointer to the maximum position in the listTree to search for.
    \return Position in the list where dataToAdd can be inserted or position where dataToAdd's value is EQUAL to the value of the object at this position. */
long FlistTree::searchTree( void* dataToAdd, long* posMin, long* posMax)
{
  long size = ( *posMax - *posMin);
  long workIdx = *posMin + ( size >> 1);
    
  long result = (*cmpFnct)( dataToAdd, get( workIdx), extra);
    
  // If something then search recusively
  if( size > 1)
  {
    if( result == 1)
    {
      *posMin = workIdx + 1;
      return searchTree( dataToAdd, posMin, posMax);
    }
    else if( result == -1)
    {
      *posMax = workIdx - 1;
      return searchTree( dataToAdd, posMin, posMax);
    }
    else  // Or found the same....
      return workIdx;
  }
  else  // To small to continue to search recursively ;)
  {
    if( result == 1)
    {
      result = (*cmpFnct)( dataToAdd, get( *posMax), extra);
      if( result == 1)
        return ( *posMax + 1); // Need to add this one
      else
        return *posMax;
    }
    else
      return *posMin;
  }
}
// -----------------------------------------------------
/** \param[in] *dataToAdd Pointer to an object to add in the listTree. */
void FlistTree::insertTree( void* dataToAdd)
{
	long count = getCount();
	
	if( !count) // If nothing then add the first
		add( dataToAdd);
	else // Add somethng recursively
	{
		long posFound = searchTree( dataToAdd);
		
		if( posFound == count) // End of list
			add( dataToAdd);  // add the data
		else
			insert( posFound, dataToAdd);
	}
}
// -----------------------------------------------------
/** \param[in] *dataToSearch Pointer to an object to add in the listTree.
    \return Position where *dataToSearch's value is EQUAL to the value of the object at this position. */
long FlistTree::searchTree( void* dataToSearch)
{
	long posMax = getCount();
	
	if( posMax)
	{
		posMax--; // Place 0 count
		long posMin = 0;
		
		return searchTree( dataToSearch, &posMin, &posMax);
	}
	else
		return RET_NOTFOUND; // Error nothing to found
}
    
}
