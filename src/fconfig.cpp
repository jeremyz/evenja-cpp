/***************************************************************************
                             fconfig.cpp
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

#include <string.h>

#include "fconfig.h"

#include <libxml/parser.h>

#include "evenjastrings.h"
#include "returncodes.h"


namespace evenja {

Fconfig::Fconfig() : FstringHash()
{
  doc = 0;
  root = 0;
  firstCurrent = 0;
  current = 0;
  fileName[ 0] = 0;
}

Fconfig::~Fconfig()
{
  endXml();
}

/** \param[in] fileNameString Filename in XML format to load a XML doc tree.
  \retval RET_OK No problemo.
  \retval RET_FILENAME2LONG Path and filename are longer than the MAX_PATH.
  \retval RET_CANNOTACCESS Error accessing the XML tree.
  \retval RET_NONODESELECTED Nothing found, content free.
  \retval RET_NONAME No name field in the first node.
  \retval RET_NOTEXIST First node not exist. */
long Fconfig::startXml( char* fileNameString)
{
  if( strlen( fileNameString) > MAX_PATH)      // Exit the famous overflow bug
    return RET_FILENAME2LONG;

  strcpy( fileName, fileNameString);          // Save data

  doc = xmlParseFile( fileName);        // Import the file information

  if( doc)
    return startXml( doc->children);
  else
    return RET_CANNOTACCESS;
}

/** \param[in] node Start a new XML tree with a node of another XML tree. The new XML tree start at the branch with this node parameter.
	\retval RET_OK No problemo.
  \retval RET_NONODESELECTED Nothing found, content free.
  \retval RET_NONAME No name field in the xml tree.
  \retval RET_NOTEXIST First node not exist. */
long Fconfig::startXml( void* node)
{
// Init values of this
  root = ( ( xmlNodePtr) node)->doc->children;
  firstCurrent = (xmlNodePtr) node;
  current = (xmlNodePtr) node;

// Find the name of this object
  if( gotoChildren() == RET_OK)
  {
    if( Find( XML_NAME, false) == RET_OK)
    {
      char *str = getNodeContent();
      if( str != ( char *) RET_NONODESELECTED)
      {
        setString( str);
        resetCurrent();
        return RET_OK;
      }
      else
        return RET_NONAME;
    }
    else
      return RET_NONAME;
  }
  else
    return RET_NOTEXIST;
}

/** \param[in] fileNameString Create a new XML tree 'connected' to the fileNameString. If empty, then juste create a new XML tree.
  \retval RET_OK No problemo.
  \retval RET_CANNOTCREATE Cannot create the xml file. */
long Fconfig::startNewXml( char* fileNameString)
{
  if( fileNameString)
  {
    if( strlen(fileNameString) > MAX_PATH)      // Exit the famous overflow bug
      return RET_FILENAME2LONG;

    strcpy( fileName, fileNameString);          // Save data
  }
  else  // No fileName => no save if call of method end
    fileName[ 0] = 0;


  doc = xmlNewDoc( (xmlChar*) XML_VERSION);      // Create the Tree
  xmlNewChild( ( xmlNodePtr) doc, NULL, (xmlChar*) XML_XML, NULL);
  root         = doc->children;            // No first node or root
  firstCurrent = root;                     // ...
  current      = root;                     // ...
  setString( TXT_NEW);        // new Tree

  if( doc)
    return RET_OK;
  else  
    return RET_CANNOTCREATE;
}

/** \retval RET_OK No problemo.
  \retval RET_CANNOTEND Cannot save the xml file. */
long Fconfig::endXml()
{
  long ret = RET_OK;

  if( doc && fileName[ 0])
    ret = xmlSaveFile( fileName, doc);

  if( ret == -1)
    return RET_CANNOTEND;
  else
  {
    if( doc)
      xmlFreeDoc( doc);

    doc = 0;
    root = 0;
    firstCurrent = 0;
    current = 0;
    fileName[ 0] = 0;

    return RET_OK;
  }
}

/** \retval node* pointer to the current node. */
void* Fconfig::getCurrent()
{
  return current;
}

// -------------------------------------------------------
// Methods to move current node pointer to a another nodes
// -------------------------------------------------------

/** \param[in] fromRoot Reset current position of node cursor. If fromRoot is true, then reset node cursor to root of the XML tree. If fromRoot is false, then current node cursor point the first evenja node. 
  \return No return value. */
void Fconfig::resetCurrent( bool fromRoot)
{
  if( fromRoot)       // if reset from the rooot then
    current = root;   // set current to the root of the tree
  else
    current = firstCurrent;
}

