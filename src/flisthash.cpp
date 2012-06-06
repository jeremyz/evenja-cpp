/***************************************************************************
                             flisthash.cpp
                             -------------
    begin                : dim nov 3 2002
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

#include <stdlib.h>

#include "flisthash.h"

namespace evenja {
    
long orderStringHash( void* dataA, void* dataB, void* extra)
{
    return ( ( FstringHash*) dataA)->compare( ( FstringHash*) dataB);
}

/** Constructor of the FlistHash */
FlistHash::FlistHash() : FlistTree( orderStringHash, 0) {}

/** Destructor, will delete all the FtringHash the list contain. */
FlistHash::~FlistHash()
{
  FstringHash** i;
  for( i = ( FstringHash**) firstElement; i < ( FstringHash**) firstElementFree; i++)
  {
    if( *i)
      delete *i;
  }
}

/** \param[in] name Pointer to a stringHash instance containing the name to search inside the list.
  \return Pointer to the pointer of the FstringHash in the list or NULL if not found. */
FstringHash** FlistHash::SearchPos( evenja::FstringHash *name)
{
  FstringHash** ret = NULL;

  // Parse the list to foun the same hashValue
  for( FstringHash** i = ( FstringHash**) firstElement; i < ( FstringHash**) firstElementFree && !ret; i++)
  {
    if( *i && (*i)->equals( name)) // Is it the exactly same hashValue
      ret = i;
  }

  return ret;
}

/** \param[in] ptr Pointer to a stringHash instance containing the name to search inside the list.
  \return Pointer of the FstringHash in the list or NULL if not found. */
FstringHash* FlistHash::Search( evenja::FstringHash* ptr)
{
  FstringHash** pos = SearchPos( ptr);

  if( pos)   // if something found ...
    return *pos;  // ...return the pointer of it
  else
    return NULL;
}

/** \param[in] ptr Pointer to a stringHash instance containing the name to search inside the list.
  \return Pointer of the FstringHash in the list or NULL if not found. */
FstringHash* FlistHash::addOrGet( evenja::FstringHash * ptr)
{
  FstringHash** pos = SearchPos( ptr); // First search if allready exist

  if( !pos) // if not found then ...
  {
    add( ptr); // ... add the new one	
    return NULL;
  }
  else      // if found then ...
    return ( FstringHash*) get( ( void**) pos);  // ... get the founded
}

/** \param[in] ptr Pointer to a stringHash instance containing the name to search inside the list.
  \return Pointer of the same FstringHash in the list or NULL if not found. */
FstringHash* FlistHash::addOrRemove( evenja::FstringHash* ptr)
{
  FstringHash** pos = SearchPos( ptr); // First search if allready exist

  if( !pos)  // if not found then add the new
  {
    add( ptr);  // add the param
    return NULL;
  }
  else       // if found then remove the pointer
    return ( FstringHash*) remove( ( void**) pos);
}

}   // namespace evenja

