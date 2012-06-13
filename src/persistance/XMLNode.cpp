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

#include "XMLNode.h"
#include "String.h"

gul::XMLNode::XMLNode(pugi::xml_node n)
  : node(n)
{
}

gul::XMLAttribute gul::XMLNode::AppendAttribute(const gul::String& name)
{
  return gul::XMLAttribute(this->node.append_attribute(name.GetData()));
}

gul::XMLAttribute gul::XMLNode::GetAttribute(const gul::String& name)
{
  return gul::XMLAttribute(this->node.attribute(name.GetData()));
}

const gul::XMLAttribute gul::XMLNode::GetAttribute(const gul::String& name) const
{
  return gul::XMLAttribute(this->node.attribute(name.GetData()));
}

void gul::XMLNode::SetName(const gul::String& name)
{
  this->node.set_name(name.GetData());
}

const gul::String gul::XMLNode::GetName(void) const
{
  return gul::String(this->node.name());
}

gul::XMLNode gul::XMLNode::AppendChild(void)
{
  return gul::XMLNode(this->node.append_child());
}

gul::XMLNode gul::XMLNode::GetFirstChild(void)
{
  return gul::XMLNode(this->node.first_child());
}

const gul::XMLNode gul::XMLNode::GetFirstChild(void) const
{
  return gul::XMLNode(this->node.first_child());
}

gul::XMLNode gul::XMLNode::GetNextSibling(void)
{
  return gul::XMLNode(this->node.next_sibling());
}

const gul::XMLNode gul::XMLNode::GetNextSibling(void) const
{
  return gul::XMLNode(this->node.next_sibling());
}

gul::XMLNode gul::XMLNode::FindChildByAttribute(const gul::String &name, const gul::String &attributName, const gul::String &attributValue)
{
  return gul::XMLNode(this->node.find_child_by_attribute(name.GetData(), attributName.GetData(), attributValue.GetData()));
}

const gul::XMLNode gul::XMLNode::FindChildByAttribute(const gul::String &name, const gul::String &attributName, const gul::String &attributValue) const
{
  return gul::XMLNode(this->node.find_child_by_attribute(name.GetData(), attributName.GetData(), attributValue.GetData()));
}

bool gul::XMLNode::IsValid(void) const
{
  return !this->node.empty();
}
