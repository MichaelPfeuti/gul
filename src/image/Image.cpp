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

#include "Image.h"
#include "Misc.h"
#include "Assert.h"

DEFINE_RTTI(gul::Image);

gul::Image::Image(void)
  : pData(nullptr),
    width(0),
    height(0),
    imageType(IT_UNDEFINED)
{

}

gul::Image::Image(int w, int h)
  : pData(nullptr),
    width(w),
    height(h),
    imageType(IT_UNDEFINED)
{
}

gul::Image::Image(int w, int h, ImageType dataImageType)
  : pData(nullptr),
    width(w),
    height(h),
    imageType(dataImageType)
{
}

gul::Image::Image(int w, int h, ImageType dataImageType, const unsigned char* data)
  : pData(nullptr),
    width(w),
    height(h),
    imageType(dataImageType)
{
  AllocateMemory();
  for(int y = 0; y < h; ++y)
    for(int x = 0; x < w; ++x)
    {
      gul::RGBA rgba = gul::RGBA(data[(y * w + x) * 4 + 0],
                                 data[(y * w + x) * 4 + 1],
                                 data[(y * w + x) * 4 + 2],
                                 data[(y * w + x) * 4 + 3]);
      SetPixel(x, y, rgba);
    }
}

void gul::Image::AllocateMemory(void)
{
  ASSERT(pData == nullptr);
  ASSERT(GetWidth()*GetHeight()*GetNumberOfChannels() > 0);

  int size = GetWidth() * GetHeight() * GetNumberOfChannels();
  pData = new float[size];
}

gul::Image::~Image(void)
{
//  GUL_DELETE_ARRAY(pData);
}

int gul::Image::GetWidth(void) const
{
  return this->width;
}

int gul::Image::GetHeight(void) const
{
  return this->height;
}

int gul::Image::GetNumberOfChannels(void) const
{
  return 4;
}

gul::Image::ImageType gul::Image::GetImageType(void) const
{
  return this->imageType;
}

const gul::RGBA gul::Image::GetPixel(int x, int y) const
{
  return gul::RGBA(this->pData[(x + y * this->GetWidth()) * this->GetNumberOfChannels() + 0],
                   this->pData[(x + y * this->GetWidth()) * this->GetNumberOfChannels() + 1],
                   this->pData[(x + y * this->GetWidth()) * this->GetNumberOfChannels() + 2],
                   this->pData[(x + y * this->GetWidth()) * this->GetNumberOfChannels() + 3]);
}

void gul::Image::SetPixel(int x, int y, const gul::RGBA& rgba)
{
  this->pData[(x + y * this->GetWidth())*this->GetNumberOfChannels() + 0] = rgba.GetRed();
  this->pData[(x + y * this->GetWidth())*this->GetNumberOfChannels() + 1] = rgba.GetGreen();
  this->pData[(x + y * this->GetWidth())*this->GetNumberOfChannels() + 2] = rgba.GetBlue();
  this->pData[(x + y * this->GetWidth())*this->GetNumberOfChannels() + 3] = rgba.GetAlpha();
}
