/***************************************************************************
                             fviewer.h
                             ---------
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

#ifndef FVIEWER_H
#define FVIEWER_H

#include "fport.h"
#include "fevendata.h"

namespace evenja {

/** Debugger class.
  function : receive information about :
    - Configuration of a port (evenDoor or evenBoard)
    - Data waiting inside the port (evenDoor or evenBoard)

  description : This class cannot be different inside the same room,
                because all ports (evenDoor and evenBoard)
                need to be able to
                access the head information :
                - source
                - destination
                and access the data information.  
                WITHOUT HAVING TO DO A VERSIONNING.
  
  @author Fabian Padilla
*/

class Fviewer : public Fport
{

protected : // Protected attributes
    
public:
	
	/** Constructor. */
	Fviewer();
	
	/** Destructor. */
	~Fviewer();  
};

}   // namespace evenja

#endif
