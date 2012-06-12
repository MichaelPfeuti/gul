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

#include "Assert.h"
#include "Misc.h"

template<typename T>
gul::StackBasic<T>::StackBasic(void)
  : list()
{
}

template<typename T>
gul::StackBasic<T>::~StackBasic(void)
{
}


template<typename T>
void gul::StackBasic<T>::Push(const T& rElement)
{
  this->list.Add(rElement);
}

template<typename T>
const T& gul::StackBasic<T>::Top(void) const
{
  ASSERT(this->list.Size() > 0)
  return this->list.Get(this->list.Size() - 1);
}

template<typename T>
T& gul::StackBasic<T>::Top(void)
{
  ASSERT(this->list.Size() > 0)
  return this->list.Get(this->list.Size() - 1);
}

template<typename T>
T gul::StackBasic<T>::Pop(void)
{
  ASSERT(this->list.Size() > 0)
  T removed = this->list.Get(this->list.Size() - 1);
  this->list.Remove(this->list.Size() - 1);
  return removed;
}

template<typename T>
void gul::StackBasic<T>::Clear(void)
{
  this->list.Clear();
}

template<typename T>
int gul::StackBasic<T>::Size(void) const
{
  return this->list.Size();
}

template<typename T>
bool gul::StackBasic<T>::IsEmpty(void) const
{
  return this->list.IsEmpty();
}

template<typename T>
bool gul::StackBasic<T>::Contains(const T& rElement) const
{
  return this->list.Contains(rElement);
}

template<typename T>
typename gul::StackBasic<T>::Iterator gul::StackBasic<T>::GetIterator(void)
{
  return Iterator(*this);
}
template<typename T>
const typename gul::StackBasic<T>::Iterator gul::StackBasic<T>::GetIterator(void) const
{
  return Iterator(*this);
}


template<typename T>
gul::StackBasic<T>::Iterator::Iterator(const gul::StackBasic<T>& s)
  : stack(s),
    currentIndex(s.Size())
{
}

template<typename T>
bool gul::StackBasic<T>::Iterator::HasNext(void) const
{
  return currentIndex > 0;
}

template<typename T>
T& gul::StackBasic<T>::Iterator::Next(void)
{
  --currentIndex;
  return const_cast<T&>(this->stack.list.Get(currentIndex));
}

template<typename T>
const T& gul::StackBasic<T>::Iterator::Next(void) const
{
  --currentIndex;
  return this->stack.list.Get(currentIndex);
}

template<typename T>
T& gul::StackBasic<T>::Iterator::Get(void)
{
  return const_cast<T&>(this->stack.list.Get(currentIndex));
}

template<typename T>
const T&  gul::StackBasic<T>::Iterator::Get(void) const
{
  return this->stack.list.Get(currentIndex);
}
