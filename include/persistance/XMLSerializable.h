#pragma once
#ifndef _GUL_PERSISTANCE_XML_SERIALIZABLE_H_
#define _GUL_PERSISTANCE_XML_SERIALIZABLE_H_
/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011, 2012 Michael Pfeuti.
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
** FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for
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
#include "String.h"
#include "MapBasic.h"
#include "ClassFactory.h"
#include "XMLNode.h"

namespace pugi
{
  class xml_node;
}


#define PRIM_PERFORM_SAVE(TYPE) \
  static void performSave(TYPE const& v, gul::XMLNode& node) \
  { \
    node.SetName(gul::String(#TYPE));\
    if(savingReferences.Contains(&v)) \
    { \
      node.AppendAttribute(refTag).SetValue(savingReferences.Get(&v)); \
    } \
    else \
    { \
      node.AppendAttribute(refIndexTag).SetValue(savingReferences.Size()); \
      savingReferences.Add(&v, savingReferences.Size()); \
      node.AppendAttribute(gul::String("value")).SetValue(v); \
    } \
  }

#include <cstdio>

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
    *
    * CAUTION: When saving a local variable exp. in a loop, it changes its values
    *          but this values won't be saved because it has the same address
    *          and is regarded as the same, hence we store the reference for later calls.
    */
  class GUL_EXPORT XMLSerializable
  {
    protected:

      PRIM_PERFORM_SAVE(bool)
      PRIM_PERFORM_SAVE(char)
      PRIM_PERFORM_SAVE(int)
      PRIM_PERFORM_SAVE(unsigned int)
      PRIM_PERFORM_SAVE(float)
      PRIM_PERFORM_SAVE(double)
      PRIM_PERFORM_SAVE(gul::String)

      static void performLoad(bool& v, const gul::XMLNode& node)
      {
        v = node.GetAttribute(gul::String("value")).GetBool();
      }

      static void performLoad(char& v, const gul::XMLNode& node)
      {
        v = static_cast<char>(node.GetAttribute(gul::String("value")).GetInt());
      }

      static void performLoad(int& v, const gul::XMLNode& node)
      {
        v = node.GetAttribute(gul::String("value")).GetInt();
      }

      static void performLoad(unsigned int& v, const gul::XMLNode& node)
      {
        v = node.GetAttribute(gul::String("value")).GetUnsignedInt();
      }

      static void performLoad(float& v, const gul::XMLNode& node)
      {
        v = node.GetAttribute(gul::String("value")).GetFloat();
      }

      static void performLoad(double& v, const gul::XMLNode& node)
      {
        v = node.GetAttribute(gul::String("value")).GetDouble();
      }

      static void performLoad(gul::String& v, const gul::XMLNode& node)
      {
        v = node.GetAttribute(gul::String("value")).GetString();
      }

      template<typename T>
      static void performSave(T const& v, gul::XMLNode& node)
      {
        node.SetName(createXMLValidTypeName(v.GetRTTI().GetName()));
        if(savingReferences.Contains(&v))
        {
          node.AppendAttribute(refTag).SetValue(savingReferences.Get(&v));
        }
        else
        {
          node.AppendAttribute(refIndexTag).SetValue(savingReferences.Size());
          savingReferences.Add(&v, savingReferences.Size());
          v.save(node);
        }
      }


      template<typename T>
      static void performSave(T* const& v, gul::XMLNode& node)
      {
        performSave(*v, node);
      }


      template<typename T>
      static void performLoad(T& v, const gul::XMLNode& node)
      {
        GUL_ASSERT_MSG(!node.GetAttribute(refTag).IsValid() &&
                   node.GetAttribute(refIndexTag).IsValid(),
                   "When loading a non-pointer we must not have a reference. Otherwise something went terribly wrong!!!!");

        T* loader = gul::ClassFactory<T>::CreateInstance(createTypeNameFromXML(gul::String(node.GetName())));
        loader->load(node);
        loadingReferences.Add(node.GetAttribute(refIndexTag).GetInt(), loader);
        v = *loader;
        GUL_DELETE(loader);
      }

      template<typename T>
      static void performLoad(T*& v, const gul::XMLNode& node)
      {
        GUL_ASSERT_MSG(node.GetAttribute(refTag).IsValid() ||
                   node.GetAttribute(refIndexTag).IsValid(),
                   "Each XML node must and a __ref or __refIndex");

        if(!node.GetAttribute(refIndexTag).IsValid())
        {
          v = static_cast<T*>(loadingReferences.Get(node.GetAttribute(refTag).GetInt()));
        }
        else
        {
          v = gul::ClassFactory<T>::CreateInstance(createTypeNameFromXML(gul::String(node.GetName())));
          v->load(node);
          loadingReferences.Add(node.GetAttribute(refIndexTag).GetInt(), v);
        }
      }

      template<typename T>
      static void performLoad(T**& v, const gul::XMLNode& node)
      {
        v = new T*;
        performLoad(*v, node);
      }


    private:
      static void reset(void)
      {
        savingReferences.Clear();
        loadingReferences.Clear();
      }
      virtual void save(gul::XMLNode& node) const = 0;
      virtual void load(const gul::XMLNode& node) = 0;

      friend class XMLManager;

    private:
      static gul::String createXMLValidTypeName(const gul::String& typeName)
      {
        return typeName.ReplaceAll(gul::String("."), gul::String(","))
               .ReplaceAll(gul::String("°"), gul::String("*"))
               .ReplaceAll(gul::String("-"), gul::String("<"))
               .ReplaceAll(gul::String("-"), gul::String(">"));
      }

      static gul::String createTypeNameFromXML(const gul::String& typeName)
      {
        int count = typeName.Count(gul::String("-"));
        GUL_ASSERT_MSG(count % 2 == 0, "TypeName must have an even number of -!");

        count >>= 1;
        if(count == 0) return typeName;

        gul::String* pOld = new gul::String(typeName);
        gul::String* pNew = nullptr;
        for(int i = 0; i < count; ++i)
        {
          GUL_DELETE(pNew);
          pNew = new gul::String(pOld->Replace(gul::String("<"), gul::String("-")).ReplaceBackward(gul::String(">"), gul::String("-")));
          GUL_DELETE(pOld);
          pOld = new gul::String(*pNew);
        }
        gul::String out = *pNew;
        GUL_DELETE(pNew);
        GUL_DELETE(pOld);
        return out.ReplaceAll(gul::String("*"), gul::String("°"))
               .ReplaceAll(gul::String(","), gul::String("."));
      }

    private:
      static gul::MapBasic<const void*, unsigned int> savingReferences;
      static gul::MapBasic<unsigned int, void*> loadingReferences;
      static const gul::String refTag;
      static const gul::String refIndexTag;

  };

}


#endif
