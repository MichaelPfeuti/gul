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

#include "Image.h"
#include "Misc.h"
#include "Assert.h"

DEFINE_TPL_RTTI(gul::ImageT);

template<typename T>
gul::ImageT<T>::ImageT(void)
  : m_pData(nullptr),
    m_width(0),
    m_height(0),
    m_imageFormat(IF_UNDEFINED)
{
}

template<typename T>
gul::ImageT<T>::ImageT(int w, int h, ImageFormat imageFormat)
  : m_pData(nullptr),
    m_width(w),
    m_height(h),
    m_imageFormat(imageFormat)
{
  initConstructor();
}

template<typename T>
gul::ImageT<T>::ImageT(int w, int h, ImageFormat imageFormat, const T* data)
  : m_pData(nullptr),
    m_width(w),
    m_height(h),
    m_imageFormat(imageFormat)
{
  initConstructor();
  memcpy(m_pData, data, sizeof(T)*w*h*GetNumberOfChannels());
}

template<typename T>
gul::ImageT<T>::ImageT(const ImageT& rImage)
  : SharedResource(),
    m_pData(nullptr),
    m_width(rImage.m_width),
    m_height(rImage.m_height),
    m_imageFormat(rImage.m_imageFormat)
{
  initCopyConstructor(rImage);
}

template<typename T>
gul::ImageT<T>& gul::ImageT<T>::operator =(const ImageT<T>& rImage)
{
  SharedResource::operator =(rImage);
  if(this != &rImage)
  {
    m_width = rImage.m_width;
    m_height = rImage.m_height;
    m_imageFormat = rImage.m_imageFormat;
  }
  return *this;
}

template<typename T>
gul::ImageT<T>::~ImageT(void)
{
}

template<typename T>
int gul::ImageT<T>::GetWidth(void) const
{
  return m_width;
}

template<typename T>
int gul::ImageT<T>::GetHeight(void) const
{
  return m_height;
}

template<typename T>
int gul::ImageT<T>::GetNumberOfChannels(void) const
{
  return 4;
}

template<typename T>
typename gul::ImageT<T>::ImageFormat gul::ImageT<T>::GetImageFormat(void) const
{
  return m_imageFormat;
}

template<typename T>
bool gul::ImageT<T>::IsNull(void) const
{
  return m_width == 0 || m_height == 0 ||
         m_imageFormat == IF_UNDEFINED;
}


template<typename T>
const T* gul::ImageT<T>::GetDataConst(void) const
{
  return m_pData;
}

template<typename T>
const T* gul::ImageT<T>::GetData(void) const
{
  return m_pData;
}

template<typename T>
T* gul::ImageT<T>::GetData(void)
{
  detach();
  return m_pData;
}

template<typename T>
const T* gul::ImageT<T>::GetScanlineConst(int scanline) const
{
  ASSERT(scanline >= 0 && scanline <= GetHeight());

  return m_pData + scanline*GetPitch();
}

template<typename T>
const T* gul::ImageT<T>::GetScanline(int scanline) const
{
  ASSERT(scanline >= 0 && scanline <= GetHeight());

  return m_pData + scanline*GetPitch();
}

template<typename T>
T* gul::ImageT<T>::GetScanline(int scanline)
{
  ASSERT(scanline >= 0 && scanline <= GetHeight());

  detach();
  return m_pData + scanline*GetPitch();
}

template<typename T>
const T& gul::ImageT<T>::GetColorConst(int x, int y, int channel) const
{
  ASSERT(channel >= 0 && channel <= GetNumberOfChannels());
  ASSERT(x >= 0 && x <= GetWidth());
  ASSERT(y >= 0 && y <= GetHeight());

  return m_pData[y*GetPitch() + x*GetNumberOfChannels() + channel];
}

template<typename T>
const T& gul::ImageT<T>::GetColor(int x, int y, int channel) const
{
  ASSERT(channel >= 0 && channel <= GetNumberOfChannels());
  ASSERT(x >= 0 && x <= GetWidth());
  ASSERT(y >= 0 && y <= GetHeight());

  return m_pData[y*GetPitch() + x*GetNumberOfChannels() + channel];
}


template<typename T>
T& gul::ImageT<T>::GetColor(int x, int y, int channel)
{
  ASSERT(channel >= 0 && channel <= GetNumberOfChannels());
  ASSERT(x >= 0 && x <= GetWidth());
  ASSERT(y >= 0 && y <= GetHeight());

  detach();
  return m_pData[y*GetPitch() + x*GetNumberOfChannels() + channel];
}

template<typename T>
int gul::ImageT<T>::GetPitch(void) const
{
  return GetNumberOfChannels() * sizeof(T) * m_width;
}

template<typename T>
void gul::ImageT<T>::allocateSharedResource(void)
{
  ASSERT(m_pData == nullptr);
  ASSERT(GetWidth()*GetHeight()*GetNumberOfChannels() > 0);

  int size = GetWidth() * GetHeight() * GetNumberOfChannels();
  m_pData = new T[size];
  memset(m_pData, 0, sizeof(T)*size);
}

template<typename T>
void gul::ImageT<T>::deleteSharedResource(void)
{
  GUL_DELETE_ARRAY(m_pData);
}

 template<typename T>
void gul::ImageT<T>::transferSharedResourceFrom(const SharedResource& newOwner)
{
  m_pData = static_cast<const ImageT<T>&>(newOwner).m_pData;
}

template<typename T>
gul::ImageT<T>::ImageT(const ImageT& rImage, bool allocate)
  : m_pData(nullptr),
    m_width(rImage.m_width),
    m_height(rImage.m_height),
    m_imageFormat(rImage.m_imageFormat)
{
  if(allocate)
  {
    allocateSharedResource();
  }
}

template<typename T>
gul::ImageT<T>* gul::ImageT<T>::createSharedResourceOwner(void) const
{
  return new gul::ImageT<T>(*this, true);
}
