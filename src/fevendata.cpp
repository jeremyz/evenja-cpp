/***************************************************************************
                             fevendata.cpp
                             -------------
    begin                : sam nov 2 2002
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

#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "returncodes.h"  
#include "fevendata.h"

namespace evenja {

FstringHash EVENDATA_BASE( ( char*) "EVENDATA_BASE");

FevenData::FevenData() : Fconfig()
{
// init local values
  startToUse = 0;
  currentDestination = 0;
  xmlBuffer = 0;

// Prepar to receive other evenDatas merged with this
  listEvenDataB = new Flist();

// Use the base template to start.
  evenDataClass.copyFrom( &EVENDATA_BASE);

  ptrWorkStart  = TXT_NULL;

  initDatas();
}

FevenData::~FevenData()
{
// if there is a xml tree, then delete all the xml tree.
  if( xmlBuffer)
    xmlFree( xmlBuffer);

// delete all eventData merged list, but not the evenDatas themself.
  resetEvenDataB( false);
  delete listEvenDataB;

// Close all.
  reset();
  endXml();
}

/** \param[in] separator Character that indicate the end of a string inside parameter [string].
  \param[in] string Contain the the full string to  seperate in smaller strings. If no [string] parameter, search the next occurence in the previously given [string] paramter.
  \retval NULL nothing found.
  \retval other_pointer_value pointer to the splitted string or next string, end by a 0.
  \retval RET_STRING2LONG string is longer than MAX_STRING. */
char* FevenData::getSplitted( char separator, char* string)
{
  char* ret;

  if( *string) // If a string is transmitted ?
  { // ... then make a copy to the local buffer
    if( strlen( string) < MAX_STRING)
       strcpy( splitBuffer, string);
    else
      return (char*) RET_STRING2LONG; 

    ptrWorkStart  = splitBuffer;
  }

  if( *ptrWorkStart) // if something to do ? ... work on it
  {
    ptrWorkEnd = strchr( ptrWorkStart, separator); // search the next separator

    ret = ptrWorkStart;

    if( ptrWorkEnd) // Something found ?
    {
      *ptrWorkEnd = 0;  // Yes then convert the End in end of string.

      ptrWorkStart = ptrWorkEnd;  // Prepare the next search
      ptrWorkStart++;
    }
    else // If nothing found to split jump to the last caracter 0
      ptrWorkStart += strlen( ptrWorkStart);

    return ret;
  }
  else // Nathing else to split
    return 0;

}

/** \param[in] name Path name of the node to set the current cursor to.
  \param[in] create If true and not found create the node name. If false and node name not found return RET_NOTFOUND.
  \param[in] onlyDatas If true search only in the datas part of the XML tree. If false, search from the root of the XML tree.
  \retval RET_OK No problemo, tag name found.
  \retval RET_STRING2LONG Node name path string is longer than MAX_STRING.
  \retval RET_NOTFOUND Node name not found in the data tree. */
long FevenData::gotoNodeName( char* name, bool create, bool onlyDatas)
{
  char* str;
  long ret = RET_OK;

  str = getSplitted( TREE_SEPARATOR, name);
  if( (long) str == RET_STRING2LONG)
    return RET_STRING2LONG;

  if( onlyDatas)
    current = datas;
  else
    current = root;

  while( str)
  {
    ret = gotoChildren();
    if( ret == RET_NOTEXIST && create)  // If childrens not exist then create it, if create true
    {
      addChildren( str, NULL);
      gotoChildren();
    }
    else if( ret == RET_NOTEXIST && !create)	// if no sub trees and crate false...
      return RET_NOTFOUND;

    ret = Find( str, false);           // Find the tag name ?
    if( ret == RET_NOTFOUND && create)
    {
      gotoParent();
      addChildren( str, NULL);
      gotoChildren();

      Find( str, false);
    }
    else if( ret == RET_NOTFOUND && !create)
      return RET_NOTFOUND;

    str = getSplitted( TREE_SEPARATOR);
  }

  return RET_OK;
}

//----------------------------- MACROS FOR getMetaDatasToXml ---------------
#define GETMETADATA( AAA, BBB)   ret = gotoNodeName( AAA, false, false); \
                                 if( ret == RET_OK)                     \
                                   BBB( getNodeContent());

#define GETMETADATAINT( AAA, BBB)   ret = gotoNodeName( AAA, false, false); \
                                    if( ret == RET_OK)                     \
                                      BBB = atoi( getNodeContent());

