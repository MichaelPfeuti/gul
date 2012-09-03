#pragma once
#ifndef _GUL_IMAGE_IMAGE_FILE_HANDLER_H_
#define _GUL_IMAGE_IMAGE_FILE_HANDLER_H_
/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011-2012 Michael Pfeuti
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

namespace gul
{
  class ImageIO;
}

#include "File.h"
#include "MapBasic.h"
#include "String.h"
#include "Image.h"

namespace gul
{

  class ImageFileHandler
  {
    public:
      static ImageFileHandler& Instance(void);
      Image Load(const gul::File& file) const;
      void Save(const gul::File& file, const Image& image) const;

    private:
      ImageFileHandler(void);
      virtual ~ImageFileHandler(void);

      void initializeAllLoaders(void);
      static void deleteInstance(void);

    private:
      MapBasic<String, ImageIO*> endingsMap;
      static ImageFileHandler* instance;

  };

}

#endif
