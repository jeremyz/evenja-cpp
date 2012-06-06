/***************************************************************************
                             OSlinux.h
                             ---------
    begin                : ven nov 1 2002
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

 /** This header includes the specific "definition" for a specific OS. */

#ifndef OSLINUX_H
#define OSLINUX_H

/** Maximum number of chars in a path for a file. */
#define MAX_PATH              2048

/** Maximum number of chars in a string (MUST BE DIVIDED BY 4 WITHOUT REST, because hashes) */
#define MAX_STRING            1024

/** Eight levels are already to many. Normally one level is enough, only a room is my favorite. */
#define MAX_TREELEVEL         8

/* Flist management. Start with a list of 100 elements */
#define START_ELEMENTS          100 
/* Flist management. If list is full increment the size of 50 elemnts */
#define INC_ELEMENTS            50    

#endif


