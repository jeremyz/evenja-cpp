/***************************************************************************
                             evenjastrings.h
                             ---------------
    begin                : ven nov 1 2002
    copyright            : (C) 1992-2008 by Fabian José Padilla
    email                : fjp@evenja.com
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

/** This header includes the different strings of the evenja kernel. */

#ifndef EVENJA_STRINGS_H
#define EVENJA_STRINGS_H


/** xml strings (names of xml tags) for config files*/
#define XML_XML         "XML"               /** XML tag to define XML definition */

/** Nodes names for the first level of the XML config tree */
#define XML_SERVER      (char*)"evenja_server"     /** XML tag to define if the software is a server (wait until a end signal) */
#define XML_DATA        (char*)"evenja_data"			 /** XML tag to define the data */
#define XML_ROOM        (char*)"evenja_room"       /** XML tag to define a room */
#define XML_DOOR        (char*)"evenja_door"       /** XML tag to define a door */
#define XML_BOARD       (char*)"evenja_board"      /** XML tag to define a board */
#define XML_PRG         (char*)"evenja_prg"        /** XML tag to define a prg */
#define XML_INIT        (char*)"evenja_init"       /** XML tag to start a evenPrg that nitialise something for some enduser functionnalities */

/** Nodes names for the second level of the XML config tree */
#define XML_NAME        (char*)"evenja_name"       /** XML tag containing the Name of a room, door, board and prg */
#define XML_DOC         (char*)"evenja_doc"        /** XML tag to contain documentation about room, door, board and prg */
#define XML_CLASS       (char*)"evenja_class"      /** XML tag to have the name of the class */
#define XML_CONF        (char*)"evenja_conf"       /** XML tag to have the name of the physical configuration file (ex: "hello.xml" */
#define XML_LIB         (char*)"evenja_lib"        /** XML tag to have the name of the physical library (ex: "hello" for "hello.so" or "hello.dll") */
#define XML_DEBUG       (char*)"evenja_debug"      /** XML tag to enable the viewer to be connected to the port */
#define XML_LNK         (char*)"evenja_link"       /** XML tag Parameters to link an evenData to port */

/** Nodes names for the third level of the XML config tree */
#define XML_LNKSOURCE   (char*)"evenja_linksource" /** XML tag Source of the evenDtata to link with ???. */
#define XML_LNKTYPE     (char*)"evenja_linktype"   /** XML tag Name of the fields that determine the type. */
#define XML_LNKVALUE    (char*)"evenja_linktvalue" /** XML tag Value corresponding to the type. */
#define XML_LNKFIELDS   (char*)"evenja_linkfields" /** XML tag to contain the list of the fields names to make the right link value. */
#define XML_LNKDEST     (char*)"evenja_linkdest"   /** XML tag Destination of the evenData after link checked ok. */

/** xml strings ( names of xml tags) for evendatas files */
#define XML_DATAS       (char*)"evendata_datas"        /** XML tag to define a datas */
#define XML_SOURCE      (char*)"evendata_source"       /** Source of the data */
#define XML_STARTTIME   (char*)"evendata_starttime"    /** Time when the data as start */
#define XML_DESTINATION (char*)"evendata_destination"  /** List of all destinations */
#define XML_DESTCOUNT   (char*)"evendata_destcount"    /** Number of destinations */
#define XML_CURRENTDEST (char*)"evendata_currentdest"  /** Actual destination number */
#define XML_DESTNUMBER  (char*)"evendata_dest%d"       /** Destination number (completed by software) */
#define XML_LINKFIELDS  (char*)"evendata_linkfields"   /** List of all fields to do the right link */

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
// ACTIONS strings
// ---------------

// -------------------------------------------------------------------------
/** evenja SYSTEM ACTIONS
  evenDoor, evenBoard and evenPrg actions */
#define ACT_SYS_START       (char*)"SYS_START"     /** Start a port, after creation */
#define ACT_SYS_UPDATE      (char*)"SYS_UPDATE"    /** Update a port */
#define ACT_SYS_END         (char*)"SYS_END"       /** End a port, before deletion */
#define ACT_SYS_STOP        (char*)"SYS_STOP"      /** Stop the work inside the port */
#define ACT_SYS_CONTINUE    (char*)"SYS_CONTINUE"  /** Continue the work inside the port (after a stop) */
#define ACT_SYS_ADDDEST     (char*)"SYS_ADDDEST"   /** Add a spceial destinatio to an evenDoor */
#define ACT_SYS_REMOVEDEST  (char*)"SYS_REMOVEDEST"/** Remove a special destination to an evenDoor */
#define ACT_SYS_TESTMODE    (char*)"SYS_TESTMODE"  /** Enable the check of a port with the configuration of them, at runtime */
                       
