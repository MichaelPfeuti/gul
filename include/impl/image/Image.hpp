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
#include "Traits.h"

DEFINE_TPL_RTTI(gul::ImageT);

template<typename T>
gul::ImageT<T>::ImageT(void)
  : m_pData(nullptr),
    m_width(0),
    m_height(0),
    m_imageFormat(IF_UNDEFINED),
    m_pSynchStatus(nullptr)
{
}

template<typename T>
gul::ImageT<T>::ImageT(int w, int h, ImageFormat imageFormat)
  : m_pData(nullptr),
    m_width(w),
    m_height(h),
    m_imageFormat(imageFormat),
    m_pSynchStatus(nullptr)
{
  initConstructor();
}

template<typename T>
gul::ImageT<T>::ImageT(int w, int h, ImageFormat imageFormat, const T* data)
  : m_pData(nullptr),
    m_width(w),
    m_height(h),
    m_imageFormat(imageFormat),
    m_pSynchStatus(nullptr)
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
    m_pSynchStatus(nullptr)
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
  synchDataToCPU();
  return m_pData->GetData();
}

template<typename T>
const T* gul::ImageT<T>::GetData(void) const
{
  synchDataToCPU();
  return m_pData->GetData();
}

template<typename T>
T* gul::ImageT<T>::GetData(void)
{
  detach();
  synchDataToCPU();
  m_pSynchStatus->isGPUDataRecent = false;
  return m_pData->GetData();
}

template<typename T>
const T* gul::ImageT<T>::GetScanlineConst(int scanline) const
{
  GUL_ASSERT(scanline >= 0 && scanline <= GetHeight());

  synchDataToCPU();
  return m_pData->GetData() + scanline*GetPitch();
}

template<typename T>
const T* gul::ImageT<T>::GetScanline(int scanline) const
{
  GUL_ASSERT(scanline >= 0 && scanline <= GetHeight());

  synchDataToCPU();
  return m_pData->GetData() + scanline*GetPitch();
}

template<typename T>
T* gul::ImageT<T>::GetScanline(int scanline)
{
  GUL_ASSERT(scanline >= 0 && scanline <= GetHeight());

  detach();
  synchDataToCPU();
  m_pSynchStatus->isGPUDataRecent = false;
  return m_pData->GetData() + scanline*GetPitch();
}

template<typename T>
const T& gul::ImageT<T>::GetColorConst(int x, int y, int channel) const
{
  GUL_ASSERT(channel >= 0 && channel <= GetNumberOfChannels());
  GUL_ASSERT(x >= 0 && x <= GetWidth());
  GUL_ASSERT(y >= 0 && y <= GetHeight());

  synchDataToCPU();
  return m_pData->GetData()[y*GetPitch() + x*GetNumberOfChannels() + channel];
}

template<typename T>
const T& gul::ImageT<T>::GetColor(int x, int y, int channel) const
{
  GUL_ASSERT(channel >= 0 && channel <= GetNumberOfChannels());
  GUL_ASSERT(x >= 0 && x <= GetWidth());
  GUL_ASSERT(y >= 0 && y <= GetHeight());

  synchDataToCPU();
  return m_pData->GetData()[y*GetPitch() + x*GetNumberOfChannels() + channel];
}

