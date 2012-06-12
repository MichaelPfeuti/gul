#pragma once
#ifndef _GUL_PERSISTANCE_XML_MACROS_H_
#define _GUL_PERSISTANCE_XML_MACROS_H_
/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011-2012 Michael Pfeuti.
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

#include <typeinfo>

#include <3rdParty/pugi/pugixml.hpp>
#include "Map.h"
#include "String.h"
#include "ClassFactory.h"
#include "Misc.h"
#include "XMLSerializable.h"


#define INHERIT_SERIALIZABLE(T) public gul::XMLSerializable, REGISTER_FACTORY(T)


#define DECLARE_SERIALIZABLE(className) \
  private:\
  virtual void save(pugi::xml_node& node) const; \
  virtual void load(const pugi::xml_node& node); \
  friend class gul::XMLSerializable; \
  private:



// #######################
// #### SAVING MACROS ####
// #######################
#define BEGIN_SAVE(className) \
  void className::save(pugi::xml_node& node) const \
  {

#define SAVE_BASE_CLASS(className) \
  className::save(node);

#define SAVE_VARIABLE(attributeArg) \
  { \
    pugi::xml_node childNode = node.append_child(); \
    childNode.append_attribute("__attributeName").set_value(#attributeArg); \
    performSave(attributeArg, childNode); \
  }

#define END_SAVE(className) \
  }





// ########################
// #### LOADING MACROS ####
// ########################
#define BEGIN_LOAD(className) \
  void className::load(const pugi::xml_node& node) {

#define LOAD_BASE_CLASS(className) \
  className::load(node);

#define LOAD_VARIABLE(attributeArg) \
  { \
    pugi::xml_node listNode = node.first_child(); \
    while (!listNode.empty()) { \
      gul::String __string(listNode.attribute("__attributeName").value()); \
      if (__string == gul::String(#attributeArg)) { \
        performLoad(attributeArg, listNode); \
      } \
      listNode = listNode.next_sibling();  \
    } \
  }

#define END_LOAD(className) \
  }


#endif
