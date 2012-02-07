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

#include "ClassFactory.h"
namespace pugi { class xml_node; }


namespace gul
{

/**
  * Here we have performSave and performLoad because we want to keep
  * Save and Load private. but in order to define the fiendship access to
  * the private Save and Load we need an additional class. The reason for that
  * is that the friendship relation is not inherited. Hence, we need to
  * access the private Save and Load via the common superclass XMLSerializable
  */
template<typename T>
class XMLSerializable : public gul::ClassRegisterer<T>
{
public:

    template<typename V> static void performSave(const V& v, pugi::xml_node& node, bool resetMode = false)
    {
      v.Save(node, resetMode);
    }

    template<typename V> static V* performLoad(const V& v, pugi::xml_node& node, bool resetMode = false)
    {
      return static_cast<V*>(v.Load(node, resetMode));
    }

private:
    virtual void Save(pugi::xml_node& node, bool resetMode) const = 0;
    virtual void* Load(const pugi::xml_node& node, bool resetMode) const = 0;

    friend class XMLManager;
};

}

#endif
