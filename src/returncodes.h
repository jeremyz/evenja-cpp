/***************************************************************************
                             returncodes.h
                             -------------
    begin                : ven nov 1 2002
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

/** This header includes the retrurn codes for the evenja, evendoor, starter and evenRouter packages. */

#ifndef RETURNCODES_H
#define RETURNCODES_H

/** If all is OK ( most of the time ?? ;) ) */
#define RET_OK	0
/** If a problem occurs. */
#define RET_KO	-1

// Standard return problems (memory, timeout, etc...)
/** Not enough memory. */
#define RET_MEMORYSPACE     -10

// Error which can be generated when the engineer develop
/** Method not already implmented. */
#define RET_NOTIMPLEMENTED  -1001
/** Text version. */
#define RET_NOTIMPLEMENTED_TXT  "NOT IMPLEMENTED" 

// Erros which can be generated at start of the application (before the rooms are working)
/** The parameter is not available. */
#define RET_NOPARAMS        -2001

/** Returns in normal usage of the evenja and evendoor technology need to be managed by the class. Base Value. */
#define RET_INTERNAL        -10000
/** The FileName is too long > MAX_PATH. */
#define RET_FILENAME2LONG   RET_INTERNAL - 1
/** String is too long. */
#define RET_STRING2LONG     RET_INTERNAL - 2
/** A router exist with the same name. */
#define RET_PORTEXIST       RET_INTERNAL - 3
/** Name not exist. */
#define RET_NONAME          RET_INTERNAL - 4
/** No informations. */
#define RET_NOINFOS         RET_INTERNAL - 5

/** Returns in normal usage of the tree or ldap used for configuration or data storage. Base Value. */
#define RET_TREE            -11000
/** Cannot access the stream (file or other). */
#define RET_CANNOTACCESS    RET_TREE - 1
/** The creation of the document is not possible. */
#define RET_CANNOTCREATE    RET_TREE - 2
/** Cannot end the stream (save file or other save datas). */
#define RET_CANNOTEND       RET_TREE - 3
/** Current = 0. */
#define RET_NONODESELECTED  RET_TREE - 4
/** {Next,Prev,Children or Parent} Node not exist and cannot be set as the current. */
#define RET_NOTEXIST        RET_TREE - 5
/** Nothing found, in the search. */
#define RET_NOTFOUND        RET_TREE - 6
/** Cannot save the file. */
#define RET_CANNOTSAVE      RET_TREE - 7

#endif

