/***************************************************************************
                             fposition.h
                             -----------
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

#ifndef FPOSITION_H
#define FPOSITION_H

#include "fstringhash.h"
#include "flist.h"

namespace evenja {

/** Define the position ( source OR destination) of the evenData.
  function : maintain the stringHashs for the computer, rooms, port, action.
  Format example : www.revena.com/room1/room2/port:normal 

  description : method "setPosition" set all position informations this mean
  - computer
  - room
  - port
  - action.
  Then these informations are retrieved with getComputer, getRoom, getPort,
  getAction methods.

  @author Fabian Padilla
*/

class Fposition : public FstringHash
{

protected:

  /** computer destination or source. */
  FstringHash computer;

  /** room destination or source. */
  Flist rooms;

  /** Number of levels inside the Flist rooms. */
  long nbLevel;

  /** port destination or source. */
  FstringHash port;

  /** action to do at the position (source or destination). */
  FstringHash action;

  /** wait time in the action. */
  long waitTime;

  /** Unit for the waitTime (ex.: y(year), n(month), d(day), h(hour), m(minute), s(seconde) or x(milliseconde)). */
  char unitWaitTime;

  /** Is this position active. */
  bool positionActived;

  /** reset position (erase datas). */
  void resetPosition();

public: 

  /** Constructor. */
  Fposition();

  /** Destructor. */
  ~Fposition();

  /** Set the source or the destination of an evenData. */
  long setPosition( char *positionString);

  /** Get the computer name. If the evenData needs to go to another computer. */
  FstringHash *getComputer();

  /** Get the room for destination or source. */
  FstringHash *getRoom( long level = 0);

  /** Number of levels in the rooms routing tree. */
  long getNbLevel();

  /** Get the port of the position (source or destination). This means an evenDoor or a evenBoard. */
  FstringHash *getPort();

  /** Get the action of the position (source or destination). */
  FstringHash *getAction();

  /** Get the amount of waiting time (unity is another get function). */
  long getWaitTime();

  /** Get the unity time y,n,d,h,m,s or x. */
  char getUnitWaitTime();

  /** Copy a position From another Fposition class. */
  void copyFrom( Fposition* pos);

};


} // namespace evenja


#endif
