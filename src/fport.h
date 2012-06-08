/***************************************************************************
                             fport.h
                             -------
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

#ifndef FPORT_H
#define FPORT_H

#include "fconfig.h"
#include "fevendata.h"
#include "flisthash.h"


namespace evenja {

/** Origin class for all part of the software that receive an evenData in evenja paradigm.

  function: Abstract class for ALL ports : FevenPrg, FevenDoor, FevenBoard, Frouter and Fviewer.

  description : Implement only the behavior with the viewer.

  ***********
  IMPORTANT :
  ***********
  In the method receive_evenData each inherited class need to call the parent
  method first , with : Fport::receive_evenData( evenData);

  @author Fabian Padilla

*/

class Fport : public Fconfig
{
protected: // Protected attributes

  /** List of all wainting envenData to be send to a port (internal message queuing) */
  static Flist listMsg;

  /** List of all wainting envenData with system datas to be send to a port (internal message queuing */
  static Flist listMsgSys;

  /** List of Free and Available evenDatas (faster than new and delete ;) */
  static FlistHash freeEvenData;

  /** Router where this port (evenDoor, evenBoard or evenPrg) is connected and from which
  it receive the evenData. */
  Fport* parent;

  /** Enable to view the datas inside the port (evenDoor or evenBoard). */
  Fport* viewer;


public:
	/** Constructor. */
  Fport();
	
	/** Destructor. */
  ~Fport();

  /** Set the debug viewer. Where all incoming evenDatas are displayed with the config of the port. */
  long setViewer( Fport* viewer);

  /** Methods called from inherited class to send evenData to another port */
  void sendEvenData( FevenData* evenData, Fport* portDestination = 0);

  /** Methods called from inherited class to send system evenData to another port */
  void sendEvenDataSys( FevenData* evenData, Fport* portDestination = 0);

  /** Get a free FevenData  */
  FevenData* getFreeEvenData( FstringHash* isA = &EVENDATA_BASE);

// -----------------------------------------------------
// Virtuals
// -----------------------------------------------------
	
  /** Start configuration of an instance with an XML file, and sets the parent router. */
	virtual long start( Fport* parentPort, char* fileNameString);
	
	/** Start configuration of an instance with a node in an XML tree, and sets the parent router. */
  virtual long start( Fport* parentPort, void* node);
	
	/** Where the data arrive in a Fport inherited class : Frouter, FevenPrg, FevenDoor or FevenBoard. Abstract because need to be implemented in any inherited class. */
  virtual long receive_evenData( FevenData* evenData) = 0;
	
  /** To force futur developer to implement the right behavior for evenDoor and evenBoard */
  virtual long end();
	 	
  /** Methods called by Fstarter. */
  virtual long justDoIt( FevenData* evenData);
	
  /** Methods called by Fstarter. */
  virtual long justDoItSys( FevenData* evenData);
	
  /** Set an evenData free */
  virtual void setFreeEvenData( FevenData* evenData);
	
  /** USED BY THE EVENDOOR LIBRARY. FUTUR IMPLEMENTATION. */
  virtual long evendoor_condition( FevenData* evenData, Fport* port);
};

} //namespace evenja

#endif
