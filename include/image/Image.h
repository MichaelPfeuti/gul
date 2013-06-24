#pragma once
#ifndef _GUL_IMAGE_IMAGE_H_
#define _GUL_IMAGE_IMAGE_H_
/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011-2013 Michael Pfeuti
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
#include "SharedResource.h"

#ifdef LIBGLEW_FOUND
#  include <GL/glew.h>
#endif

namespace gul
{

  template<typename T>
  class ImageT : private SharedResource
  {
      DECLARE_RTTI(ImageT)

    public:
      enum ImageFormat
      {
        IF_UNDEFINED,
        IF_GRAY,
        IF_RGBA,
        IF_CMYKA,
        IF_HSLA,
        IF_HSVA,
        IF_HSIA
      };

    public:
      ImageT(void);
      ImageT(int w, int h, ImageFormat ImageFormat = IF_RGBA);
      ImageT(int w, int h, ImageFormat imageFormat, const T* data);
      ImageT(const ImageT& rImage);
      virtual ~ImageT(void);

      ImageT& operator=(const ImageT& other);

      int GetWidth(void) const;
      int GetHeight(void) const;
      int GetNumberOfChannels(void) const;
      ImageFormat GetImageFormat(void) const;

      bool IsNull(void) const;

      const T& GetColorConst(int x, int y, int channel) const;
      const T& GetColor(int x, int y, int channel) const;
      T& GetColor(int x, int y, int channel);

      const T* GetDataConst(void) const;
      const T* GetData(void) const;
      T* GetData(void);

      const T* GetScanlineConst(int scanline) const;
      const T* GetScanline(int scanline) const;
      T* GetScanline(int scanline);

      int GetPitch(void) const;


    protected:
      using SharedResource::operator =;
      virtual void deleteSharedResource(void);
      virtual void transferSharedResourceFrom(const SharedResource& newOwner);
      virtual ImageT* createSharedResourceOwner(void) const;
      virtual bool isResourceDataSizeEqual(const SharedResource& rOther);
      virtual void copyDataFrom(const SharedResource& rOther);

    private:
      T* m_pData;
      int m_width;
      int m_height;
      ImageFormat m_imageFormat;
      bool m_isGLDataSynched;

#ifdef LIBOPENGL_FOUND
    public:
      const GLuint& GetGLTexture(void);

    private:
      GLuint m_glTexture;
#endif
  };

  typedef ImageT<unsigned char> Image;
  typedef ImageT<float> ImageF;
  typedef ImageT<unsigned int> ImageI;
}

SPECIALIZE_TPL_TRAITS(gul::ImageT)


#include "impl/image/Image.hpp"


#endif
