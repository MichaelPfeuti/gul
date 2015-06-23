#pragma once
#ifndef _GUL_BASE_SHARED_RESOURCE_H_
#define _GUL_BASE_SHARED_RESOURCE_H_
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

#include "gul_export.h"
#include "ArrayBasic.h"
#include "Cloneable.h"

namespace gul
{
  /**
   * @brief The SharedResource class
   *
   * This is the base class for managing shared resources. An existing
   * example that uses shared resources is the gul::Image class.
   *
   * The general idea behind the shared resources implementation is that
   * two kinds of SharedResource instances exist. One are the owners and
   * the others the referencees.\n
   * The owners are hidden from the outside (outside the SharedResource).
   * Their goal is to be the actual data owner. They hold a list of
   * referencees. Each referencee has one and only one owner. \n
   * NOTE: A referencee has ALWAYS an owner. \n
   * The situation for a one instance situation would be that we have
   * the referencee which is the class that the developer passes
   * around and uses in the code. Its owner is hidden inside the
   * referencee. When the referencee is deleted then is also deletes
   * the owner (of course only when it is the only referencee).
   * When there are more than one instanst of a class that share data
   * then they reference the same owner. When one detaches itself it
   * creates again a new owner for itself. \n
   * To sum up we have the referencee which we work with in the code
   * and a hidden owner that floats around behind the curtain.
   *
   * For a class the become a shared resource you must inherit from
   * the SharedResource class. All you need to do is implement
   * the three pure virtual methods createSharedResourceOwner()
   * deleteSharedResource(), transferSharedResourceFrom(),
   * isResourceDataSizeEqual() and copyDataFrom().
   *
   * createSharedResourceOwner():
   * Here the class usually creates a copy of itself with freshly
   * allocated memory. The new owner must be initialized such that
   * a successive copyDataFrom() call succeeds. So
   * createSharedResourceOwner just allocates the memory and
   * copyDataFrom() performs the copy if necessary.
   *
   * deleteSharedResource():
   * This deletes the memory that was allocated in
   * createSharedResourceOwner() for the owner.
   *
   * transferSharedResourceFrom():
   * This basically copies pointers around from the owner to itself
   * the referencee.
   *
   * isResourceDataSizeEqual():
   * Check if the data that is shared has the same size. This is
   * use to check if a data is just copied on assignment or if the
   * data owner from the assinged instance is used. This way we do
   * not free data that could be reused.
   *
   * copyDataFrom():
   * copy the data is the case isResourceDataSizeEqual() is true
   * and it the only referencee.
   *
   * example from gul::Image:
   *
   * @code{.cpp}
   * template<typename T>
   * void gul::ImageT<T>::deleteSharedResource(void)
   * {
   *   GUL_DELETE_ARRAY(m_pData);
   * }
   *
   * template<typename T>
   * void gul::ImageT<T>::transferSharedResourceFrom(const SharedResource& newOwner)
   * {
   *   m_pData = static_cast<const ImageT<T>&>(newOwner).m_pData;
   * }
   *
   * template<typename T>
   * gul::ImageT<T>* gul::ImageT<T>::createSharedResourceOwner(void) const
   * {
   *   gul::ImageT<T>* newImage = new gul::ImageT<T>();
   *   newImage->m_width = m_width;
   *   newImage->m_height = m_height;
   *   newImage->m_imageFormat = m_imageFormat;
   *   int size = GetWidth() * GetHeight() * GetNumberOfChannels();
   *   newImage->m_pData = new T[size];
   *   if(m_pData == NULL)
   *   {
   *     memset(newImage->m_pData, 0, sizeof(T)*size);
   *   }
   *   else
   *   {
   *     memcpy(newImage->m_pData, m_pData, sizeof(T)*size);
   *   }
   *   return newImage;
   * }
   *
   * template<typename T>
   * bool gul::ImageT<T>::isResourceDataSizeEqual(const SharedResource& rOther)
   * {
   *   return m_width == static_cast<const ImageT<T>&>(rOther).m_width &&
   *          m_height == static_cast<const ImageT<T>&>(rOther).m_height &&
   *          m_imageFormat == static_cast<const ImageT<T>&>(rOther).m_imageFormat;
   * }
   *
   * template<typename T>
   * void gul::ImageT<T>::copyDataFrom(const SharedResource& rOther)
   * {
   *   memcpy(m_pData, static_cast<const ImageT<T>&>(rOther).GetData(), GetPitch()*m_height);
   * }
   * @endcode
   */
  class GUL_EXPORT SharedResource
  {
    protected:
      SharedResource(void);
      /**
       * @brief Copy constructor is disabled on purpose.
       *
       * Copy constructor is disabled because pure virtual methods
       * need to be called. This would no be allowed by the C++ from
       * the copy constructor of this class.
       *
       * You should call initCopyConstructor in your subclass copy constructor.
       */
      SharedResource(const SharedResource&) = delete;
      virtual ~SharedResource(void);
      virtual SharedResource& operator=(const SharedResource& other);

      void initConstructor(void);
      void initCopyConstructor(const gul::SharedResource& other);
      void detach(void);

      virtual SharedResource* createSharedResourceOwner(void) const = 0;
      virtual void deleteSharedResource(void) = 0;
      virtual void transferSharedResourceFrom(const SharedResource& newOwner) = 0;
      virtual bool isResourceDataSizeEqual(const SharedResource& rOther) = 0;
      virtual void copyDataFrom(const SharedResource& rOther) = 0;

    private:
      void attachToNewOwner(SharedResource& owner);
      void attachToResource(const SharedResource& otherReferencee);
      void detachFromOwner(void);
      bool isOnlyReferencee(void) const;
      bool isOwner(void) const;

    private:
      /**
       * @brief This is empty for owners, but valid for referencees
       */
      SharedResource* m_pOwner;

      /**
       * @brief This is empty for referencees but filled for owners
       */
      gul::ArrayBasic<const SharedResource*>* m_pReferencees;

  };

}

#endif
