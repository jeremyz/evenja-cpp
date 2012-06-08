/***************************************************************************
                             fstarter.cpp
                             ------------
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

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#include "fstarter.h"
#include "returncodes.h"
#include "evenjastrings.h"


namespace evenja {

bool Fstarter::exitApp = false;

Fstarter::Fstarter() : Frouter() {}

Fstarter::~Fstarter() {}

/** \param[in] fileNameString Filename in XML format to load a XML doc tree.
	\retval RET_OK No problemo.
	\retval RET_FILENAME2LONG Path and filename are longer than the MAX_PATH.
	\retval RET_CANNOTACCESS Error accessing the XML tree.
	\retval RET_NONODESELECTED Nothing found, content free.
	\retval RET_NONAME No name field in the first node.
	\retval RET_NOTEXIST First node not exist.
	\retval RET_NOINFOS No configuration informations to process. */
long Fstarter::start( char *fileNameString)
{
  long ret = Frouter::start( NULL, fileNameString);

  if( ret == RET_OK)
  {
    pushCurrent();
    server = !Find( XML_SERVER);
    popCurrent();
  }

  return ret;
}

/** \retval RET_OK No problemo... do you know a software allways working ;). */
long Fstarter::execute()
{
  FevenData* data;
  /** If it is a server then wait for an exitApp message, otherwise exit immediately */
  do
  {
    while( listMsgSys.getCount() || listMsg.getCount())
    {
      if( listMsgSys.getCount())
      {
        data = ( FevenData*) listMsgSys.removeFifo();
        ( ( Fport*) data->getActivePort())->justDoItSys( data);
      }
      else
      {
        data = ( FevenData*) listMsg.removeFifo();
        ( ( Fport*) data->getActivePort())->justDoIt( data);
      }
    }
  }while( server && !exitApp);

  return RET_OK;
}

/** \retval RET_OK No problemo.
	\retval RET_CANNOTEND Cannot save the xml file. */
long Fstarter::end()
{
  return Frouter::end();
}

}   // namespace evenja