// -------------------------------------------------------------------------
/** SOFTWARE ACTIONS.
    Standard actions implemented in the evenja kernel.
    Actions for evenPorts */
#define ACT_NORMAL            (char*)"normal"              /** No specific action, each Fport have is own "normal" action */

/** Action for evenBoard */
#define ACT_ONEDATADESTINATION  (char*)"oneDataDestination"    /** no special action, no link with another evenData (with the linkValue). Used in the evenPrg. */
#define ACT_LEADDESTINATION   (char*)"leadDestination"     /** it waits until another evenData arrives in the same evenBoard (with the same linkValue) and follows the Destination of them. */
#define ACT_FOLLOWDESTINATION (char*)"followDestination"   /** if another evenData with the same linkValue is waiting in the evenBoard, then follows the destination of the evenData. If no evenData with the same linkValue isn't waiting, then it wait inside the evenBoard for another evenData. */
#define ACT_WAIT              (char*)"wait"                /** it works like "leadDestination" if another evenData with the same linkValue is already inside the evenBoard. If no evenData with the same linkValue is inside the evenBoard, then it waits a time defined after the Action (ex: wait,100s). */

/** Actions for evenDoor */
#define ACT_ADD               (char*)"add"                 /** Add the evenData to Fport ( ex.: if it is an evenDoor of a DB then Add the datas to the Database) */
#define ACT_SET               (char*)"set"								 /** Set the evenData to Fport ( ex.: if it is an evenDoor of a DB then Update the record of the Database) */
#define ACT_GET               (char*)"get"                 /** Get an evenData from a Port ( ex.: if is is an evenDoor of a file, get the next line) */
#define ACT_DELETE            (char*)"delete"              /** Delete the evenData to Fport ( ex.: if it is an evenDoor of a DB then Delete the record of the Database) */

#define ACT_END               (char*)"end"                 /** Set an evenData from a Port ( ex.: if is is an evenDoor of a file, set infos) */
#define ACT_ERROR             (char*)"error"               /** The evenData goes to a specific evenPort where all errors are sents. Like a log, but it can be each evenPort inherited. */

/** Format of the wait time when ACT_WAIT is used */
#define ACT_WAIT_NOTHING      (char)' '                   /** In fact, don't wait. */
#define ACT_WAIT_YEAR         (char)'y'                   /** Wait by year value. */
#define ACT_WAIT_MONTH        (char)'n'                   /** Wait by month value. */
#define ACT_WAIT_DAY          (char)'d'                   /** Wait by day value. */
#define ACT_WAIT_HOUR         (char)'h'                   /** Wait by hour value. */
#define ACT_WAIT_MINUTE       (char)'m'                   /** Wait by minute value. */
#define ACT_WAIT_SECOND       (char)'s'                   /** Wait by seconde value. */
#define ACT_WAIT_MILLISEC     (char)'x'                   /** Wait by tenth of a second value. */

// -------------------------------------------------------------------------
/** Internal Names
    Just for fun and coherence */
#define XML_VERSION                 (char*)"1.0"           /** Version of XML (compatible) */
#define TXT_NEW                     (char*)"NEW"           /** Name of a new tree */
#define TXT_NULL                    (char*)""              /** Null string */
#define FIELD_SEPARATOR             (char)','							 /** Separator of fields */
#define FIELD_SEPARATOR_STR         (char*)","						 /** Separator of fields */
#define TREE_SEPARATOR              (char)'/'							 /** Separator of the XML TREE NODE NAME */
#define TREE_SEPARATOR_STR          (char*)"/"						 /** Separator of the XML TREE NODE NAME */
#define DESTINATION_SEPARATOR       (char)';'							 /** Separator of destination */
#define DESTINATION_SEPARATOR_STR   (char*)";"						 /** Separator of destination */
#define TXT_NOVALUES                (char*)"NOVALUES"			 /** Value that tke an evenData when no values are alreadyin the data tree */

// -------------------------------------------------------------------------

#endif