template<typename T>
T& gul::ImageT<T>::GetColor(int x, int y, int channel)
{
  GUL_ASSERT(channel >= 0 && channel <= GetNumberOfChannels());
  GUL_ASSERT(x >= 0 && x <= GetWidth());
  GUL_ASSERT(y >= 0 && y <= GetHeight());

  detach();
  synchDataToCPU();
  m_pSynchStatus->isGPUDataRecent = false;
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
  m_pSynchStatus->isCPUDataRecent = static_cast<const ImageT<T>&>(rOther).m_pSynchStatus->isCPUDataRecent;
  m_pSynchStatus->isGPUDataRecent = static_cast<const ImageT<T>&>(rOther).m_pSynchStatus->isGPUDataRecent;

  if(m_pSynchStatus->isCPUDataRecent)
  {
    memcpy(m_pData->GetData(),
           static_cast<const ImageT<T>&>(rOther).m_pData->GetData(),
           GetPitch()*m_height);
  }

  m_pCLImage->isGLAquiredByCL = static_cast<const ImageT<T>&>(rOther).m_pCLImage->isGLAquiredByCL;


  if(m_pSynchStatus->isGPUDataRecent)
  {
    // There is no easy way to copy GL textues
    // so we use opencl to copy the texture
    if(!m_pCLImage->isGLAquiredByCL)
    {
      aquireCLGLBinding();
    }

    CLContext* pCurrentContext = CLContext::GetCurrentContext();
    size_t origin[] = {0, 0, 0};
    size_t region[] = { (size_t) m_width, (size_t) m_height, 1};
    clEnqueueCopyImage(pCurrentContext->GetCurrentQueue(),
                       static_cast<const ImageT<T>&>(rOther).m_pCLImage->clImage, m_pCLImage->clImage,
                       origin, origin, region,
                       0, nullptr, nullptr);
  }
}

template<typename T>
void gul::ImageT<T>::deleteSharedResource(void)
{
  GUL_DELETE(m_pData);
  GUL_DELETE(m_pSynchStatus);

  realeaseCLGLBinding();

  if(glIsTexture(m_glTexture))
  {
    GUL_LOG_DEBUG("Image Opengl texture deleted!");
    glDeleteTextures(1, &m_glTexture);
  }

  if(isCLImageInitialized())
  {
    clReleaseMemObject(m_pCLImage->clImage);
  }
  GUL_DELETE(m_pCLImage);
}

template<typename T>
void gul::ImageT<T>::transferSharedResourceFrom(const SharedResource& newOwner)
{
  m_pData = static_cast<const ImageT<T>&>(newOwner).m_pData;
  m_pSynchStatus = static_cast<const ImageT<T>&>(newOwner).m_pSynchStatus;
  m_glTexture = static_cast<const ImageT<T>&>(newOwner).m_glTexture;
  m_pCLImage = static_cast<const ImageT<T>&>(newOwner).m_pCLImage;
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
  newImage->m_pSynchStatus = new SynchStatus();
  newImage->m_pSynchStatus->isCPUDataRecent = false;
  newImage->m_pSynchStatus->isGPUDataRecent = false;

  glGenTextures(1, &newImage->m_glTexture);
  glBindTexture(GL_TEXTURE_2D, newImage->m_glTexture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);

  GLenum glError;
  if((glError = glGetError()) != GL_NO_ERROR)
  {
    GUL_LOG_WARNING("OpenGL could create texture (code %d) : %s", glError, gluErrorString(glError));
  }

  newImage->m_pCLImage = new CLImageData();
  newImage->m_pCLImage->isGLAquiredByCL = false;

  return newImage;
}

template<typename T>
const GLuint& gul::ImageT<T>::GetGLTextureConst(void) const
{
  GLenum glError;

  realeaseCLGLBinding();

  if(!m_pSynchStatus->isGPUDataRecent)
  {
    glBindTexture(GL_TEXTURE_2D, m_glTexture);
    const T* pData = nullptr;
    if(m_pSynchStatus->isCPUDataRecent)
    {
      pData = m_pData->GetData();
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                 GetWidth(), GetHeight(), 0,
                 GL_RGBA, gul::Traits<T>::GetGLType(),
                 pData);

    if((glError = glGetError()) != GL_NO_ERROR)
    {
      GUL_LOG_WARNING("OpenGL could set buffer data (code %d) : %s", glError, gluErrorString(glError));
    }
  }

  m_pSynchStatus->isCPUDataRecent = true;
  m_pSynchStatus->isGPUDataRecent = true;

  return m_glTexture;
}

template<typename T>
const GLuint& gul::ImageT<T>::GetGLTexture(void)
{
  GetGLTextureConst();
  m_pSynchStatus->isCPUDataRecent = false;
  m_pSynchStatus->isGPUDataRecent = true;
  return m_glTexture;
}

