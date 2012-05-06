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
gul::List<T>::List(const gul::List<T>& rList)
  : pHead(nullptr),
    pTail(nullptr),
    size(0)
{
  this->copyAllData(rList);
}

template<typename T>
gul::List<T>::~List(void)
{
  this->Clear();
}

template<typename T>
gul::List<T>& gul::List<T>::operator=(const gul::List<T>& rList)
{
  if(this != &rList)
  {
    this->copyAllData(rList);
  }
  return *this;
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
  this->Add(rElement, this->size);
}

template<typename T>
void gul::List<T>::Add(const T& rElement, int index)
{
  ASSERT(index >= 0);

  int insertIndex = gul::min(index, this->size);
  ListElement<T>* pNew = new ListElement<T>(rElement);

  if(this->size == 0)
  {
    this->pHead = pNew;
    this->pTail = pNew;
  }
  else if(insertIndex == this->size)
  {
    this->pTail->pNext = pNew;
    pNew->pPrev = this->pTail;
    this->pTail = pNew;
  }
  else if(insertIndex == 0)
  {
    this->pHead->pPrev = pNew;
    pNew->pNext = this->pHead;
    this->pHead = pNew;
  }
  else
  {
    // find element to move
    ListElement<T>* pMove = this->pHead;
    for(int i = 0; i < insertIndex; ++i)
    {
      pMove = pMove->pNext;
    }

    pNew->pPrev = pMove->pPrev;
    pNew->pNext = pMove;

    pNew->pPrev->pNext = pNew;
    pNew->pNext->pPrev = pNew;
  }

  ++this->size;
}

template<typename T>
T& gul::List<T>::Get(int index)
{
  // TODO: remove code duplication
  ASSERT(index >= 0);
  ASSERT(index < this->size);

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
  ASSERT(index >= 0);
  ASSERT(index < this->size);

  ListElement<T>* pCur = this->pHead;
  while(index > 0)
  {
    pCur = pCur->pNext;
    --index;
  }
  return pCur->data;
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

  for(int i = 0; i < this->size; ++i)
  {
    if(rElement == pCur->data)
    {
      return i;
    }
    pCur = pCur->pNext;
  }

  return gul::NOT_FOUND;
}

template<typename T>
void gul::List<T>::Remove(int index)
{
  ASSERT(index >= 0);
  ASSERT(index < this->size);

  if(this->size == 1)
  {
    GUL_DELETE(this->pHead);
    this->pHead = nullptr;
    this->pTail = nullptr;
  }
  else if(index == 0)
  {
    this->pHead = this->pHead->pNext;
    GUL_DELETE(this->pHead->pPrev);
  }
  else if(index == this->size - 1)
  {
    this->pTail = this->pTail->pPrev;
    GUL_DELETE(this->pTail->pNext);
  }
  else
  {
    ListElement<T>* pCur = this->pHead;
    for(int i = 0; i < index; ++i)
    {
      pCur = pCur->pNext;
    }

    pCur->pPrev->pNext = pCur->pNext;
    pCur->pNext->pPrev = pCur->pPrev;
    GUL_DELETE(pCur);
  }

  --this->size;
}

template<typename T>
void gul::List<T>::RemoveElement(const T& rElement)
{
  int index = this->IndexOf(rElement);
  ASSERT(index != gul::NOT_FOUND);
  this->Remove(index);
}

template<typename T>
void gul::List<T>::Clear(void)
{
  ListElement<T>* pCur = this->pHead;
  ListElement<T>* pNext;
  for(int i = 0; i < this->size; ++i)
  {
    pNext = pCur->pNext;
    GUL_DELETE(pCur);
    pCur = pNext;
  }
  this->size = 0;
}

template<typename T>
void gul::List<T>::copyAllData(const List& rList)
{
  this->Clear();
  ListElement<T>* pCur = rList.pHead;
  for(int i = 0; i < rList.size; ++i)
  {
    this->Add(pCur->data);
    pCur = pCur->pNext;
  }
}

template<typename T>
void gul::List<T>::save(pugi::xml_node& node) const
{
  GUL_UNUSED_VAR(node);
}

template<typename T>
void gul::List<T>::load(const pugi::xml_node& node)
{
  GUL_UNUSED_VAR(node);
}
