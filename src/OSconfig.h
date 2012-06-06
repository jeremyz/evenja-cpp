/***************************************************************************
                             OSconfig.h
                             ----------
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

 /** This header includes the specific file depending of the OS. */

#ifndef OSCONFIG_H
#define OSCONFIG_H

// Now only the Linux version is available

// Windows
#ifdef _WIN32__
#include "OSwindows.h"
#define OSDEFINED
#endif

// Apple
#ifdef __APPLE__
#include "OSapple.h"
#define OSDEFINED
#endif

// Linux or others
#ifndef OSDEFINED
#include "OSlinux.h"
#endif

#endif

