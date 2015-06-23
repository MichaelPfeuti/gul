/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011-2015 Michael Pfeuti.
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
void gul::Map<K, V>::save(gul::XMLNode& node) const
{
  typename gul::MapBasic<K, V>::Iterator it = this->GetIterator();
  int i = 0;
  while(it.HasNext())
  {
    it.Next();

    gul::XMLNode keyNode = node.AppendChild();
    keyNode.SetName(gul::String("key"));
    keyNode.AppendAttribute(gul::String("idx")).SetValue(i);
    gul::XMLNode keyData = keyNode.AppendChild();
    gul::XMLSerializable::performSave(it.Get().GetKey(), keyData);

    gul::XMLNode valueNode = node.AppendChild();
    valueNode.SetName(gul::String("value"));
    valueNode.AppendAttribute(gul::String("idx")).SetValue(i);
    gul::XMLNode valueData = valueNode.AppendChild();
    gul::XMLSerializable::performSave(it.Get().GetValue(), valueData);

    ++i;
  }
}

template<typename K, typename V>
void gul::Map<K, V>::load(const gul::XMLNode& node)
{
  gul::XMLNode child = node.GetFirstChild();
  while(child.IsValid())
  {
    // find only keynodes
    while(gul::String(child.GetName()) != gul::String("key"))
    {
      child = child.GetNextSibling();

      if(!child.IsValid()) return;
    }

    // get key data
    const gul::XMLNode keyData = child.GetFirstChild();
    K newKey;
    gul::XMLSerializable::performLoad(newKey, keyData);

    // find corresponding value and its data
    gul::XMLNode valueNode = node.FindChildByAttribute(gul::String("value"), gul::String("idx"), child.GetAttribute(gul::String("idx")).GetString());

    // TODO: only log this event or throw exception
    GUL_ASSERT_MSG(valueNode.IsValid(), "Invalid Map XML Data (no matching value found)!");

    if(valueNode.IsValid())
    {
      V newValue;
      gul::XMLNode valueData = valueNode.GetFirstChild();
      gul::XMLSerializable::performLoad(newValue, valueData);

      this->Add(newKey, newValue);
    }

    child = child.GetNextSibling();
  }
}
