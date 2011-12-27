#pragma once
#ifndef _GUL_PERSISTANCE_XML_MACROS_H_
#define _GUL_PERSISTANCE_XML_MACROS_H_
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

#include <typeinfo>

#include <3rdParty/pugi/pugixml.hpp>
#include "Map.h"
#include "String.h"
#include "ClassFactory.h"
#include "Misc.h"

typedef gul::Map<gul::String, void*> InstanceMap;

// @todo: chose better name, because this doesn't imply the instance handling!!!
#define DECLARE_SERIALIZABLE() \
    private: \
        mutable int __refIndex;   /* reference index*/ \
        static int __maxRef; /* highest reference index*/ \
        static InstanceMap __loadedInstances; /* reference index to instance map*/ \
    public:\
        virtual void Save(pugi::xml_node& node, bool resetMode = false) const; \
        virtual void* Load(const pugi::xml_node& node, bool resetMode = false) const; \
    private:



// #######################
// #### SAVING MACROS ####
// #######################
#define BEGIN_SAVE(className) \
        int className::__maxRef = 0; \
        \
        void className::Save(pugi::xml_node& node, bool resetMode) const \
        { \
            if(resetMode && !__saved)  /*in this case this node was already reset*/ \
            { \
                return; \
            }  \
            if(resetMode) /*in this case we have to reset this node, and traverse fruther*/ \
            { \
                __saved = false; \
                __maxRef = 0; \
                __refIndex = -1; \
            } \
            node.set_name(#className); \
            if (__saved && !resetMode) /* in this case we save this node already.*/ \
            { \
                node.append_attribute("__ref").set_value(__refIndex); \
                return; \
            } \
            __refIndex = __maxRef++; \
            SAVE_PRIMITIVE(__refIndex); \
            if(!resetMode) /* in this case we mark that this node was saved */ \
            { \
                __saved = true; \
            }


#define BEGIN_SAVE_BASE_CLASS(className) \
        void className::Save(pugi::xml_node& node, bool resetMode) \
        {


#define SAVE_BASE_CLASS(className) \
          className::Save(node, resetMode);


#define SAVE_PRIMITIVE(attributeArg) \
          if(!resetMode) \
          { \
              node.append_attribute(#attributeArg).set_value(attributeArg); \
          }


#define SAVE_POINTER(attributeArg) \
          if(attributeArg != nullptr) \
          { \
              pugi::xml_node childNode = node.append_child(); \
              attributeArg->Save(childNode, resetMode); \
              childNode.append_attribute("attributeName").set_value(#attributeArg); \
          } \
          else \
          { \
              FAIL("Could not save pointer because it was null"); \
          }

#define SAVE_VARIABLE(attributeArg) \
          { \
            pugi::xml_node childNode = node.append_child(); \
            childNode.append_attribute("attributeName").set_value(#attributeArg); \
            attributeArg.Save(childNode, resetMode); \
          }


#define END_SAVE_BASE_CLASS(className) \
      }


#define END_SAVE(className) \
      }





// ########################
// #### LOADING MACROS ####
// ########################
#define BEGIN_LOAD(className) \
      \
      InstanceMap className::__loadedInstances =  InstanceMap(); \
      \
      void* className::Load(const pugi::xml_node& node, bool resetMode) const { \
          if(resetMode) \
          { \
              className::__loadedInstances.Clear(); \
          } \
          int i; unsigned int ui; \
          short s; unsigned short us; \
          long l; unsigned long ul; \
          float f; \
          double d;\
          bool b; \
          char c; \
          UNUSED_VARIABLE(i); \
          UNUSED_VARIABLE(ui); \
          UNUSED_VARIABLE(s); \
          UNUSED_VARIABLE(us); \
          UNUSED_VARIABLE(l); \
          UNUSED_VARIABLE(ul); \
          UNUSED_VARIABLE(f); \
          UNUSED_VARIABLE(d); \
          UNUSED_VARIABLE(b); \
          UNUSED_VARIABLE(c); \
          if (!resetMode && !node.attribute("__ref").empty()) \
          { \
              gul::String string(node.attribute("__ref").value()); \
              void* ptr = className::__loadedInstances.Get(string); \
              return ptr; \
          } \
          className* instance; \
          if(!resetMode) \
          { \
              instance = new className(); \
          } \
          LOAD_PRIMITIVE(__refIndex); \
          if(!resetMode) \
          { \
              gul::String indexString = gul::String("%").Arg(instance->__refIndex); \
              className::__loadedInstances.Add(indexString, instance); \
          }


#define BEGIN_LOAD_BASE_ClASS(className) \
    void* className::Load(const pugi::xml_node& node, void* instanceVoid, bool resetMode) const { \
        int i; unsigned int ui; \
        short s; unsigned short us; \
        long l; unsigned long ul; \
        float f; \
        double d;\
        bool b; \
        UNUSED_VARIABLE(i); \
        UNUSED_VARIABLE(ui); \
        UNUSED_VARIABLE(s); \
        UNUSED_VARIABLE(us); \
        UNUSED_VARIABLE(l); \
        UNUSED_VARIABLE(ul); \
        UNUSED_VARIABLE(f); \
        UNUSED_VARIABLE(d); \
        UNUSED_VARIABLE(b); \
        UNUSED_VARIABLE(listNode); \
        className* instance; \
        if(!resetMode) \
            instance = (className*) instanceVoid;


#define LOAD_BASE_CLASS(className) \
        className::Load(node, instance, resetMode);


// TODO: check signed/unsigned
#define LOAD_PRIMITIVE(attributeArg) \
    if (!resetMode && !node.attribute(#attributeArg).empty()) { \
        if (typeid(attributeArg) == typeid(i) || typeid(attributeArg) == typeid(s) || \
            typeid(attributeArg) == typeid(l) || typeid(attributeArg) == typeid(ui) || \
            typeid(attributeArg) == typeid(us) || typeid(attributeArg) == typeid(ul)) \
        { \
            instance->attributeArg = node.attribute(#attributeArg).as_int(); \
        } \
        else if (typeid(attributeArg) == typeid(d) || typeid(attributeArg) == typeid(f)) \
        { \
            instance->attributeArg = node.attribute(#attributeArg).as_double(); \
        } \
        else if (typeid(attributeArg) == typeid(b)) \
        { \
            instance->attributeArg = node.attribute(#attributeArg).as_bool(); \
        } \
        else if (typeid(attributeArg) == typeid(c)) \
        { \
            instance->attributeArg = static_cast<char>(node.attribute(#attributeArg).as_int()); \
        } else { \
            FAIL("Invalid Primitive!"); \
        }\
    }

//@todo: use templates to rid className
#define LOAD_POINTER(attributeArg, className) \
    { \
      pugi::xml_node listNode = node.first_child(); \
      while (!listNode.empty()) { \
          gul::String string(listNode.attribute("attributeName").value()); \
          if (string == gul::String(#attributeArg)) { \
              className* loaderObject = (className*) gul::ClassFactory::CreateInstance(gul::String(listNode.name()));   \
              className* myObject = (className*) loaderObject->Load(listNode, resetMode); \
              delete loaderObject; \
              if(!resetMode) { \
                  instance->attributeArg = myObject; \
              } \
          } \
          listNode = listNode.next_sibling();  \
      } \
    }

//@todo: use templates to rid className
#define LOAD_VARIABLE(attributeArg, className) \
    { \
      pugi::xml_node listNode = node.first_child(); \
      while (!listNode.empty()) { \
          gul::String string(listNode.attribute("attributeName").value()); \
          if (string == gul::String(#attributeArg)) { \
              className* loaderObject = (className*) gul::ClassFactory::CreateInstance(gul::String(listNode.name()));   \
              className* myObject = (className*) loaderObject->Load(listNode, resetMode); \
              delete loaderObject; \
              if(!resetMode) { \
                  instance->attributeArg = *myObject; \
                  GUL_DELETE(myObject); \
              } \
          } \
          listNode = listNode.next_sibling();  \
      } \
    }


#define END_LOAD_BASE_CLASS(className) \
        return instance; \
    }


#define END_LOAD(className) \
        return instance; \
    }


#endif
