#pragma once
#ifndef _GUL_IMAGE_IMAGE_H_
#define _GUL_IMAGE_IMAGE_H_
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

#include "RTTI.h"
#include "RGBA.h"

namespace gul
{

  class Image
  {
    DECLARE_RTTI(Image)

    public:
      enum ImageType
      {
        IT_UNDEFINED,
        IT_RGBA,
        IT_CMYK,
        IT_HSL,
        IT_HSV
      };

    public:
      Image(void);
      Image(int w, int h);
      Image(int w, int h, ImageType dataImageType);
      Image(int w, int h, ImageType dataImageType, const unsigned char* data);
      virtual ~Image(void);

      void AllocateMemory(void);

      int GetWidth(void) const;
      int GetHeight(void) const;
      int GetNumberOfChannels(void) const;
      ImageType GetImageType(void) const;

      const RGBA GetPixel(int x, int y) const;
      void SetPixel(int x, int y, const gul::RGBA &rgba);

    private:
      float* pData;
      int width;
      int height;
      ImageType imageType;

  };
}

SPECIALIZE_TRAITS(gul::Image)


#endif
