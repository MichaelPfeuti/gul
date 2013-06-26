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
#include "Log.h"

DEFINE_TPL_RTTI(gul::ImageT);

template<typename T>
gul::ImageT<T>::ImageT(void)
  : m_pData(nullptr),
    m_width(0),
    m_height(0),
    m_imageFormat(IF_UNDEFINED),
    m_isGLDataSynched(false),
    m_isGLAquiredByCL(false)
{
}

template<typename T>
gul::ImageT<T>::ImageT(int w, int h, ImageFormat imageFormat)
  : m_pData(nullptr),
    m_width(w),
    m_height(h),
    m_imageFormat(imageFormat),
    m_isGLDataSynched(false),
    m_isGLAquiredByCL(false)
{
  initConstructor();
}

template<typename T>
gul::ImageT<T>::ImageT(int w, int h, ImageFormat imageFormat, const T* data)
  : m_pData(nullptr),
    m_width(w),
    m_height(h),
    m_imageFormat(imageFormat),
    m_isGLDataSynched(false),
    m_isGLAquiredByCL(false)
{
  initConstructor();
  memcpy(m_pData->GetData(), data, sizeof(T)*w*h*GetNumberOfChannels());
}

template<typename T>
gul::ImageT<T>::ImageT(const ImageT& rImage)
  : SharedResource(),
    m_pData(nullptr),
    m_width(rImage.m_width),
    m_height(rImage.m_height),
    m_imageFormat(rImage.m_imageFormat),
    m_isGLDataSynched(rImage.m_isGLDataSynched),
    m_isGLAquiredByCL(rImage.m_isGLAquiredByCL)
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
    m_isGLDataSynched = rImage.m_isGLDataSynched;
    m_isGLAquiredByCL = rImage.m_isGLAquiredByCL;
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
  return m_pData->GetData();
}

template<typename T>
const T* gul::ImageT<T>::GetData(void) const
{
  return m_pData->GetData();
}

template<typename T>
T* gul::ImageT<T>::GetData(void)
{
  detach();
  m_isGLDataSynched = false;
  return m_pData->GetData();
}

template<typename T>
const T* gul::ImageT<T>::GetScanlineConst(int scanline) const
{
  GUL_ASSERT(scanline >= 0 && scanline <= GetHeight());

  return m_pData->GetData() + scanline*GetPitch();
}

template<typename T>
const T* gul::ImageT<T>::GetScanline(int scanline) const
{
  GUL_ASSERT(scanline >= 0 && scanline <= GetHeight());

  return m_pData->GetData() + scanline*GetPitch();
}

template<typename T>
T* gul::ImageT<T>::GetScanline(int scanline)
{
  GUL_ASSERT(scanline >= 0 && scanline <= GetHeight());

  detach();
  m_isGLDataSynched = false;
  return m_pData->GetData() + scanline*GetPitch();
}

template<typename T>
const T& gul::ImageT<T>::GetColorConst(int x, int y, int channel) const
{
  GUL_ASSERT(channel >= 0 && channel <= GetNumberOfChannels());
  GUL_ASSERT(x >= 0 && x <= GetWidth());
  GUL_ASSERT(y >= 0 && y <= GetHeight());

  return m_pData->GetData()[y*GetPitch() + x*GetNumberOfChannels() + channel];
}

template<typename T>
const T& gul::ImageT<T>::GetColor(int x, int y, int channel) const
{
  GUL_ASSERT(channel >= 0 && channel <= GetNumberOfChannels());
  GUL_ASSERT(x >= 0 && x <= GetWidth());
  GUL_ASSERT(y >= 0 && y <= GetHeight());

  return m_pData->GetData()[y*GetPitch() + x*GetNumberOfChannels() + channel];
}


template<typename T>
T& gul::ImageT<T>::GetColor(int x, int y, int channel)
{
  GUL_ASSERT(channel >= 0 && channel <= GetNumberOfChannels());
  GUL_ASSERT(x >= 0 && x <= GetWidth());
  GUL_ASSERT(y >= 0 && y <= GetHeight());

  detach();
  m_isGLDataSynched = false;
  return m_pData->GetData()[y*GetPitch() + x*GetNumberOfChannels() + channel];
}

template<typename T>
int gul::ImageT<T>::GetPitch(void) const
{
  return GetNumberOfChannels() * sizeof(T) * m_width;
}

template<typename T>
bool gul::ImageT<T>::isResourceDataSizeEqual(const SharedResource& rOther)
{
  return m_width == static_cast<const ImageT<T>&>(rOther).m_width &&
         m_height == static_cast<const ImageT<T>&>(rOther).m_height &&
         m_imageFormat == static_cast<const ImageT<T>&>(rOther).m_imageFormat;
}

template<typename T>
void gul::ImageT<T>::copyDataFrom(const SharedResource& rOther)
{
  memcpy(m_pData->GetData(), 
         static_cast<const ImageT<T>&>(rOther).m_pData->GetData(), 
         GetPitch()*m_height);
}