/** \return No return value. */
void FevenData::getMetaEvenDatasFromXml()
{
  long ret = 0;
  long nbDest;
  char b[ MAX_STRING];
  char f[ MAX_STRING];

  GETMETADATA( XML_SOURCE, setSource);

  GETMETADATAINT( XML_STARTTIME, startToUse);

  strcpy( b, XML_DESTINATION); strcat( b, TREE_SEPARATOR_STR); strcat( b, XML_DESTCOUNT);
  GETMETADATAINT( b, nbDest);

  strcpy( b, XML_DESTINATION); strcat( b, TREE_SEPARATOR_STR); strcat( b, XML_CURRENTDEST);
  GETMETADATAINT( b, currentDestination);

  for( long i = 0; i < nbDest; i++)
  {
    strcpy( f, XML_DESTINATION);
    strcat( f, TREE_SEPARATOR_STR);
    strcat( f, XML_DESTNUMBER);
    sprintf( b, f, i);
    GETMETADATA( b, addDestination);
  }

  GETMETADATA( XML_LINKFIELDS, setLinkFieldsNames);
}

//----------------------------- MACROS FOR setMetaDatasToXml ---------------
#define SETMETADATA( AAA, BBB)   gotoNodeName( AAA, true, false); \
                                 setNodeContent( BBB);

#define SETMETADATAINT( AAA, BBB)   gotoNodeName( AAA, true, false); \
                                    sprintf( b, "%ld", BBB);                \
                                    setNodeContent( b);

/** \return No return value. */
void FevenData::setMetaEvenDatasToXml()
{
  char b[ MAX_STRING];
  char f[ MAX_STRING];

  SETMETADATA( XML_SOURCE, ( ( char*) source.getString()));

  SETMETADATAINT( XML_STARTTIME, startToUse);

  gotoNodeName( XML_DESTINATION, true, false);

  strcpy( b, XML_DESTINATION); strcat( b, TREE_SEPARATOR_STR); strcat( b, XML_DESTCOUNT);
  SETMETADATAINT( b, destination.getCount());

  strcpy( b, XML_DESTINATION); strcat( b, TREE_SEPARATOR_STR); strcat( b, XML_CURRENTDEST);
  SETMETADATAINT( b, currentDestination);

  for( long i = 0; i < destination.getCount(); i++)
  {
    strcpy( f, XML_DESTINATION);
    strcat( f, TREE_SEPARATOR_STR);
    strcat( f, XML_DESTNUMBER);
    sprintf( b, f, i);
    SETMETADATA( b, ( ( char*) ( ( FstringHash*) destination.get( i))->getString()));
  }

  // Transfer all the linkFieldsNames to a single string
  b[ 0] = 0;
  for( long i = 0; i < linkFieldsNames.getCount(); i++)
  {
    strcat( b, ( ( FstringHash *) linkFieldsNames.get( i))->getString());
    strcat( b, FIELD_SEPARATOR_STR);
  }
  if( b[ 0])
    b[ strlen(b) - 1] = 0; // remove the last FIELD_SEPARATOR

  SETMETADATA( XML_LINKFIELDS, b);
}

/** \param[in] newDoc XML document to define as the XML tree of this FevenData.
  \retval RET_OK No problemo.
  \retval RET_CANNOTACCESS Error accessing the XML tree, or parameter is void.
  \retval RET_NONODESELECTED Nothing found, content free.
  \retval RET_NONAME No name field in the first node.
  \retval RET_NOTEXIST First node not exist. */
long FevenData::setDatasFromXml( xmlDocPtr newDoc)
{
  long ret = RET_OK;

  if( newDoc)
  {
    // Erase all existing datas
    endXml();
    doc = newDoc;

    ret = startXml( doc->children);

    // init the datas node pointer
    resetCurrent();
    gotoChildren();
    Find( XML_DATAS, false);
    datas = current;

    // Get MetaDatas
    getMetaEvenDatasFromXml();
    updateHashValue();

    return ret;
  }
  else
    return RET_CANNOTACCESS;
}

/** \param[in] fieldName If exist in the linkFieldsName or is NULL, FevenData's hashValue will be updated.  
  \return No return value. */
