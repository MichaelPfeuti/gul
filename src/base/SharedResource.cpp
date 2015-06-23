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

#include "SharedResource.h"
#include "Log.h"

/**
 * @brief Default constructor does not setup or do anything
 *
 * You should call initConstructor in your subclass constructors when
 * you need data allocation.
 */
gul::SharedResource::SharedResource(void)
  : m_pOwner(nullptr),
    m_pReferencees(nullptr)
{
}

/**
 * @brief Detaches itself from the owner
 * Destroys also the referee list if this instance is an owner.
 */
gul::SharedResource::~SharedResource(void)
{
  detachFromOwner();
  GUL_ASSERT(this->m_pOwner == nullptr);
  GUL_DELETE(this->m_pReferencees);
}

/**
 * @brief Remove yourself from you owner and assign yourself the other's owner.
 * @param other A referee that has an owner.
 * @return *this
 */
gul::SharedResource& gul::SharedResource::operator=(const SharedResource& rOther)
{
  GUL_ASSERT(rOther.m_pOwner != nullptr);
  GUL_ASSERT(rOther.m_pReferencees == nullptr);
  GUL_ASSERT(rOther.m_pOwner->m_pReferencees != nullptr);
  GUL_ASSERT(rOther.m_pOwner->m_pReferencees->Size() > 0);

  if(this != &rOther)
  {
    if(!isOwner() && isOnlyReferencee() && isResourceDataSizeEqual(rOther))
    {
      copyDataFrom(rOther);
    }
    else
    {
      detachFromOwner();
      attachToResource(rOther);
    }
  }

  return *this;
}

/**
 * @brief Create your owner for the shared data.
 *
 * Call this method in all your constructors that need to allocate
 * data.
 *
 * Note: data allocation is done only through the callbacks of this class.
 *
 * Note: the true constructor is disabled because pure virtual
 *       methods need to be called. This would no be allowed by the
 *       C++ from the constructor of this class.
 */
void gul::SharedResource::initConstructor(void)
{
  attachToNewOwner(*this->createSharedResourceOwner());
}

/**
 * @brief Attach yourself to the other shared resource
 * @param other A referee that has an owner.
 *
 * Call this method in all copy constructor.
 *
 * Note: the true copy constructor is disabled because pure virtual
 *       methods need to be called. This would no be allowed by the
 *       C++ from the copy constructor of this class.
 */
void gul::SharedResource::initCopyConstructor(const gul::SharedResource& other)
{
  GUL_ASSERT(other.m_pOwner != nullptr);
  GUL_ASSERT(other.m_pReferencees == nullptr);
  GUL_ASSERT(other.m_pOwner->m_pReferencees != nullptr);
  GUL_ASSERT(other.m_pOwner->m_pReferencees->Size() > 0);

  attachToResource(other);
}

/**
 * @brief Detach yourself from your shared owner and create your own.
 *
 * Here it is important to understand the mechanism of the SharedResource.
 *
 * If this instance is the only referee then no further action is needed.
 * In other words no data is shared.
 *
 * If the data is shared then a new owner for this instance is created
 * and assigned to it. The data is copied from the previous owner by calling
 * copyDataFrom() after createSharedResourceOwner().
 */
void gul::SharedResource::detach(void)
{
  if(!isOnlyReferencee())
  {
    GUL_LOG_DEBUG("gul::SharedResource::detach %p causes copy", this);

    SharedResource* newOwner = m_pOwner->createSharedResourceOwner();
    newOwner->copyDataFrom(*m_pOwner);
    detachFromOwner();
    m_pOwner = newOwner;
    attachToNewOwner(*newOwner);
  }
}

/**
 * @brief Initialize owner and attache yourself to the owner.
 * @param owner new and uninitialized resource owner
 *
 * The resource owner has not a referee list. This list is allocated here.
 * After initializing the transferSharedResourceFrom() hook is called for
 * the subclass to react to the new owner and get the data pointers from
 * the owner.
 */
void gul::SharedResource::attachToNewOwner(SharedResource& owner)
{
  this->m_pOwner = &owner;
  this->m_pOwner->m_pReferencees = new gul::ArrayBasic<const gul::SharedResource*>();
  this->m_pOwner->m_pReferencees->Add(this);
  transferSharedResourceFrom(*m_pOwner);
}

/**
 * @brief Attach yourself to the otherReferee's owner
 * @param otherReferee
 *
 * Copy the owner data and add yourself to the referee list of the new owner.
 * Afterwards the transferSharedResourceFrom() hook is called for
 * the subclass to react to the new owner and get the data pointers from
 * the owner.
 */
void gul::SharedResource::attachToResource(const SharedResource& otherReferencee)
{
  this->m_pOwner = otherReferencee.m_pOwner;
  this->m_pOwner->m_pReferencees->Add(this);
  transferSharedResourceFrom(*m_pOwner);
}

/**
 * @brief Detach yourself from the owner and delete it if you were the only referee.
 */
void gul::SharedResource::detachFromOwner(void)
{
  if(!isOwner())
  {
    if(isOnlyReferencee())
    {
      this->m_pOwner->m_pReferencees->RemoveElement(this);

      this->m_pOwner->deleteSharedResource();
      GUL_DELETE(this->m_pOwner);
    }
    else
    {
      this->m_pOwner->m_pReferencees->RemoveElement(this);
    }
    this->m_pOwner = nullptr;
  }
}

bool gul::SharedResource::isOnlyReferencee(void) const
{
  return this->m_pOwner->m_pReferencees->Size() == 1;
}

bool gul::SharedResource::isOwner(void) const
{
  return this->m_pOwner == nullptr;
}
