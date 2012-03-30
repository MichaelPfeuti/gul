/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011 Michael Pfeuti.
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
** FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
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
#include "3rdParty/pugi/pugixml.hpp"
#include <cstring>

template<typename T>
gul::Array<T>::Array(void)
  : pData(new T[10]),
    size(0),
    reservedMemoryBlocks(10)
{
}

template<typename T>
gul::Array<T>::Array(int initSize)
  : pData(new T[initSize]),
    size(0),
    reservedMemoryBlocks(initSize)
{
}

template<typename T>
gul::Array<T>::Array(const gul::Array<T>& rArray)
  : pData(new T[rArray.Size()]),
    size(rArray.Size()),
    reservedMemoryBlocks(rArray.Size())
{
  memcpy(this->pData, rArray.pData, rArray.Size()*sizeof(T));
}

template<typename T>
template<typename U>
gul::Array<T>::Array(const gul::Container<U>& rContainer)
{
  FAIL("not implemented");
}

template<typename T>
gul::Array<T>::~Array(void)
{
  GUL_DELETE_ARRAY(this->pData);
}

template<typename T>
gul::Array<T>& gul::Array<T>::operator=(const gul::Array<T>& rArray)
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
int gul::Array<T>::Size(void) const
{
  return this->size;
}

template<typename T>
bool gul::Array<T>::IsEmpty(void) const
{
  return this->size == 0;
}

template<typename T>
void gul::Array<T>::Add(const T& rElement)
{
  this->Add(rElement, this->size);
}

template<typename T>
void gul::Array<T>::Add(const T& rElement, int index)
{
  ASSERT(index >= 0);
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
T& gul::Array<T>::Get(int index)
{
  // TODO: remove duplicated code (see const version)
  ASSERT(index >= 0);
  ASSERT(index < this->size);

  return this->pData[index];
}

template<typename T>
const T& gul::Array<T>::Get(int index) const
{
  ASSERT(index >= 0);
  ASSERT(index < this->size);

  return this->pData[index];
}

template<typename T>
bool gul::Array<T>::Contains(const T& rElement) const
{
  return this->IndexOf(rElement) != gul::NOT_FOUND;
}

template<typename T>
int gul::Array<T>::IndexOf(const T& rElement) const
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
void gul::Array<T>::Remove(int index)
{
  ASSERT(index >= 0);
  ASSERT(index < this->size);

  // when the new item is not appended we need to move the memory content
  if(index < this->size - 1)
  {
    memmove(this->pData + index, this->pData + index + 1, sizeof(T) * (this->size - index - 1));
  }
  --(this->size);
}

template<typename T>
void gul::Array<T>::RemoveElement(const T& rElement)
{
  int idx = this->IndexOf(rElement);
  this->Remove(idx);
}

template<typename T>
void gul::Array<T>::Clear(void)
{
  this->size = 0;
}

template<typename T>
void gul::Array<T>::save(pugi::xml_node& node) const
{
  for(int i = 0; i < this->Size(); ++i)
  {
    pugi::xml_node childNode = node.append_child();
    gul::XMLSerializable::performSave(this->Get(i), childNode);
  }
}

template<typename T>
void gul::Array<T>::load(const pugi::xml_node& node)
{
  pugi::xml_node child = node.first_child();
  while (!child.empty())
  {
    T newInst;
    performLoad(newInst, child);
    this->Add(newInst);
    child = child.next_sibling();
  }
}
