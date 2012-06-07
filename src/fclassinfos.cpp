/***************************************************************************
                             fclassinfos.cpp
                             ---------------
    begin                : ven 2 oct 2009
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

#include "fclassinfos.h"

namespace evenja {

/** Constructor without params. */
FclassInfos::FclassInfos() {}
	
/** \param[in] classType Type name of the class.
 \param[in]	classConf Filename of the configuration file (when outside the main conf file).
 \param[in]	classLib	Library name, filename without extension.
 \param[in]	classDebug Port name to see debug datas.
*/
FclassInfos::FclassInfos( char* classType, char* classConf, char* classLib, char* classDebug)
{
	type.setString( classType);
  conf.setString( classConf);
  lib.setString( classLib);
  debug.setString( classDebug);
}

FclassInfos::~FclassInfos()
{
}

}  // end namespace evenja

