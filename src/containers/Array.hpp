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
#include "memleak.h"

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

}

template<typename T>
void gul::Array<T>::Add(const T& rElement, int index)
{
  ASSERT(index > 0);

}

template<typename T>
T& gul::Array<T>::Get(int index)
{
  FAIL("NOT IMPLEMENTED");
  return *pData;
}

template<typename T>
const T& gul::Array<T>::Get(int index) const
{
  ASSERT(index > 0);
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

}

template<typename T>
void gul::Array<T>::RemoveElement(const T& rElement)
{

}

template<typename T>
void gul::Array<T>::Clear(void)
{

}

#include "memleak_template_end.h"
