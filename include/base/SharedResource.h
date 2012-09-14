#pragma once
#ifndef _GUL_BASE_SHARED_RESOURCE_H_
#define _GUL_BASE_SHARED_RESOURCE_H_
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

#include "ArrayBasic.h"
#include "Cloneable.h"

namespace gul
{

  class SharedResource
  {
    protected:
      SharedResource(void);
      SharedResource(const SharedResource& other) = delete;
      virtual ~SharedResource(void);
      virtual SharedResource& operator=(const SharedResource& other);

      void initConstructor(void);
      void initCopyConstructor(const gul::SharedResource& other);
      void detach(void);

      virtual SharedResource* createSharedResourceOwner(void) const = 0;
      virtual void deleteSharedResource(void) = 0;
      virtual void transferSharedResourceFrom(const SharedResource& newOwner) = 0;

    private:
      void attachToNewResource(SharedResource& owner);
      void attachToResource(const SharedResource& otherReferee);
      void detachFromResource(void);
      bool isLastReferee(void) const;
      bool isOwner(void) const;

    private:
      SharedResource* pOwner;
      gul::ArrayBasic<const SharedResource*>* pReferees;

  };

}

#endif
