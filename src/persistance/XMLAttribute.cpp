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

#include "XMLAttribute.h"
#include "String.h"
#include "Misc.h"

#include "3rdParty/pugi/pugixml.hpp"

gul::XMLAttribute::XMLAttribute(const pugi::xml_attribute& rAttribute)
  : pAttribute(new pugi::xml_attribute)
{
  *pAttribute = rAttribute;
}

gul::XMLAttribute::XMLAttribute(const gul::XMLAttribute& rOther)
  : pAttribute(new pugi::xml_attribute)
{
  *pAttribute = *rOther.pAttribute;
}

gul::XMLAttribute::~XMLAttribute(void)
{
  GUL_DELETE(pAttribute);
}

gul::XMLAttribute& gul::XMLAttribute::operator=(const gul::XMLAttribute& rOther)
{
  if(this != &rOther)
  {
    *pAttribute = rOther.pAttribute;
  }

  return *this;
}

void gul::XMLAttribute::SetValue(const gul::String& val)
{
  this->pAttribute->set_value(val.GetData());
}

void gul::XMLAttribute::SetValue(unsigned int i)
{
  this->pAttribute->set_value(i);
}

void gul::XMLAttribute::SetValue(int i)
{
  this->pAttribute->set_value(i);
}

void gul::XMLAttribute::SetValue(float f)
{
  this->pAttribute->set_value(f);
}

void gul::XMLAttribute::SetValue(double d)
{
  this->pAttribute->set_value(d);
}

void gul::XMLAttribute::SetValue(bool b)
{
  this->pAttribute->set_value(b);
}

gul::String gul::XMLAttribute::GetString(void) const
{
  return gul::String(this->pAttribute->value());
}

int gul::XMLAttribute::GetInt(void) const
{
  return this->pAttribute->as_int();
}

unsigned int gul::XMLAttribute::GetUnsignedInt(void) const
{
  return this->pAttribute->as_uint();
}

float gul::XMLAttribute::GetFloat(void) const
{
  return this->pAttribute->as_float();
}

double gul::XMLAttribute::GetDouble(void) const
{
  return this->pAttribute->as_double();
}

bool gul::XMLAttribute::GetBool(void) const
{
  return this->pAttribute->as_bool();
}

bool gul::XMLAttribute::IsValid(void) const
{
  return !this->pAttribute->empty();
}
