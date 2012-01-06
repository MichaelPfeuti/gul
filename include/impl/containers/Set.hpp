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
#include "memleak.h"

template<typename T>
gul::Set<T>::Set(void)
  : list()
{
}

template<typename T>
gul::Set<T>::~Set(void)
{
}

template<typename T>
int gul::Set<T>::Size(void) const
{
  return this->list.Size();
}

template<typename T>
bool gul::Set<T>::IsEmpty(void) const
{
  return this->list.IsEmpty();
}

template<typename T>
bool gul::Set<T>::Contains(const T& rElement) const
{
  return this->list.Contains(rElement);
}

template<typename T>
void gul::Set<T>::Add(const T& rElement)
{
  if(!this->list.Contains(rElement))
    this->list.Add(rElement);
}

template<typename T>
void gul::Set<T>::Remove(const T& rElement)
{
  ASSERT(this->list.Contains(rElement));
  this->list.RemoveElement(rElement);
}

template<typename T>
void gul::Set<T>::Clear(void)
{
  this->list.Clear();
}

template<typename T>
void gul::Set<T>::Save(pugi::xml_node& node, bool resetMode) const
{
  node.set_name("gul::Set<T>");
}

template<typename T>
void* gul::Set<T>::Load(const pugi::xml_node& node, bool resetMode) const
{
  return new Set<T>();
}


#include "memleak_template_end.h"
