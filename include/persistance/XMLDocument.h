#pragma once
#ifndef _GUL_PERSISTANCE_XML_DOCUMENT_H_
#define _GUL_PERSISTANCE_XML_DOCUMENT_H_
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

#include "File.h"
#include "XMLNode.h"
#include "NonCopyable.h"

namespace pugi
{
  class xml_document;
}

namespace gul
{

  class GUL_EXPORT XMLDocument : public NonCopyable
  {
    public:
      XMLDocument(void);
      ~XMLDocument(void);

      bool SaveFile(const File& rFile);
      void LoadFile(const File& rFile);
      XMLNode GetRoot(void);

    private:
      const pugi::xml_document* getConstDocument(void)
      {
        return pDocument;
      }

    private:
      pugi::xml_document* pDocument;
      bool hasRootNode;
  };

}

#endif
