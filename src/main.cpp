/***************************************************************************
                             main.cpp
                             --------
    begin                : mar oct  1 14:35:53 CEST 2002
    copyright            : (C) 1992-2012 by Fabian José Padilla
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

#include <stdlib.h>

#include "OSconfig.h"
#include "fstarter.h"
#include "returncodes.h"
#include "globalvars.h"

int main(int argc, char * const argv[])
{
  long ret = RET_OK;
	char buff[ MAX_STRING];

  if (argc < 2)
  {
    sprintf( buff, "Error #%ld \n", (long) RET_NOPARAMS);
    printf( "%s", buff);
		return EXIT_FAILURE;
  }

  evenja::initGlobalVars();

  evenja::Fstarter* starter = new evenja::Fstarter();
  if(! starter)                  // if created then work, otherwise error
  {
    sprintf( buff, "Error #%ld \n", ( long) RET_MEMORYSPACE);
    printf( "%s", buff);
		return EXIT_FAILURE;
  }

  // Start with the config file
  ret = starter->start( argv[ 1]);

  if (ret != RET_OK)
  {
    sprintf( buff, "Error #%ld \n", ret);
    printf( "%s", buff);
		return EXIT_FAILURE;
  }

  starter->execute();
  ret = starter->end();       // Enabled if we are in a dynamic configuration
	
  delete starter;

  return RET_OK;
}