void FevenData::updateHashValue( char* fieldName)
{
  bool update = false;

  if( fieldName)  // IF a field exist then search in the table if the same exist
  {
    for( long i = 0; i < linkFieldsNames.getCount(); i++)
    {
      if( !strcasecmp( ( ( FstringHash*) linkFieldsNames.get( i))->getString(), fieldName))
        update = true;
    }
  }
  else
    update = true;

  if( update) // if something exist
  {
    xmlNodePtr bkpCurrent = current;

    char b[ MAX_STRING];
    long l = 0;
  	  b[ 0] = 0;
    char* value;
    long nbExist = 0;
    for( long i = 0; i < linkFieldsNames.getCount(); i++)
    {
      value = getData( (char*) ( ( FstringHash*) linkFieldsNames.get( i))->getString());
      long j = 0;
      if( (long) value != RET_NOTFOUND)
      {
        while( ( value[ j]) && ( b[ l++] = value[ j++]) && ( l < MAX_STRING));
        b[ l] = 0;
        nbExist++;
      }
    }

    if( nbExist == linkFieldsNames.getCount())
      setString( b);
    else
      setString( TXT_NOVALUES);

    current = bkpCurrent;
  }
}

/** \param[in] sourceString Set the source of the FevenData.
  \retval RET_OK Source position OK
  \retval RET_STRING2LONG Source position string to long. */
long FevenData::setSource( char* sourceString)
{
  return source.setPosition( sourceString);
}

/** \return Pointer to a Fposition class containing the source. */
Fposition * FevenData::getSource()
{
  return &source;
}

/** \param[in] destinationString Set the destination of the FevenData. Can be many destinations, separated by DESTINATION_SEPARATOR.
	\retval RET_OK Destination added correctly.
  \retval RET_MEMORYSPACE No more memory space. */
long FevenData::addDestination( char* destinationString)
{
  long ret = RET_OK;

  char * str = getSplitted( DESTINATION_SEPARATOR, destinationString);

  while( str && ( ret == RET_OK))
  {
    evenja::Fposition *pos = new evenja::Fposition();

    pos->setPosition( str);

    ret = destination.add( pos);

    str = getSplitted( DESTINATION_SEPARATOR);
  }

  return ret;
}

/** \retval true there is some other destinations.
  \retval false no more destination for this evenData. */
bool FevenData::haveDestination()
{
  return ( destination.getCount() && ( currentDestination < destination.getCount()));
}

/** \retval RET_KO no current destination found.
  \retval Fposition_pointer pointer to the current Fposition destination. */
Fposition* FevenData::getCurrentDestination()
{
  if( destination.getCount())
    return ( Fposition*) destination.get( currentDestination);
  else
    return ( Fposition*) RET_KO;
}

/** \retval RET_OK Current destination exist and is pointed in this evenData.
  \retval RET_NOTEXIST No next destinations exit. */
long FevenData::selectNextDestination()
{
  if( currentDestination + 1 < destination.getCount())
  {
    currentDestination++;
    activePort = 0;
    return RET_OK;
  }
  else
    return RET_NOTEXIST;
}

/** \return No return values. */
void FevenData::resetDestinations()
{
  evenja::Fposition *pos;

  long nbDest = destination.getCount();

  for( long i = 0; i < nbDest; i++)
  {
    pos = ( Fposition*) destination.remove( (long) 0);

    delete pos;
  }

  currentDestination = 0;
}

/** \param[in] port Set the port for the next sendEvendata operation.
  \return No return value. */
void FevenData::setActivePort( void* port)
{
  activePort = port;
}

/** \return Pointer to the active instance of the inherited object of FPort. */
void* FevenData::getActivePort()
{
  return activePort;
}

/** \param[in] action Set the action name to do when arrive in the port.
  \param[in] portName Set the port name to go to. If NULL and no destinations, a FconditionLink will apply.
  \retval RET_OK No problemo.
  \retval RET_STRING2LONG To long string 'linkFieldsNames'. */
long FevenData::setPortAction( char* action, char* portName)
{
  char b[ MAX_STRING];
  long l = 1;

  if( portName)
    l += strlen( portName);

  l += strlen( action);

  if( l > MAX_STRING)
    return RET_STRING2LONG;

  if( portName)
    strcpy( b, portName);
  else
    b[ 0] = 0;

  if( l)
  {
    strcat( b, ":");
    strcat( b, action);
  }

  addDestination( b);

  if( destination.getCount())
    currentDestination = destination.getCount() - 1;
  else
    currentDestination = 0;

  return RET_OK;
}

/** \param[in] linkFieldsNamesString Set the list of fields names that will generate de hashValue, to link with another FevenData.
  \retval RET_OK Set the fileds or tags names OK.
  \retval RET_STRING2LONG To long string 'linkFieldsNames'. */
