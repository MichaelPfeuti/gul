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

#include "Map.h"
#include "String.h"
#include "ClassFactory.h"
#include "Misc.h"
#include "XMLSerializable.h"


#define INHERIT_SERIALIZABLE(T) public gul::XMLSerializable, REGISTER_FACTORY(T)


#define DECLARE_SERIALIZABLE(className) \
  private:\
  virtual void save(gul::XMLNode& node) const; \
  virtual void load(const gul::XMLNode& node); \
  friend class gul::XMLSerializable; \
  private:



// #######################
// #### SAVING MACROS ####
// #######################
#define BEGIN_SAVE(className) \
  void className::save(gul::XMLNode& node) const \
  {

#define SAVE_BASE_CLASS(className) \
  className::save(node);

#define SAVE_VARIABLE(attributeArg) \
  { \
    gul::XMLNode childNode = node.AppendChild(); \
    childNode.AppendAttribute(gul::String("__attributeName")).SetValue(gul::String(#attributeArg)); \
    performSave(attributeArg, childNode); \
  }

#define END_SAVE(className) \
  }





// ########################
// #### LOADING MACROS ####
// ########################
#define BEGIN_LOAD(className) \
  void className::load(const gul::XMLNode& node) {

#define LOAD_BASE_CLASS(className) \
  className::load(node);

#define LOAD_VARIABLE(attributeArg) \
  { \
    gul::XMLNode listNode = node.GetFirstChild(); \
    while (listNode.IsValid()) { \
      gul::String __string(listNode.GetAttribute(gul::String("__attributeName")).GetString()); \
      if (__string == gul::String(#attributeArg)) { \
        performLoad(attributeArg, listNode); \
      } \
      listNode = listNode.GetNextSibling();  \
    } \
  }

#define END_LOAD(className) \
  }


#endif
