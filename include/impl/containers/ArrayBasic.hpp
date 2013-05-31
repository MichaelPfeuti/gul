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

#include "Assert.h"
#include "ContainerConstants.h"
#include "Misc.h"
#include "Math.h"
#include "String.h"
#include <cstring>

template<typename T>
gul::ArrayBasic<T>::ArrayBasic(void)
  : pData(new T[10]),
    size(0),
    reservedMemoryBlocks(10)
{
}

template<typename T>
gul::ArrayBasic<T>::ArrayBasic(int initSize)
  : pData(new T[initSize]),
    size(0),
    reservedMemoryBlocks(initSize)
{
}

template<typename T>
gul::ArrayBasic<T>::ArrayBasic(const gul::ArrayBasic<T>& rArray)
  : pData(new T[rArray.Size()]),
    size(rArray.Size()),
    reservedMemoryBlocks(rArray.Size())
{
  memcpy(this->pData, rArray.pData, rArray.Size()*sizeof(T));
}

template<typename T>
gul::ArrayBasic<T>::~ArrayBasic(void)
{
  GUL_DELETE_ARRAY(this->pData);
}

template<typename T>
gul::ArrayBasic<T>& gul::ArrayBasic<T>::operator=(const gul::ArrayBasic<T>& rArray)
{
  if(this != &rArray)
  {
    GUL_DELETE_ARRAY(this->pData);
    this->pData = new T[rArray.Size()];
    memcpy(this->pData, rArray.pData, rArray.Size()*sizeof(T));
    this->size = rArray.Size();
    this->reservedMemoryBlocks = this->size;
  }
  return *this;
}

template<typename T>
int gul::ArrayBasic<T>::Size(void) const
{
  return this->size;
}

template<typename T>
bool gul::ArrayBasic<T>::IsEmpty(void) const
{
  return this->size == 0;
}

template<typename T>
void gul::ArrayBasic<T>::Add(const T& rElement)
{
  this->Add(rElement, this->size);
}

template<typename T>
void gul::ArrayBasic<T>::Add(const T& rElement, int index)
{
  GUL_ASSERT(index >= 0);
  int insertIndex = gul::min(index, this->size);

  // do we need to allocate more memory?
  if(this->size + 1 >= this->reservedMemoryBlocks)
  {
    int oldBlockCount = this->reservedMemoryBlocks;
    this->reservedMemoryBlocks <<= 1;

    T* newMemory = new T[this->reservedMemoryBlocks];
    memcpy(newMemory, this->pData, oldBlockCount * sizeof(T));

    GUL_DELETE_ARRAY(this->pData);
    this->pData = newMemory;
  }

  // when the new item is not appended we need to move the memory content
  if(insertIndex < this->size - 1)
  {
    memmove(this->pData + insertIndex + 1, this->pData + insertIndex, sizeof(T) * (this->size - insertIndex));
  }

  // copy element into array
  this->pData[insertIndex] = T(rElement);
  ++(this->size);
}

template<typename T>
T& gul::ArrayBasic<T>::Get(int index)
{
  // TODO: remove duplicated code (see const version)
  GUL_ASSERT(index >= 0);
  GUL_ASSERT(index < this->size);

  return this->pData[index];
}

template<typename T>
const T& gul::ArrayBasic<T>::Get(int index) const
{
  GUL_ASSERT(index >= 0);
  GUL_ASSERT(index < this->size);

  return this->pData[index];
}

template<typename T>
bool gul::ArrayBasic<T>::Contains(const T& rElement) const
{
  return this->IndexOf(rElement) != gul::NOT_FOUND;
}

template<typename T>
int gul::ArrayBasic<T>::IndexOf(const T& rElement) const
{
  for(int i = 0; i < this->size; ++i)
  {
    if(this->pData[i] == rElement)
    {
      return i;
    }
  }
  return gul::NOT_FOUND;
}

template<typename T>
void gul::ArrayBasic<T>::Remove(int index)
{
  GUL_ASSERT(index >= 0);
  GUL_ASSERT(index < this->size);

  // when the new item is not appended we need to move the memory content
  if(index < this->size - 1)
  {
    memmove(this->pData + index, this->pData + index + 1, sizeof(T) * (this->size - index - 1));
  }
  --(this->size);
}

template<typename T>
void gul::ArrayBasic<T>::RemoveElement(const T& rElement)
{
  int idx = this->IndexOf(rElement);
  this->Remove(idx);
}

template<typename T>
void gul::ArrayBasic<T>::Clear(void)
{
  this->size = 0;
}

template<typename T>
typename gul::ArrayBasic<T>::Iterator gul::ArrayBasic<T>::GetIterator(void)
{
  return Iterator(*this);
}
template<typename T>
const typename gul::ArrayBasic<T>::Iterator gul::ArrayBasic<T>::GetIterator(void) const
{
  return Iterator(*this);
}


template<typename T>
gul::ArrayBasic<T>::Iterator::Iterator(const gul::ArrayBasic<T>& arr)
  : array(arr),
    currentIndex(-1)
{
}

template<typename T>
bool gul::ArrayBasic<T>::Iterator::HasNext(void) const
{
  return currentIndex < array.Size() - 1;
}

template<typename T>
T& gul::ArrayBasic<T>::Iterator::Next(void)
{
  ++currentIndex;
  return const_cast<T&>(this->array.Get(currentIndex));
}

template<typename T>
const T& gul::ArrayBasic<T>::Iterator::Next(void) const
{
  ++currentIndex;
  return this->array.Get(currentIndex);
}

template<typename T>
T& gul::ArrayBasic<T>::Iterator::Get(void)
{
  return const_cast<T&>(this->array.Get(currentIndex));
}

template<typename T>
const T&  gul::ArrayBasic<T>::Iterator::Get(void) const
{
  return this->array.Get(currentIndex);
}