long FevenData::setLinkFieldsNames( char* linkFieldsNamesString)
{
  FstringHash* strH1;
  char* str;

  str = getSplitted( FIELD_SEPARATOR, linkFieldsNamesString);
  if( (long) str == RET_STRING2LONG)
    return RET_STRING2LONG;

	// If already something, then clear them
  if( linkFieldsNames.getCount())
    resetLinkFieldsNames();

	// Transfer the fields names
  while( str)
  {
    strH1 = new FstringHash();
    strH1->setString( str);

    linkFieldsNames.add( strH1);

    str = getSplitted( FIELD_SEPARATOR);
  }

  updateHashValue();

  return RET_OK;
}

/** \return No return value. */
void FevenData::resetLinkFieldsNames()
{
  FstringHash* str1;

  long nbString = linkFieldsNames.getCount();

  for( long i = 0; i < nbString; i++)
  {
    str1 = ( Fposition*) linkFieldsNames.remove( (long) 0);

    delete str1;
  }
}

/** \retval time_t structure containing the creation time of the evenData. Precision "millisecond". */
time_t FevenData::getStartToUse()
{
  return startToUse;
}

/** \param[in] evenData FevenData to add in the listEvenDataB.
  \return No return value. */
void FevenData::addEvenDataB( FevenData* evenData)
{
  listEvenDataB->add( evenData);
}

/** \ param[in] idx Index of the FevenDataB to return.
  \retval RET_NOTEXIST Pointer to the RET_NOTEXIST value. 
  \retval other_pointer_value The asked evenDataB pointer. */
FevenData* FevenData::getEvenDataB( long idx)
{
  return ( FevenData *) listEvenDataB->get( idx);
}

/** \param[in] idx Index of the FevenDataB to remove and return.
  \retval RET_NOTEXIST Pointer to the RET_NOTEXIST value. 
  \retval other_pointer_value The asked evenDataB pointer. */
FevenData* FevenData::removeEvenDataB( long idx)
{
  return ( FevenData *) listEvenDataB->remove( (long) idx);
}

/** \retval Number of elements evenDataB currently merged with this evenData. */
long FevenData::getCountEvenDataB()
{
  return listEvenDataB->getCount();
}

/** \param[in] del If true remove FevenDataBs from listEvenDataB AND delete them. If false, only remove from the list AND not delete.
   \return No return value. */
void FevenData::resetEvenDataB( bool del)
{
  if( listEvenDataB->getCount())
  {
     FevenData * evenData;
	   if( del)
	   while( listEvenDataB->getCount())
	   {
	     evenData = ( FevenData *) listEvenDataB->remove( (long) 0);
         delete evenData;
	   }
	 else
	   while( listEvenDataB->getCount())
	     listEvenDataB->remove( (long) 0);
  }
}

/** \param[in] nodeName Node name path to set the content.
  \param[in] value Content to set at the node name path.
  \retval RET_OK No problemo, value set.
  \retval RET_STRING2LONG Node name path string is longer than MAX_STRING.
  \retval RET_NOTFOUND Node name not found in the data tree. */
long FevenData::setData( char* nodeName, char* value)
{
  long ret = gotoNodeName( nodeName);

  if( ret == RET_OK)
  {
    ret = setNodeContent( value);
    updateHashValue( nodeName);
  }

  return ret;
}

/** \param[in] nodeName Node name path to return the content.
  \retval char* content of the current node.
  \retval TXT_NULL current nodedo not have content.
  \retval RET_NONODESELECTED No node currently selected.
  \retval RET_STRING2LONG Node name path string is longer than MAX_STRING.
  \retval RET_NOTFOUND Node name not found in the data tree. */
char * FevenData::getData( char* nodeName)
{
  long ret = gotoNodeName( nodeName, false);

  if( ret == RET_OK)
    return getNodeContent();
  else
    return ( char*) ret;
}

	/** \param[in] nodeName Node name path to set the content (long).
	 \param[in] value Content (long) to set at the node name path.
  \retval RET_OK No problemo, value set.
  \retval RET_STRING2LONG Node name path string is longer than MAX_STRING.
  \retval RET_NOTFOUND Node name not found in the data tree. */
long FevenData::setDataLong( char *nodeName, long value)
{
  char b[ MAX_STRING];

  long ret = gotoNodeName( nodeName);

  sprintf( b, "%ld", value);

  if( ret == RET_OK)
  {
    ret = setNodeContent( b);
    updateHashValue( nodeName);
  }

  return ret;
}

