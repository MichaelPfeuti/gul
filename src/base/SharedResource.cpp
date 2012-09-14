/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011-2012 Michael Pfeuti.
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

gul::SharedResource::SharedResource(void)
  : pOwner(nullptr),
    pReferees(nullptr)
{
}

gul::SharedResource::~SharedResource(void)
{
  detachFromResource();
  GUL_DELETE(this->pOwner);
  GUL_DELETE(this->pReferees);
}

gul::SharedResource& gul::SharedResource::operator=(const SharedResource& other)
{
  ASSERT(other.pOwner != nullptr);
  ASSERT(other.pReferees == nullptr);
  ASSERT(other.pOwner->pReferees != nullptr);
  ASSERT(other.pOwner->pReferees->Size() > 0);

  if(this != &other)
  {
    detachFromResource();
    attachToResource(other);
  }

  return *this;
}

void gul::SharedResource::initConstructor(void)
{
  attachToNewResource(*this->createSharedResourceOwner());
}

void gul::SharedResource::initCopyConstructor(const gul::SharedResource& other)
{
  ASSERT(other.pOwner != nullptr);
  ASSERT(other.pReferees == nullptr);
  ASSERT(other.pOwner->pReferees != nullptr);
  ASSERT(other.pOwner->pReferees->Size() > 0);

  attachToResource(other);
}

void gul::SharedResource::detach(void)
{
  if(pOwner->pReferees->Size() > 1)
  {
    SharedResource* newOwner = pOwner->createSharedResourceOwner();
    detachFromResource();
    pOwner = newOwner;
    attachToNewResource(*newOwner);
  }
}

void gul::SharedResource::attachToNewResource(SharedResource& owner)
{
  this->pOwner = &owner;
  this->pOwner->pReferees = new gul::ArrayBasic<const gul::SharedResource*>();
  this->pOwner->pReferees->Add(this);
  transferSharedResourceFrom(*pOwner);
}

void gul::SharedResource::attachToResource(const SharedResource& otherReferee)
{
  this->pOwner = otherReferee.pOwner;
  this->pOwner->pReferees->Add(this);
  transferSharedResourceFrom(*pOwner);
}

void gul::SharedResource::detachFromResource(void)
{
  if(!isOwner())
  {
    this->pOwner->pReferees->RemoveElement(this);

    if(isLastReferee())
    {
      this->pOwner->deleteSharedResource();
      GUL_DELETE(this->pOwner);
    }
    this->pOwner = nullptr;
  }
}

bool gul::SharedResource::isLastReferee(void) const
{
  return this->pOwner->pReferees->Size() == 0;
}

bool gul::SharedResource::isOwner(void) const
{
  return this->pOwner == nullptr;
}
