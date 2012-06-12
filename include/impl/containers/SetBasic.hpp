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

#include "String.h"
#include "Assert.h"

template<typename T>
gul::SetBasic<T>::SetBasic(void)
  : list()
{
}

template<typename T>
gul::SetBasic<T>::~SetBasic(void)
{
}

template<typename T>
int gul::SetBasic<T>::Size(void) const
{
  return this->list.Size();
}

template<typename T>
bool gul::SetBasic<T>::IsEmpty(void) const
{
  return this->list.IsEmpty();
}

template<typename T>
bool gul::SetBasic<T>::Contains(const T& rElement) const
{
  return this->list.Contains(rElement);
}

template<typename T>
void gul::SetBasic<T>::Add(const T& rElement)
{
  if(!this->list.Contains(rElement))
    this->list.Add(rElement);
}

template<typename T>
void gul::SetBasic<T>::Remove(const T& rElement)
{
  ASSERT(this->list.Contains(rElement));
  this->list.RemoveElement(rElement);
}

template<typename T>
void gul::SetBasic<T>::Clear(void)
{
  this->list.Clear();
}

template<typename T>
typename gul::SetBasic<T>::Iterator gul::SetBasic<T>::GetIterator(void)
{
  return Iterator(*this);
}
template<typename T>
const typename gul::SetBasic<T>::Iterator gul::SetBasic<T>::GetIterator(void) const
{
  return Iterator(*this);
}


template<typename T>
gul::SetBasic<T>::Iterator::Iterator(const gul::SetBasic<T>& s)
  : set(s),
    currentIndex(-1)
{
}

template<typename T>
bool gul::SetBasic<T>::Iterator::HasNext(void) const
{
  return currentIndex < set.Size() - 1;
}

template<typename T>
T& gul::SetBasic<T>::Iterator::Next(void)
{
  ++currentIndex;
  return const_cast<T&>(this->set.list.Get(currentIndex));
}

template<typename T>
const T& gul::SetBasic<T>::Iterator::Next(void) const
{
  ++currentIndex;
  return this->set.list.Get(currentIndex);
}

template<typename T>
T& gul::SetBasic<T>::Iterator::Get(void)
{
  return const_cast<T&>(this->set.list.Get(currentIndex));
}

template<typename T>
const T&  gul::SetBasic<T>::Iterator::Get(void) const
{
  return this->set.list.Get(currentIndex);
}