/** \param[in] nodeName Node name path to return the content (long).
  \retval int_value content of the current node.
  \retval TXT_NULL current nodedo not have content.
  \retval RET_NONODESELECTED No node currently selected.
  \retval RET_STRING2LONG Node name path string is longer than MAX_STRING.
  \retval RET_NOTFOUND Node name not found in the data tree. */
long FevenData::getDataLong( char *nodeName)
{
  long ret = gotoNodeName( nodeName, false);

  if( ret == RET_OK)
    return atol( getNodeContent());
  else
    return ret;
}

/** \param[in] stringXML String containing the XML tree in a string format.
  \retval RET_OK No problemo.
  \retval RET_CANNOTACCESS Error accessing the XML tree, or parameter is void.
  \retval RET_NONODESELECTED Nothing found, content free.
  \retval RET_NONAME No name field in the first node.
  \retval RET_NOTEXIST First node not exist. */
long FevenData::setDatasFromString( char *stringXML)
{
  return setDatasFromXml( xmlParseMemory( string, (int)strlen( string)));
}

/** \param[in] fileNameString Set XML tree from a XML file.
  \retval RET_OK No problemo.
  \retval RET_FILENAME2LONG FileName is too long > MAX_PATH.
  \retval RET_CANNOTACCESS Error accessing the XML tree, or parameter is void.
  \retval RET_NONODESELECTED Nothing found, content free.
  \retval RET_NONAME No name field in the first node.
  \retval RET_NOTEXIST First node not exist. */
long FevenData::setDatasFromFile( char* fileNameString)
{
  if( strlen( fileNameString) > MAX_PATH)      // Exit the famous overflow bug
    return RET_FILENAME2LONG;

  return setDatasFromXml( xmlParseFile( fileNameString));
}

/** \retval char* XML tree in a string. */
char* FevenData::getDatasToString()
{
  if( xmlBuffer)
    xmlFree( xmlBuffer);

  setMetaEvenDatasToXml();

  int len;
  xmlDocDumpMemory( doc, &xmlBuffer, &len);
  xmlBuffer[ len] = 0;

  return (char*) xmlBuffer;
}

/** \param[in] fileNameString Export XML tree to this fileNameString. 
   \retval RET_OK No problemo, XML tree saved to a file.
   \retval RET_FILENAME2LONG FileName is too long > MAX_PATH.
   \retval RET_CANNOTSAVE Cannot save to the XML file.*/
long FevenData::getDatasToFile( char* fileNameString)
{
  if( strlen( fileNameString) > MAX_PATH)      // Exit the famous overflow bug
	return RET_FILENAME2LONG;

  setMetaEvenDatasToXml();

  long ret = xmlSaveFile( fileName, doc);

  if( ret == -1)
    return RET_CANNOTSAVE;
  else
    return RET_OK;
}

/** \param[in] data Copy and XML tree from another FevenData.
  \retval RET_OK No problemo.
  \retval RET_CANNOTACCESS Error accessing the XML tree, or parameter is void.
  \retval RET_NONODESELECTED Nothing found, content free.
  \retval RET_NONAME No name field in the first node.
  \retval RET_NOTEXIST First node not exist. */
long FevenData::copyFrom( FevenData* data)
{
  return setDatasFromString( data->getDatasToString());;
}

/** \retval stringHash* Hash value of the type. */
FstringHash* FevenData::isA()
{
  return &evenDataClass;
}

/** \return No return value. */
void FevenData::initDatas()
{
// if it is a base evendata, then start initiating evenData
  if( isA()->equals( &EVENDATA_BASE))
  {
    startNewXml();

    addChildren( XML_DATAS, NULL);

    gotoChildren();
    Find( XML_DATAS, false);
    datas = current;

    setString( TXT_NOVALUES);
  }
}


/** \return No return value. */
void FevenData::reset()
{
// Erase the source
  source.setString( TXT_NULL);

// reset the time to be born or reborn or reborn .... recycling is more natural ;)
  time( &startToUse);

// erase the list of destinations
  resetDestinations();

// erase the link Fields Names
  resetLinkFieldsNames();

// erase evenDataB
  resetEvenDataB();

// erase all datas
  endXml();
  initDatas();          
}

/** \retval evenData* new instance of this type of FevenData. */
FevenData* FevenData::createInstance()
{
  return new FevenData();
}

}   // namespace evenja
