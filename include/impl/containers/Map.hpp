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

#include "Assert.h"
#include "Misc.h"

DEFINE_2TPL_RTTI(gul::Map)


template<typename K, typename V>
void gul::Map<K, V>::save(pugi::xml_node& node) const
{
  typename gul::MapBasic<K,V>::Iterator it = this->GetIterator();
  int i = 0;
  while(it.HasNext())
  {
    it.Next();

    pugi::xml_node keyNode = node.append_child();
    keyNode.set_name("key");
    keyNode.append_attribute("idx").set_value(i);
    pugi::xml_node keyData = keyNode.append_child();
    gul::XMLSerializable::performSave(it.Get().GetKey(), keyData);

    pugi::xml_node valueNode = node.append_child();
    valueNode.set_name("value");
    valueNode.append_attribute("idx").set_value(i);
    pugi::xml_node valueData = valueNode.append_child();
    gul::XMLSerializable::performSave(it.Get().GetValue(), valueData);

    ++i;
  }
}

template<typename K, typename V>
void gul::Map<K, V>::load(const pugi::xml_node& node)
{
  pugi::xml_node child = node.first_child();
  while(!child.empty())
  {
    // find only keynodes
    while(gul::String(child.name()) != gul::String("key"))
    {
      child = child.next_sibling();

      if(child.empty()) return;
    }

    // get key data
    pugi::xml_node keyData = child.first_child();
    K newKey;
    gul::XMLSerializable::performLoad(newKey, keyData);

    // find corresponding value and its data
    pugi::xml_node valueNode = node.find_child_by_attribute("value", "idx", child.attribute("idx").value());

    // TODO: only log this event or throw exception
    ASSERT_MSG(!valueNode.empty(), "Invalid Map XML Data (no matching value found)!");

    if(!valueNode.empty())
    {
      V newValue;
      pugi::xml_node valueData = valueNode.first_child();
      gul::XMLSerializable::performLoad(newValue, valueData);

      this->Add(newKey, newValue);
    }

    child = child.next_sibling();
  }
}