template<typename T>
void gul::ImageT<T>::realeaseCLGLBinding(void) const
{
  if(m_pCLImage->isGLAquiredByCL)
  {
    CLContext* pCurrentContext = CLContext::GetCurrentContext();
    clFinish(pCurrentContext->GetCurrentQueue());
    clEnqueueReleaseGLObjects(pCurrentContext->GetCurrentQueue(),
                              1, &m_pCLImage->clImage,
                              0, nullptr,
                              nullptr);
    m_pCLImage->isGLAquiredByCL = false;
  }
}

template<typename T>
void gul::ImageT<T>::aquireCLGLBinding(void) const
{
  if(!m_pCLImage->isGLAquiredByCL)
  {
    glFinish();
    CLContext* pCurrentContext = CLContext::GetCurrentContext();
    clEnqueueAcquireGLObjects(pCurrentContext->GetCurrentQueue(),
                              1, &m_pCLImage->clImage,
                              0, nullptr,
                              nullptr);
    m_pCLImage->isGLAquiredByCL = true;
  }
}

template<typename T>
bool gul::ImageT<T>::isCLImageInitialized(void) const
{
  return clGetImageInfo(m_pCLImage->clImage, CL_IMAGE_FORMAT,
                        0, nullptr, nullptr) == CL_INVALID_MEM_OBJECT;

}

template<typename T>
const cl_mem& gul::ImageT<T>::GetCLImageConst(void) const
{
  CLContext* pCurrentContext = CLContext::GetCurrentContext();
  cl_int clError;

  if(isCLImageInitialized())
  {
    m_pCLImage->clImage = clCreateFromGLTexture2D(pCurrentContext->GetCLContext(),
                                        CL_MEM_READ_WRITE,
                                        GL_TEXTURE_2D,
                                        0,
                                        GetGLTexture(),
                                        &clError);


    if(clError != CL_SUCCESS)
    {
      GUL_LOG_WARNING("OpenCL could not create Image (code %d)", clError);
    }
  }

  aquireCLGLBinding();

  if(!m_pSynchStatus->isGPUDataRecent &&
      m_pSynchStatus->isCPUDataRecent)
  {
    size_t origin[] = {0, 0, 0};
    size_t region[] = { (size_t) m_width, (size_t) m_height, 1};
    clError= clEnqueueWriteImage(pCurrentContext->GetCurrentQueue(),
                                 m_pCLImage->clImage,
                                 true, origin, region,
                                 GetPitch(), 0,
                                 m_pData->GetData(),
                                 0, nullptr, nullptr);
  }

  return m_pCLImage->clImage;
}

template<typename T>
const cl_mem& gul::ImageT<T>::GetCLImage(void)
{
  GetCLImageConst();
  m_pSynchStatus->isCPUDataRecent = false;
  m_pSynchStatus->isGPUDataRecent = true;
  return m_pCLImage->clImage;
}

template<typename T>
void gul::ImageT<T>::synchDataToCPU(void) const
{
  if(!m_pSynchStatus->isCPUDataRecent &&
      m_pSynchStatus->isGPUDataRecent)
  {
    if(!m_pCLImage->isGLAquiredByCL)
    {
      glBindTexture(GL_TEXTURE_2D, m_glTexture);
      glGetTexImage(GL_TEXTURE_2D,
                    0, GL_RGBA,
                    gul::Traits<T>::GetGLType(),
                    m_pData->GetData());
      GLenum glError;
      if((glError = glGetError()) != GL_NO_ERROR)
      {
        GUL_LOG_WARNING("OpenGL could not read back texture data (code %d) : %s", glError, gluErrorString(glError));
      }
    }
    else
    {
      CLContext* pCurrentContext = CLContext::GetCurrentContext();
      size_t origin[] = {0, 0, 0};
      size_t region[] = { (size_t) m_width, (size_t) m_height, 1};
      cl_int clError = clEnqueueReadImage(pCurrentContext->GetCurrentQueue(),
                                          m_pCLImage->clImage,
                                          true, origin, region,
                                          GetPitch(), 0,
                                          m_pData->GetData(),
                                          0, nullptr, nullptr);
      if(clError != CL_SUCCESS)
      {
        GUL_LOG_WARNING("OpenCL could not read Image (code %d)", clError);
      }
    }
  }
  m_pSynchStatus->isCPUDataRecent = true;
}

