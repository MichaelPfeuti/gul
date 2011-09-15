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

#include "memleak.h"

template<typename T>
gul::Stack<T>::Stack(void)
{

}

template<typename T>
gul::Stack<T>::~Stack(void)
{

}

template<typename T>
void gul::Stack<T>::Push(const T& rElement)
{

}

template<typename T>
const T& gul::Stack<T>::Top(void) const
{
  return T();
}

template<typename T>
T& gul::Stack<T>::Top(void)
{
  return *(new T());
}

template<typename T>
T gul::Stack<T>::Pop(void)
{
  return T();
}

template<typename T>
void gul::Stack<T>::Clear(void)
{

}

template<typename T>
int gul::Stack<T>::Size(void)
{
  return 0;
}

template<typename T>
bool gul::Stack<T>::IsEmpty(void)
{
  return false;
}

#include "memleak_template_end.h"