/** \return No return value. */
void Fconfig::pushCurrent()
{
  stackCurrent.add( current);
}

/** \return No return value. */
void Fconfig::popCurrent()
{
  if( stackCurrent.getCount())
    current = ( xmlNodePtr) stackCurrent.removeStack();
}

/** \retval RET_OK No problemo.
  \retval RET_NONODESELECTED No node currently selected. */
long Fconfig::gotoFirst()
{
  if( current)
  {
    current = current->parent->children;
    if( current->type != XML_ELEMENT_NODE)
      return gotoNext();
    else
      return RET_OK;
  }
  else
    return RET_NONODESELECTED;
}

/** \retval RET_OK No problemo.
  \retval RET_NONODESELECTED No node currently selected.*/
long Fconfig::gotoLast()
{
  if( current)
  {
    current = current->parent->last;
    if( current->type != XML_ELEMENT_NODE)
      return gotoPrev();
    else
      return RET_OK;
  }
  else
    return RET_NONODESELECTED;
}

/** \retval RET_OK No problemo.
  \retval RET_NOTEXIST Next node not exist.
  \retval RET_NONODESELECTED No node currently selected.*/
long Fconfig::gotoNext()
{
  if( current)
  {
    if( current->next)
    {
      xmlNodePtr currentW = current->next;
      while( currentW->type != XML_ELEMENT_NODE && currentW->next)
        currentW = currentW->next;

      if( currentW->type == XML_ELEMENT_NODE)
      {
        current = currentW;
        return RET_OK;
      }
      else
        return RET_NOTEXIST;
    }
    else
      return RET_NOTEXIST;
  }
  else
    return RET_NONODESELECTED;
}

/** \retval RET_OK No problemo.
  \retval RET_NOTEXIST Prev node not exist.
  \retval RET_NONODESELECTED No node currently selected.*/
long Fconfig::gotoPrev()
{
  if( current)
  {
    if( current->prev)
    {
      xmlNodePtr currentW = current->prev;
      while( currentW->type != XML_ELEMENT_NODE && currentW->prev)
        currentW = currentW->prev;

      if( currentW->type == XML_ELEMENT_NODE)
      {
        current = currentW;
        return RET_OK;
      }
      else
        return RET_NOTEXIST;
    }
    else
      return RET_NOTEXIST;
  }
  else
    return RET_NONODESELECTED;
}

/** \retval RET_OK No problemo.
  \retval RET_NOTEXIST Children node not exist.
  \retval RET_NONODESELECTED No node currently selected. */
long Fconfig::gotoChildren()
{
  if( current)
  {
    if( current->children)
    {
      current = current->children;
      if( current->type != XML_ELEMENT_NODE)
      {
        long ret = gotoNext();
        if( ret == RET_NOTEXIST)
          gotoParent();
        return ret;
      }
      else 
        return RET_OK;
    }
    else
      return RET_NOTEXIST;
  }
  else
    return RET_NONODESELECTED;
}

/** \retval RET_OK No problemo.
  \retval RET_NOTEXIST Parent node not exist.
  \retval RET_NONODESELECTED No node currently selected.*/
long Fconfig::gotoParent()
{
  if( current)
  {
    if( current->parent)
    {
      current = current->parent;
      if( current->type != XML_ELEMENT_NODE)
        return gotoPrev();
      else
        return RET_OK;
    }
    else
      return RET_NOTEXIST;
  }
  else
    return RET_NONODESELECTED;
}

/** \param[in] name Search 'name' node in the XML tree.
  \param[in] subTree Search in the subtree nodes too.
  \retval RET_OK No problemo, current node cursor point the node equal to name.
  \retval RET_NOTFOUND Nothing found with this name. */
long Fconfig::Search( char* name /* Name of the tree node to found. */, bool subTree)
{
  char *str;
  long ret = RET_KO;
  bool found = false;

  xmlNodePtr bkpCurrent = current;    // Backup of the current position

  do{
    str = getNodeName();
    if( str != ( char*) RET_NONODESELECTED)	// If no node are selected...
    {
      found = !strcasecmp( name, str);		// check if found
      if( !found && subTree && current->children)    // if not found and node contain a children then go to children level
      {
        ret = gotoChildren();
        if( ret == RET_OK)
        {
          ret = Search( name, subTree);
          if( ret == RET_NOTFOUND)
            gotoParent();
          else
            found = ( ret == RET_OK);
        }
      }
    }
  }while( !found && !( ret = gotoNext()));  

  if( found) // If something found ...
    return RET_OK;
  else  // else nothing found
  {
    current = bkpCurrent;
    return RET_NOTFOUND;
  }
}

