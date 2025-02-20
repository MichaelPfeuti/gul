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

#include "XMLDocument.h"

#include "Misc.h"
#include <pugixml.hpp>

gul::XMLDocument::XMLDocument(void)
  : pDocument(new pugi::xml_document),
    hasRootNode(false)
{
}

gul::XMLDocument::~XMLDocument(void)
{
  GUL_DELETE(pDocument);
}

bool gul::XMLDocument::SaveFile(const File& rFile)
{
  return this->pDocument->save_file(rFile.GetPath().GetData());
}

void gul::XMLDocument::LoadFile(const File& rFile)
{
  this->pDocument->load_file(rFile.GetPath().GetData());
  this->hasRootNode = true;
}

gul::XMLNode gul::XMLDocument::GetRoot(void)
{
  if(this->hasRootNode)
  {
    return gul::XMLNode(this->pDocument->first_child());
  }
  else
  {
    return gul::XMLNode(pDocument->append_child());
  }
}
