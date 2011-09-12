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
gul::List<T>::List(void)
  : pHead(nullptr),
    pTail(nullptr),
    size(0)
{
}

template<typename T>
template<typename U>
gul::List<T>::List(const gul::Container<U>& rContainer)
{
  FAIL("not implemented");
}

template<typename T>
gul::List<T>::~List(void)
{
}

template<typename T>
int gul::List<T>::Size(void) const
{
  return this->size;
}

template<typename T>
bool gul::List<T>::IsEmpty(void) const
{
  return this->size == 0;
}

template<typename T>
void gul::List<T>::Add(const T& rElement)
{

}

template<typename T>
void gul::List<T>::Add(const T& rElement, int index)
{
  ASSERT(index > 0);

}

template<typename T>
T& gul::List<T>::Get(int index)
{
  ListElement<T>* pCur = this->pHead;
  while(index > 0)
  {
    pCur = pCur->pNext;
    --index;
  }
  return pCur->data;
}

template<typename T>
const T& gul::List<T>::Get(int index) const
{
  ASSERT(index > 0);
  ASSERT(index < this->size);

  return this->pData[index];
}

template<typename T>
bool gul::List<T>::Contains(const T& rElement) const
{
  return this->IndexOf(rElement) != gul::NOT_FOUND;
}

template<typename T>
int gul::List<T>::IndexOf(const T& rElement) const
{
  ListElement<T>* pCur = this->pHead;
  int i = 0;
  do
  {
    if(this->pHead->data == pCur->data)
    {
      return i;
    }

    pCur = pCur->pNext;

  } while(pCur!=pTail);
  return gul::NOT_FOUND;
}

template<typename T>
void gul::List<T>::Remove(int index)
{

}

template<typename T>
void gul::List<T>::RemoveElement(const T& rElement)
{

}

template<typename T>
void gul::List<T>::Clear(void)
{

}

#include "memleak_template_end.h"