/** \param[in] name Find 'name' node in the XML tree.
	\param[in] subTree Search in the subtree nodes too.
  \retval RET_OK No problemo, current node cursor point the node equal to name.
  \retval RET_NOTFOUND Nothing found with this name.
  \retval RET_NONODESELECTED No node currently selected. */
long Fconfig::Find( char* name, bool subTree)
{
  long ret;
  if( !( ret = gotoFirst())) // Begin at the start of the branch
    return Search( name, subTree);
  else
    return ret;
}

/** \param[in] name Find next 'name' node in the XML tree.
	 \param[in] subTree Search in the subtree nodes too.
  \retval RET_OK No problemo, current node cursor point the node equal to name.
  \retval RET_NOTFOUND Nothing found with this name.
  \retval RET_NONODESELECTED No node currently selected. */
long Fconfig::FindNext( char* name, bool subTree)
{
  long ret;

  if( !( ret = gotoNext()))
    return Search( name, subTree);
  else
    return ret;
}

// --------------------------------------------------------
// Methods to get or set informations from the current node
// --------------------------------------------------------

/** \retval char* name of the current node.
  \retval RET_NONODESELECTED No node currently selected. */
char* Fconfig::getNodeName()
{
  if( current)
    return (char*) current->name;
  else
    return ( char*) RET_NONODESELECTED;
}

/** \param[in] name Set the current node name.
  \retval RET_OK No problemo.
  \retval RET_NONODESELECTED No node currently selected. */
long Fconfig::setNodeName( char* name)
{
  if( current)
  {
    xmlNodeSetName( current, (xmlChar*) name);
    return RET_OK;
  }
  else
    return RET_NONODESELECTED;
}

/** \retval char* content of the current node.
  \retval TXT_NULL current nodedo not have content.
  \retval RET_NONODESELECTED No node currently selected. */
char* Fconfig::getNodeContent()
{
  if( current)
  {
    xmlNodePtr currentA = current->children;
    if( currentA)
      return ( char*) currentA->content;
    else
      return TXT_NULL;
  }
  else
    return ( char*) RET_NONODESELECTED;
}

/** \param[in] content Set the current node content.
  \retval RET_OK No problemo.
  \retval RET_NONODESELECTED No node currently selected. */
long Fconfig::setNodeContent( char* content)
{
  if( current)
  {
    if( content)
      xmlNodeSetContent( current, (xmlChar*) content);
    else
      xmlNodeSetContent( current, (xmlChar*) TXT_NULL);

    return RET_OK;
  }
  else
    return RET_NONODESELECTED;
}


// ----------------------------------
// Methods to create or delete a node
// ----------------------------------

/** \param[in] name Name of the new node.
  \param[in] content Content of the new node.
  \retval RET_OK No problemo.
  \retval RET_NONODESELECTED No node currently selected. */
long Fconfig::addChildren( char* name, char* content)
{
  if( current)
  {
    xmlNewChild( current, NULL, (xmlChar*) name, content ? (xmlChar*) content : NULL);

    if( doc && !root)
    {
      root         = doc->children;            // No first node or root
      firstCurrent = root;                     // ...
      current      = root;                     // ...
    }

    return RET_OK;
  }
  else
    return RET_NONODESELECTED;  
}

/** \retval RET_OK No problemo.
  \retval RET_NONODESELECTED No node currently selected. */
long Fconfig::removeCurrent()
{
  char *str;
  
  str = getNodeName();
  if( str != ( char*) RET_NONODESELECTED)
  {
    if( strcasecmp( XML_XML, str))    // Not erase the first level (tag XML)
    {
      xmlNodePtr toRemove = current;

      if( current->prev)              // if previous exist, then go to it
        gotoPrev();
      else if( current->next)         // ...otherwise if next exist, go to it
        gotoNext();
      else if( current->parent)
        gotoParent();                 // ...otherwise if parent exist, go to it

      if( root == toRemove || firstCurrent == toRemove
          || root->doc->children == toRemove)
      {
        root = 0;
        firstCurrent = 0;
        current = 0;
      }

      xmlUnlinkNode( toRemove);
      xmlFreeNode( toRemove);
    }
    return RET_OK;
  }
  else
    return RET_NONODESELECTED; 
}

} // namespace evenja
