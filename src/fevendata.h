/***************************************************************************
                             fevendata.h
                             -----------
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

#ifndef FEVENDATA_H
#define FEVENDATA_H

#include <time.h>
#include <libxml/parser.h>

#include "OSconfig.h"

#include "fconfig.h"
#include "fposition.h"
#include "flist.h"
#include "fstringhash.h"
#include "evenjastrings.h"

namespace evenja {

extern FstringHash EVENDATA_BASE;

/** Kernel of the evenja and evendoor technology => the DATA.
  Data is the only that know where they want to go. They can go to all 
  FPort inherited classes , like FevenDoor, FevenBoard, etc...
  THIS TECHNOLOGY AND SCENARIO OF USE IS COVERED BY THE 
  AGPL Affero General Public License.
  COPYRIGHT 1992-2004 Fabian Padilla.

  function: contain data, where the datas need to go and from where .

  description: A container to store datas and where the datas need to be worked. And to be evenja the way this datas link with other datas.

  @author Fabian Padilla
  */

class FevenData : public Fconfig
{

protected: // Protected attributes

// --------------------------------------\
// Properties                             >
// --------------------------------------/

  /** Where the evenData as been created. Most of the tinme an evenDoor. */
  Fposition source;

  /** Date and time when this evenData as been sent from the evenDoor in the first room. */
  time_t startToUse;

  /** List of where the evenData want to go. List of destinations. */
  Flist destination;

  /** Index of the current active destination in the list of destinations. */
  long currentDestination;

  /** The active current port where the evenData is sent. Pointer to the instance of the inherited object of FPort. */
  void* activePort;

  /** List of fields names that link two evenData by there values. */
  Flist linkFieldsNames;

  /** THE XML TREE, contain the datas. Really, only one pointer, to manage all datas ;). */
  xmlNodePtr datas;

  /** Pointers of the internal xmlBuffer when methods setDatasFromString and getDatasFromString are called. */
  xmlChar* xmlBuffer;

  /** Internal values to split strings separated by a char.
      FJP : I know ! Just for speed and not use of malloc and free, is a little stupid but... funny. Isn't it ? */
  char  splitBuffer[ MAX_STRING];
	/** Local temporary pointer of the start of the splitted string. */
  char* ptrWorkStart;
	
	/** Local temporary pointer of the end of the splitted string. */
  char* ptrWorkEnd;

  /** When a merge is done with two evenDatas in the evenBoard. The "listEvenDataB" contain a list of all other evenDatas merged with "this" one. */
  Flist* listEvenDataB;

  /** Type of evenData. There can be many different evenDatas in a Room, "evenDataClass" give them a name by type. */
  evenja::FstringHash evenDataClass;

// --------------------------------------\
// Methods                                >
// --------------------------------------/

  /** Method to split string by a char separator. */
  char* getSplitted( char separator, char* string = TXT_NULL);

  /** Go to the xml node 'name' in the Tree, or create all necessary to access to it. */
  long gotoNodeName( char* name, bool create = true,  bool onlyDatas = true);

  /** set META evenData => Source, Destination, startTime, etc... */
  void setMetaEvenDatasToXml();

  /** get META evenData => Source, Destination, startTime, etc... */
  void getMetaEvenDatasFromXml();

  /** End the sequence of importing datas to the tree, source no dependencie. */
  long setDatasFromXml( xmlDocPtr newDoc);

  /** Update the hashValue of the FevenData, if fieldName exist in the linkFieldsName or is NULL. */
  void updateHashValue( char* fieldName = NULL);

public: 

  /** Constructor */
  FevenData();

  /** Destructor */
  ~FevenData();

// -----------------------------------------------------
// From and To where evenData will go informations
// -----------------------------------------------------
	
  /** Set the source port path, from where the evenData comes. */
  long setSource( char* sourceString);

  /** Get the source position, from where the evenData comes. */
  Fposition * getSource();

  /** Add destination to the list of destinations, to where the evenData goes. */
  long addDestination( char* destinationsString);

  /** Have this evenData some Destination allready define ? */
  bool haveDestination();

  /** Get the current destination position, to where the evenData goes. */
  Fposition* getCurrentDestination();

  /** Select next destination. Ex.: after a evenBoard this can be a evenPrg, but sure a Fport inherited object. */
  long selectNextDestination();

  /** Remove all the destinations from the list and delete them. */
  void resetDestinations();

  /** Set the active port. Pointer to the Instance of the active inherited instance of FPort. */
  void setActivePort( void* port);

  /** Get the active port. Pointer to the Instance of the active inherited instance of FPort. */
  void* getActivePort();

  /** Do an action. Type of action to do in the portName ( inherited instance of FPort). */
  long setPortAction( char* actionString, char* portName = 0);

// Link evenDatas informations

  /** Name of the fields that represent the link between two evenDatas. And link is between two evenDatas THE MOST important thing in the evenja world. */
  long setLinkFieldsNames( char* linkFieldsNamesString);

  /** Remove all link fields names. */
  void resetLinkFieldsNames();

// -----------------------------------------------------
// Time information
// -----------------------------------------------------
	
  /** Init the timer for the evenData, normally when created. */
  time_t getStartToUse();
	
// -----------------------------------------------------
// evenData B management
// -----------------------------------------------------
	
  /** Add an other evenData to merged them with this. */
  void addEvenDataB( FevenData* evenData);

  /** Get an other evenData merged with this. Do not reove the pointer from the list. */
  FevenData* getEvenDataB( long idx);

  /** Remove an other evenData merged with this, and remove the pointer from the list. In FIFO mode. */
  FevenData* removeEvenDataB( long idx = 0);

  /** Get the number of other evenDatas in the list. */
  long getCountEvenDataB();

  /** Reset the list of EvenDataBs. */
  void resetEvenDataB( bool del = true);

// -----------------------------------------------------
// XML Tree access
// -----------------------------------------------------

  /** Set a "Value" string to the nodeName in the datatree. */
  long setData( char* nodeName, char* value);

  /** Get the "Value" string of the nodeName in the datatree. */
  char *getData( char* nodeName);

  /** Set a long "Value" in the datatree. */
  long setDataLong( char* nodeName, long value);

  /** Get the long "Value" of the nodeName in the datatree. */
  long getDataLong( char* nodeName);

  /** Set ALL the datas of the datatree.
  All new datas replace the old datas. */
  long setDatasFromString( char* stringXML);

  /** Set ALL the datas of the datatree.
  From a File or a stream. All this new datas replace the old datas. */
  long setDatasFromFile( char* fileNameString);

  /** Get ALL the datas to a string (ex.: XML format). */
  char* getDatasToString();

  /** Get ALL the datas to a File or a stream. */
  long getDatasToFile( char* fileNameString);

  /** Copy all datas from another evenData. */
  long copyFrom( FevenData* data);

// -----------------------------------------------------
// Virtuals
// -----------------------------------------------------
	
  /** Return the StringHash of the evenData type. */
  virtual FstringHash* isA();

  /** Init the Datas Structure. */
  virtual void initDatas();

  /** Reset the datas ( erase all informations). */
  virtual void reset();

  /** CreateInstance of the same evenData. */
  virtual FevenData* createInstance();

};

}	// namespace evendata

#endif
