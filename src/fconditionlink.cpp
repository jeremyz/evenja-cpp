/***************************************************************************
                             fconditionlink.cpp
                             ------------------
    begin                : ven 2 oct 2009
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

#include "fconditionlink.h"

namespace evenja {

/** Constructor withour parameters. */
FconditionLink::FconditionLink() {}
	
/** 
 \param[in] linkSource Where the specialLink will apply.
 \param[in] linkTypeFieldsNames List of fields to generate a temporary value that need to be equal to [value] to apply the conditionLink.
 \param[in]	linkValue Value to compare with concatened [typeFields]'s values, to apply or not a conditionLink.
 \param[in]	linkFieldsNames	EvenData's fields to generate the linkValue for the rest of the room (if conditionLink apply).
 \param[in]	linkDestination	EvenData's destination, when conditionLink apply.
*/
FconditionLink::FconditionLink( char* linkSource, char* linkTypeFieldsNames, char* linkValue, char* linkFieldsNames, char* linkDestination)
{
	source.setString( linkSource);

  typeFields.setString( linkTypeFieldsNames);
  value.setString( linkValue);

  fields.setString( linkFieldsNames);
  destination.setString( linkDestination);
}

FconditionLink::~FconditionLink()
{
}

}  // end namespace evenja

