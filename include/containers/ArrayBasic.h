#pragma once
#ifndef _GUL_CONTAINERS_ARRAY_BASIC_H_
#define _GUL_CONTAINERS_ARRAY_BASIC_H_
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

namespace gul
{

  template<typename T>
  class ArrayBasic
  {
    public:
      class Iterator
      {
        private:
          Iterator(const ArrayBasic<T>& array);

        public:
          bool HasNext(void) const;

          T& Next(void);
          const T& Next(void) const;

          T& Get(void);
          const T& Get(void) const;

        private:
          const ArrayBasic<T>& array;
          mutable int currentIndex;

          friend class ArrayBasic<T>;
      };

    public:
      ArrayBasic(void);
      explicit ArrayBasic(int initSize);

      virtual ~ArrayBasic(void);

      ArrayBasic(const ArrayBasic& rArray);
      ArrayBasic& operator=(const ArrayBasic& rArray);

      int Size(void) const;
      bool IsEmpty(void) const;

      void Add(const T& element);
      void Add(const T& element, int index);

      T& Get(int index);
      const T& Get(int index) const;

      bool Contains(const T& element) const;
      int IndexOf(const T& element) const;

      void Remove(int index);
      void RemoveElement(const T& element);

      void Clear(void);

      Iterator GetIterator(void);
      const Iterator GetIterator(void) const ;

    private:
      T* pData;
      int size;
      int reservedMemoryBlocks;
  };

}

#include "impl/containers/ArrayBasic.hpp"

#endif
