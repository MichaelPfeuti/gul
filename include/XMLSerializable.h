#pragma once
#ifndef _GUL_PERSISTANCE_XML_SERIALIZABLE_H_
#define _GUL_PERSISTANCE_XML_SERIALIZABLE_H_
/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011 Michael Pfeuti.
**
** Contact: Michael Pfeuti (mpfeuti@ganymede.ch)
**
**
** gul is free software: you can redistribute it and/or modify it under the
** terms of the GNU Lesser General Public License as published by the Free
** Software Foundation, either version 3 of the License, or (at your option)
** any later version.
**
** gul is distributed in the hope that it will be useful, but WITHOUT ANY
** WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
** FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
** more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with gul. If not, see <http://www.gnu.org/licenses/>.
**
**
** If you have questions regarding the use of this file, please contact
** Michael Pfeuti at mpfeuti@ganymede.ch.
**
***************************************************************************/

#include <3rdParty/pugi/pugixml.hpp>

namespace gul
{

/** this enforces that saved is initially false */
class XMLSerializable
{
protected:
    XMLSerializable(void) : __saved (false) {}
    mutable bool __saved;
public:
    virtual void Save(pugi::xml_node& node, bool resetMode = false) const = 0;
    virtual void* Load(const pugi::xml_node& node, bool resetMode = false) const = 0;
};

}

#endif
