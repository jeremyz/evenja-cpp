/***************************************************************************
                             fevenprg.h
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

#ifndef FEVENPRG_H
#define FEVENPRG_H

#include "fportbkpevendata.h"

namespace evenja {

/** evenPrg do the modification on the evenData or many evenDatas.

  function : Interface for all evenPrg.

  description : Must contain only the behavior to modify datas and "if"s concerning the
                modification of datas. Do not implement in a evenPrg "if" about end user
                functionnalities. See the withepaper.pdf at www.evenja.org.
  
  @author Fabian Padilla
*/

class FevenPrg : public FportBkpEvenData
{
private:
  /** Backup of the evenDatas that need to be sends by sendEvenData */
  FevenData* evenDataB;
  
public:
	/*! Constructor. */
	FevenPrg();
	
	/*! Destructor. */
  ~FevenPrg();

  /** Methods to sends evenDatas to a port */
  void sendEvenData( FevenData* evenData);

  /** Methods to enable all ports to sends evenDatas to a port */
  void sendEvenDataSys( FevenData* evenData);

// -----------------------------------------------------
// Virtuals
// -----------------------------------------------------
	
  /** Methods called by Fstarter */
  virtual long justDoIt( FevenData* evenData);
	
};

}	// namespace evenja

#endif
