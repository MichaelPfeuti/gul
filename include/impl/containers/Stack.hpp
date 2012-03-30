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
#include "Misc.h"

template<typename T>
gul::Stack<T>::Stack(void)
  : list()
{
}

template<typename T>
gul::Stack<T>::~Stack(void)
{
}


template<typename T>
void gul::Stack<T>::Push(const T& rElement)
{
  this->list.Add(rElement);
}

template<typename T>
const T& gul::Stack<T>::Top(void) const
{
  ASSERT(this->list.Size() > 0)
  return this->list.Get(this->list.Size() - 1);
}

template<typename T>
T& gul::Stack<T>::Top(void)
{
  ASSERT(this->list.Size() > 0)
  return this->list.Get(this->list.Size() - 1);
}

template<typename T>
T gul::Stack<T>::Pop(void)
{
  ASSERT(this->list.Size() > 0)
  T removed = this->list.Get(this->list.Size() - 1);
  this->list.Remove(this->list.Size() - 1);
  return removed;
}

template<typename T>
void gul::Stack<T>::Clear(void)
{
  this->list.Clear();
}

template<typename T>
int gul::Stack<T>::Size(void) const
{
  return this->list.Size();
}

template<typename T>
bool gul::Stack<T>::IsEmpty(void) const
{
  return this->list.IsEmpty();
}

template<typename T>
bool gul::Stack<T>::Contains(const T& rElement) const
{
  return this->list.Contains(rElement);
}

template<typename T>
void gul::Stack<T>::Save(pugi::xml_node& node, bool resetMode) const
{
  GUL_UNUSED_VAR(node);
  GUL_UNUSED_VAR(resetMode);
  node.set_name("gul::Stack<T>");
}

template<typename T>
void* gul::Stack<T>::Load(const pugi::xml_node& node, bool resetMode) const
{
  GUL_UNUSED_VAR(node);
  GUL_UNUSED_VAR(resetMode);
  return new Stack<T>();
}
