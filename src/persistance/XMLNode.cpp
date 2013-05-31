/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011-2013 Michael Pfeuti.
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
#include "Misc.h"

#include <pugixml.hpp>

gul::XMLNode::XMLNode(const pugi::xml_node& rNode)
  : pNode(new pugi::xml_node)
{
  *pNode = rNode;
}

gul::XMLNode::XMLNode(const XMLNode& rOther)
  : pNode(new pugi::xml_node)
{
  *pNode = *rOther.pNode;
}

gul::XMLNode::~XMLNode(void)
{
  GUL_DELETE(pNode);
}

gul::XMLNode& gul::XMLNode::operator=(const XMLNode& rOther)
{
  if(&rOther != this)
  {
    *pNode = *rOther.pNode;
  }

  return *this;
}

gul::XMLAttribute gul::XMLNode::AppendAttribute(const gul::String& rName)
{
  return gul::XMLAttribute(this->pNode->append_attribute(rName.GetData()));
}

gul::XMLAttribute gul::XMLNode::GetAttribute(const gul::String& rName)
{
  return gul::XMLAttribute(this->pNode->attribute(rName.GetData()));
}

const gul::XMLAttribute gul::XMLNode::GetAttribute(const gul::String& rName) const
{
  return gul::XMLAttribute(this->pNode->attribute(rName.GetData()));
}

void gul::XMLNode::SetName(const gul::String& rName)
{
  this->pNode->set_name(rName.GetData());
}

const gul::String gul::XMLNode::GetName(void) const
{
  return gul::String(this->pNode->name());
}

gul::XMLNode gul::XMLNode::AppendChild(void)
{
  return gul::XMLNode(this->pNode->append_child());
}

gul::XMLNode gul::XMLNode::GetFirstChild(void)
{
  return gul::XMLNode(this->pNode->first_child());
}

const gul::XMLNode gul::XMLNode::GetFirstChild(void) const
{
  return gul::XMLNode(this->pNode->first_child());
}

gul::XMLNode gul::XMLNode::GetNextSibling(void)
{
  return gul::XMLNode(this->pNode->next_sibling());
}

const gul::XMLNode gul::XMLNode::GetNextSibling(void) const
{
  return gul::XMLNode(this->pNode->next_sibling());
}

gul::XMLNode gul::XMLNode::FindChildByAttribute(const gul::String& rName, const gul::String& rAttributName, const gul::String& rAttributValue)
{
  return gul::XMLNode(this->pNode->find_child_by_attribute(rName.GetData(), rAttributName.GetData(), rAttributValue.GetData()));
}

const gul::XMLNode gul::XMLNode::FindChildByAttribute(const gul::String& name, const gul::String& rAttributName, const gul::String& rAttributValue) const
{
  return gul::XMLNode(this->pNode->find_child_by_attribute(name.GetData(), rAttributName.GetData(), rAttributValue.GetData()));
}

bool gul::XMLNode::IsValid(void) const
{
  return !this->pNode->empty();
}
