/***************************************************************************
                             fstarter.h
                             ----------
    begin                : sam nov 2 2002
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

#ifndef FSTARTER_H
#define FSTARTER_H

#include "fevendata.h"
#include "frouter.h"

namespace evenja {

/** First class of evenja and evendoor to be created. 
  Function : Create the first level of classes Fport (Frouter,...)
             and receive informations from the OS.

  Description : root room of the evenja application.
  Connection with the OS for messaging or other incoming OS informations.
  This class implmentation is OS dependant.

  @author Fabian Padilla
*/

class Fstarter : public Frouter
{

protected:
  /** Is the software a server (deamon) or a normal software.
    A Server or deamon software wait auntil a signal ask for the end
    A normal software wil end when nothing is to do (at the end) */
  bool server;
  
  /** End of the server application ? */
  static bool exitApp;
  
public:
	
	/** Constructor. */
  Fstarter();

	/** Destructor. */
  ~Fstarter();
  
  /** Open the config file and transmit the first level of the rooms to the FfirstRouter. */
  long start( char *fileNameString);
  
  /** Method called by the "main" of the application.
			It send an evenData to all evenBoard and then to all evenDoor to really start the work of the rooms.
				- Start the work of the rooms : sent an evenData to all evenBoard and after to all evenDoor.
				- Wait for the system SIGNALs and if necessary
				- End the work of the rooms : send an evenData to all evenDoor and after to all evenBoard.
		And wait until a TERM signal arrives from the OS. */
  long execute();
  
  /** Manage if Fstarter saves the config file ( in a dinamyc configuration of rooms).
  Or if it is not needed because it is a static configuration. */
  virtual long end();
};

}   //namesspace evenja

#endif

