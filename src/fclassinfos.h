/***************************************************************************
                             fclassinfos.h
                             -------------
    begin                : tue september 15 2009
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

#ifndef FCLASSINFOS_H
#define FCLASSINFOS_H

#include "fstringhash.h"

namespace evenja {

/** description : Contain strings informations about classes of evenja get from the config file (XML).

  @author Fabian Padilla
*/

struct FclassInfos
{

  /** XML_CLASS type name of the class. */
  FstringHash type;

	/** XML_CONF filename of the configuration file. */
  FstringHash conf;

	/** XML_LIB library name, filename without extension. */
  FstringHash lib;

	/** XML_DEBUG  port name to see debug datas. */
  FstringHash debug;
	

	/** Constructor without params. */
	FclassInfos();
	
	/** Constructor, with the only parameters of the class. */
	FclassInfos( char* classType, char* classConf, char* classLib, char* classDebug);
	
	/** Destructor. */
	~FclassInfos(); 

};

} // namespace evenja

#endif