template<typename T>
void gul::ImageT<T>::deleteSharedResource(void)
{
  GUL_DELETE(m_pData);

//#ifdef LIBOPENGL_FOUND
//#ifdef LIBOPENCL_FOUND
//  if(m_isGLAquiredByCL)
//  {
//    CLContext* pCurrentContext = CLContext::GetCurrentContext();
//    clEnqueueReleaseGLObjects(pCurrentContext->GetCurrentQueue(),
//                              1, &m_clImage,
//                              0, nullptr,
//                              nullptr);
//  }
//#endif

//  if(glIsTexture(m_glTexture))
//  {
//    GUL_LOG_DEBUG("Image Opengl texture deleted!");
//    glDeleteTextures(1, &m_glTexture);
//  }
//#endif

//#ifdef LIBOPENCL_FOUND
//  clReleaseMemObject(m_clImage);
//#endif
}

template<typename T>
void gul::ImageT<T>::transferSharedResourceFrom(const SharedResource& newOwner)
{
  m_pData = static_cast<const ImageT<T>&>(newOwner).m_pData;

#ifdef LIBOPENGL_FOUND
  m_glTexture = static_cast<const ImageT<T>&>(newOwner).m_glTexture;
#endif

#ifdef LIBOPENCL_FOUND
  m_clImage = static_cast<const ImageT<T>&>(newOwner).m_clImage;
#endif
}

template<typename T>
gul::ImageT<T>* gul::ImageT<T>::createSharedResourceOwner(void) const
{
  gul::ImageT<T>* newImage = new gul::ImageT<T>();
  newImage->m_width = m_width;
  newImage->m_height = m_height;
  newImage->m_imageFormat = m_imageFormat;
  int size = GetWidth() * GetHeight() * GetNumberOfChannels();
  newImage->m_pData = new OnDemandMemory<T>(size);

//#ifdef LIBOPENGL_FOUND
//  glGenTextures(1, &newImage->m_glTexture);
//  glBindTexture(GL_TEXTURE_2D, newImage->m_glTexture);
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//  glBindTexture(GL_TEXTURE_2D, 0);

//  GLenum glError;
//  if((glError = glGetError()) != GL_NO_ERROR)
//  {
//    GUL_LOG_WARNING("OpenGL could create texture (code %d) : %s", glError, gluErrorString(glError));
//  }

//# ifdef LIBOPENCL_FOUND
//  CLContext* pCurrentContext = CLContext::GetCurrentContext();

//  cl_int clError;
//  newImage->m_clImage = clCreateFromGLTexture2D(pCurrentContext->GetCLContext(),
//                                                CL_MEM_READ_WRITE,
//                                                GL_TEXTURE_2D,
//                                                0,
//                                                newImage->m_glTexture,
//                                                &clError);

//  if(clError != CL_SUCCESS)
//  {
//    GUL_LOG_WARNING("OpenCL could not create Image from GL Texture (code %d)", clError);
//  }
//# endif

//#else

//# ifdef LIBOPENCL_FOUND
//  CLContext* pCurrentContext = CLContext::GetCurrentContext();

//  cl_int clError;
//  struct _cl_image_format clFormat;
//  clFormat.image_channel_data_type = CL_UNORM_INT8;
//  clFormat.image_channel_order = CL_RGBA;
//  newImage->m_clImage = clCreateImage2D(pCurrentContext->GetCLContext(),
//                                        CL_MEM_READ_WRITE,
//                                        clFormat,
//                                        newImage->GetWidth(), newImage->GetHeight(),
//                                        newImage->GetPitch(),
//                                        nullptr,
//                                        &clError);
//  if(clError != CL_SUCCESS)
//  {
//    GUL_LOG_WARNING("OpenCL could not create Image (code %d)", clError);
//  }
//# endif
//#endif


  return newImage;
}

#ifdef LIBOPENGL_FOUND

template<typename T>
const GLuint& gul::ImageT<T>::GetGLTexture(void)
{
  GLenum glError;

#ifdef LIBOPENCL_FOUND
  if(m_isGLAquiredByCL)
  {
    CLContext* pCurrentContext = CLContext::GetCurrentContext();
    clEnqueueReleaseGLObjects(pCurrentContext->GetCurrentQueue(),
                              1, &m_clImage,
                              0, nullptr,
                              nullptr);
  }
#endif

  if(!m_isGLDataSynched)
  {
    glBindTexture(GL_TEXTURE_2D, m_glTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                 GetWidth(), GetHeight(), 0,
                 GL_RGBA, GL_UNSIGNED_BYTE,
                 GetDataConst());
    m_isGLDataSynched = true;

    if((glError = glGetError()) != GL_NO_ERROR)
    {
      GUL_LOG_WARNING("OpenGL could set buffer data (code %d) :", glError, gluErrorString(glError));
    }
  }

  return m_glTexture;
}

#endif

#ifdef LIBOPENCL_FOUND

template<typename T>
const cl_mem& gul::ImageT<T>::GetCLImage(void) const
{
  CLContext* pCurrentContext = CLContext::GetCurrentContext();
  clEnqueueAcquireGLObjects(pCurrentContext->GetCurrentQueue(),
                            1, &m_clImage,
                            0, nullptr,
                            nullptr);

  m_isGLAquiredByCL = true;
  return m_clImage;
}

#endif

