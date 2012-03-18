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

#include "Misc.h"

namespace pugi { class xml_node; }


namespace gul
{

/**
  * Here we have performSave and performLoad because we want to keep
  * Save and Load private. but in order to define the fiendship access to
  * the private Save and Load we need an additional class. The reason for that
  * is that the friendship relation is not inherited. Hence, we need to
  * access the private Save and Load via the common superclass XMLSerializable
  *
  * Here we need to solve the Loading via virtual inheritance because of the case
  * when class A : public B and we want to store A* with a dynamic B. Here we generate
  * a B (through the macros) and call Load. However we only know at compile time that
  * we will get something of type A. As a result we cannot use template functions
  * for loading as we need to know the template type at compile time. The save
  * story is with regular function overloading. Hence, we need to exploit virtual
  * inheritance.
  */
class XMLSerializable
{
public:

    template<typename T>
    static void performSave(T const& v, pugi::xml_node& node, bool resetMode = false)
    {
      v.Save(node, resetMode);
    }


    template<typename T>
    static void performSave(T* const& v, pugi::xml_node& node, bool resetMode = false)
    {
      performSave(*v, node, resetMode);
    }


    template<typename T> static T* performLoad(T const& v, pugi::xml_node& node, bool resetMode = false)
    {
      return static_cast<T*>(v.Load(node, resetMode));
    }

    template<typename T> static T** performLoad(T* const& v, pugi::xml_node& node, bool resetMode = false)
    {
      return new T*(performLoad(*v, node, resetMode));
    }

    template<typename T> static void deleteLoaderObject(T*& v)
    {
      GUL_DELETE(v);
    }

    template<typename T> static void deleteLoaderObject(T**& v)
    {
      GUL_DELETE(*v);
      GUL_DELETE(v);
    }


private:
    virtual void Save(pugi::xml_node& node, bool resetMode) const = 0;
    virtual void* Load(const pugi::xml_node& node, bool resetMode) const = 0;

    friend class XMLManager;
};

}


#endif
