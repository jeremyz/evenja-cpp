/***************************************************************************
                             fstringhash.h
                             -------------
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

#ifndef FSTRINGHASH_H
#define FSTRINGHASH_H

#include "OSconfig.h"

namespace evenja {

#define STRING_MODULO 64

/** To speed up the process of comparaison between values, basically between evenData and FPort 
    evenja use a hash technology.

  function : hash a string and show hashvalue and string.
  
  description : the method "setString" is used to set the the value of the stringhash. 
  		Then  the hash value is available. 
		This will speedup the comparaison between the different "string" in evenja rooms.
		( it is faster to compare four int than a complete string).

  @author Fabian Padilla
*/

class FstringHash
{

protected : // Protected attributes

  /** The string of the Hash. */
  char string[ MAX_STRING + STRING_MODULO];
	
  /** Length of the string. */
  long len;

  /** The hash Value of the string, today is an MD5 hash technology but can be MD4, SHA-1 or another. */
  unsigned int hashValue[ 4];

// Protected methods

  /** Hash the value. You can use any technology that is fast and hash a string into a hash value.
  BUT TAKE CARE TO USE ALWAYS THE SAME IN ONE APPLICATION.
  BETWEEN TWO APPLICATIONS XML WILL NOT CONTAIN THIS HASH VALUE. */
  virtual void hash();

  /** In this implementation we use the MD5 hashing technology */
  void md5( unsigned int* state, unsigned char* str, unsigned int length);
  
public: 

  /** Constructor, without parameters (for inheritance capabilities). */
  FstringHash();

  /** Constructor, with the string to hash. */
  FstringHash( char* value);

  /** Destructor. */
  ~FstringHash();

  /** Set the string and compute the HashValue. */
  long setString(char *string);

  /** Reset all the string and the hashValue. */
  void resetString();

  /** Enabled to read the string. */
  char* getString();
	
  /** Get len of the string. */
  long getLen();
  
  /** Enable to read the HashValue. To speed up the comparaison process. */
  unsigned* getHashValue();

  /** Copy from another FstringHash. */
  void copyFrom( FstringHash *original);

  /** EQUAL. check if it is an equality between two FstringHash. */
  bool equals( FstringHash *original);

  /** COMPARE. the values between two FstringHash. */
  long compare( FstringHash *original);
};

}  // namespace evenja

#endif

