#pragma once
#ifndef _GUL_CONTAINERS_STACK_BASIC_H_
#define _GUL_CONTAINERS_STACK_BASIC_H_
/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011-2013 Michael Pfeuti.
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

#include "ListBasic.h"

namespace gul
{

  template<typename T>
  class StackBasic
  {
    public:
      class Iterator
      {
        private:
          Iterator(const StackBasic<T>& list);

        public:
          bool HasNext(void) const;

          T& Next(void);
          const T& Next(void) const;

          T& Get(void);
          const T& Get(void) const;

        private:
          const StackBasic<T>& stack;
          mutable int currentIndex;

          friend class StackBasic<T>;
      };

      friend class Iterator;

    public:
      StackBasic(void);
      virtual ~StackBasic(void);

      void Push(const T& rElement);
      const T& Top(void) const;
      T& Top(void);
      T Pop(void);
      void Clear(void);
      int Size(void) const;
      bool IsEmpty(void) const;
      bool Contains(const T&) const;

      Iterator GetIterator(void);
      const Iterator GetIterator(void) const;

    private:
      ListBasic<T> list;
  };
}

#include "impl/containers/StackBasic.hpp"

#endif
