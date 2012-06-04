/***************************************************************************
                             fconfig.h
                             ---------
    begin                : sam nov 2 2002
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

#ifndef FCONFIG_H
#define FCONFIG_H

#include <libxml/tree.h>

#include "fstringhash.h"
#include "flist.h"

namespace evenja {

/** Class done to open or load and close or save the config in tree files
  (XML now, but can be changed to connect a LDAP tree or any other tree data structure).

  function : It is the access to a tree of information needed by the class which inheritate from Fconfig.
  This class can be modified if the datas are stored in another system than a file.
  The file can be a stream or every other input stream data ( good in a tree like XML or LDAP).

  description :
  - Methods start and startNew will connect Fconfig to a tree (XML in this example, but can be a
     LDAP or other tree style).
  - Method end will enable to save the tree (not always needed, example config xml file).
  - Method resetCurrent will reset the current pointer node and point to the root or first node.
  - Methods gotoNext,gotoPrev, gotoChildren, gotoParent enable to move inside the tree.
  - Methods Find and FindNext enable to search by name an tree Node.

  Fconfig is a generic caller for a tree access. This enable to change the type of supported tree XML,
    LDAP or others, without having to update the evenja kernel.  
  
  @author Fabian Padilla
*/

class Fconfig : public FstringHash
{

protected: // Protected attributes

// --------------------------------------\
// Properties                             >
// --------------------------------------/

  /** Name of the file conataining datas. */
  char fileName[ MAX_PATH];

  /** xml Document (tree).
      Pointer of the document tree. */
  xmlDocPtr doc;

  /** Pointer of the root node. */
  xmlNodePtr root;

  /** Pointer of the first node. */
  xmlNodePtr firstCurrent;

  /** Pointer of the current node. */
  xmlNodePtr current;

  /** List of all "current" pushed. */
  Flist stackCurrent;

	
// --------------------------------------\
// Methods                                >
// --------------------------------------/
	
  /** Search inside the tree (XML, LDAP or other tree). */
  long Search( char* name, bool subTree = true);

public:

  /** Constructor, reset default internal values. */
  Fconfig();

  /** Desctructor, call endXml. */
  ~Fconfig();

// -----------------------------------------------------
//  Start and end of the use of this "tree container".
// -----------------------------------------------------

  /**  Open the XML data file with FileName string and connect to the first Node. */
  long startXml( char* fileNameString);

  /** Open the data tree with the first Node of datas tree (config or others). */
  long startXml( void* node);

  /** Open a new tree of Datas  (config or others). */
  long startNewXml( char* fileNameString = NULL);

  /** Save (if needed) and close the file or the stream input data. */
  long endXml();

  /** Get the current node pointer. */
  void* getCurrent();

// -----------------------------------------------------
// Methods to move current node pointer to an another node 
// -----------------------------------------------------

  /** Reset the current pointer to the root of document (with fromRoot = true) or the first node defined with start(). */
  void resetCurrent( bool fromRoot = false);

  /** Push the Current position in the data tree to the stack. */
  void pushCurrent();

  /** Pop the Current position from the data tre of the stack. */
  void popCurrent();

  /** Go to the first node of the current branch. */
  long gotoFirst();

  /** Go to the last node of the current branch. */
  long gotoLast();

  /** Go to the next node of the current branch. */
  long gotoNext();

  /** Go to the previous node of the current branch. */
  long gotoPrev();

  /** Go to the children node of the current node. */
  long gotoChildren();

  /** Go to the parent node of the current node. */
  long gotoParent();

  /** Find a name, with or without tree recusivity. */
  long Find( char* name, bool subTree = true);

  /** Find next name, with or without tree recusivity. */
  long FindNext( char* name, bool subTree = true);

// -----------------------------------------------------
// Methods to get or set informations from the current node
// -----------------------------------------------------

  /** Get the Name of the current Node. */
  char* getNodeName();

  /** Set the Name of the current Node. */
  long setNodeName( char* name);

  /** Get the Content of the current Node. */
  char* getNodeContent();

  /** Set the Name of the current Node. */
  long setNodeContent( char* content);

// -----------------------------------------------------
// Methods to add/create or delete a node
// -----------------------------------------------------

  /** Create a new node (the current node is the parent). */
  long addChildren( char* name, char* content = NULL);

  /** Remove the current node (recursively). After remove goto the Previous Node or if the first where removed
      goto the next node. */
  long removeCurrent();

};

}	// namespace evenja

#endif

