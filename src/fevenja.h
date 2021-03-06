/***************************************************************************
                        fevenja.cpp
                        -----------
 begin                : jeu nov 24 2011
 copyright            : (C) 1992-2011 by Fabian José Padilla
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

#ifndef FEVENJA_H
#define FEVENJA_H

#include "fstarter.h"

namespace evenja {

/** Object to manage evenja objects from another application.
  //xx
  Function : Create the first level of classes Fport (Frouter,...)
  and receive informations from the OS.

  Description : root room of the evenja application.
  Connection with the OS for messaging or other incoming OS informations.
  This class implmentation is OS dependant.

  @author Fabian Padilla
*/

class Fevenja
{

public:
	/** Constructor. */
  Fevenja();


};

}   // namespace evenja

#endif
