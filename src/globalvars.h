/***************************************************************************
                             globalVars.h
                             -------------------
    begin                : lun fév 23 2004
    copyright            : (C) 1992-2008 by Fabian José Padilla
    email                : fjp@evenja.org
 ***************************************************************************/

/******************************************************************************
 *   Copyright (C) 2012 Fabian JosŽ Padilla                                   *
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

#ifndef GLOBALVARS_H
#define GLOBALVARS_H

#include "fstringhash.h"

namespace evenja {

// ACTIONS
extern FstringHash gvActionNormal;
extern FstringHash gvActionOneDataDestination;
extern FstringHash gvActionLeadDestination;
extern FstringHash gvActionFollowDestination;
extern FstringHash gvActionWait;

extern FstringHash gvActionAdd;
extern FstringHash gvActionSet;
extern FstringHash gvActionGet;
extern FstringHash gvActionDelete;

extern FstringHash gvActionEnd;
extern FstringHash gvActionError;

// SYSTEM ACTIONS
extern FstringHash gvActionSysStart;
extern FstringHash gvActionSysUpdate;
extern FstringHash gvActionSysEnd;
extern FstringHash gvActionSysStop;
extern FstringHash gvActionSysContinue;
extern FstringHash gvActionSysAddDest;
extern FstringHash gvActionSysRemoveDest;
extern FstringHash gvActionSysTestMode;

// PARAMETERS
extern FstringHash gvNoValues;

/** Initialize the global variables, most are actions type. */
void initGlobalVars();

};

#endif


