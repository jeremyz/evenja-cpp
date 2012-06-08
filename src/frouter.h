/***************************************************************************
                             frouter.h
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

#ifndef FROUTER_H
#define FROUTER_H

#include <libxml/tree.h>

#include "fportlisthash.h"
#include "fevendata.h"

#include "fclassinfos.h"
#include "fconditionlink.h"

namespace evenja {

/** function : Manage the entire routing of evenDatas between routers,
               evenDoor, evenBoard and evenPrg.

    description : route like an tcpip/internet router the evenData to his destination.

  @author Fabian Padilla
*/

class Frouter : public FportListHash
{

protected: // Protected attributes

  /** Get the informations concerning the cration of a port (room, evenprg, etc...) */
  long getClassInfos( FclassInfos* classInfos);

  /** Get the informations concerning the cration of a port (room, evenprg, etc...) */
  long getLinkInfos( FconditionLink* conditionLink);

  /** Create a room with a structure defined by the config or node in start method */
  long createRoom();

public:
	
	/** Constructor. */
	Frouter();
	
	/** Destructor. */
	~Frouter();
	
// -----------------------------------------------------
// Virtuals
// -----------------------------------------------------

  /** Start configuration of an instance with an XML file, and sets the parent router. */
	virtual long start( Fport* parentPort, char* fileNameString);
	
	/** Start configuration of an instance with a node in an XML tree, and sets the parent router. */
  virtual long start( Fport* parentPort, void* node);

  /** Receive the evenData to be routed to the right router or port. */
  virtual long receive_evenData( FevenData* evenData);

  /** Deploy the end() until the port. */
  virtual long end();

  /** Methods called by Fstarter. */
  virtual long justDoIt( FevenData* evenData);

};

} // namespace evenja

// MACROS TO IMPORT THE RIGTH CLASSE

#endif
