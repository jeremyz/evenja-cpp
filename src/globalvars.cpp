/***************************************************************************
                             globalVars.cpp
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


#include "evenjastrings.h"
#include "fstringhash.h"
 

namespace evenja {

// ACTIONS  
FstringHash gvActionNormal;
FstringHash gvActionOneDataDestination;
FstringHash gvActionLeadDestination;
FstringHash gvActionFollowDestination;
FstringHash gvActionWait;

FstringHash gvActionAdd;
FstringHash gvActionSet;
FstringHash gvActionGet;
FstringHash gvActionDelete;

FstringHash gvActionEnd;
FstringHash gvActionError;

// SYSTEM ACTIONS
FstringHash gvActionSysStart;
FstringHash gvActionSysUpdate;
FstringHash gvActionSysEnd;
FstringHash gvActionSysStop;
FstringHash gvActionSysContinue;
FstringHash gvActionSysAddDest;
FstringHash gvActionSysRemoveDest;
FstringHash gvActionSysTestMode;

FstringHash gvNoValues;


/** \return No return value. */
void initGlobalVars()
{
	// Init normal actions
  gvActionNormal.setString( ACT_NORMAL);
  gvActionOneDataDestination.setString( ACT_ONEDATADESTINATION);
  gvActionLeadDestination.setString( ACT_LEADDESTINATION);
  gvActionFollowDestination.setString( ACT_FOLLOWDESTINATION);
  gvActionWait.setString( ACT_WAIT);

  gvActionAdd.setString( ACT_ADD);
  gvActionSet.setString( ACT_SET);
  gvActionGet.setString( ACT_GET);
  gvActionDelete.setString( ACT_DELETE);

  gvActionSet.setString( ACT_END);
  gvActionError.setString( ACT_ERROR);

    // Init system actions
	gvActionSysStart.setString( ACT_SYS_START);
	gvActionSysUpdate.setString( ACT_SYS_UPDATE);
	gvActionSysEnd.setString( ACT_SYS_END);
	gvActionSysStop.setString( ACT_SYS_STOP);
	gvActionSysContinue.setString( ACT_SYS_CONTINUE);
	gvActionSysAddDest.setString( ACT_SYS_ADDDEST);
	gvActionSysRemoveDest.setString( ACT_SYS_REMOVEDEST);
	gvActionSysTestMode.setString( ACT_SYS_TESTMODE);

  gvNoValues.setString( TXT_NOVALUES);
}

};
