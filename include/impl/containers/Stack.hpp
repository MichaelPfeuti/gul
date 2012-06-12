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

DEFINE_TPL_RTTI(gul::Stack)


template<typename T>
void gul::Stack<T>::save(pugi::xml_node& node) const
{
  const typename gul::Stack<T>::Iterator it = this->GetIterator();
  while(it.HasNext())
  {
    pugi::xml_node childNode = node.append_child();
    gul::XMLSerializable::performSave(it.Next(), childNode);
  }
}

template<typename T>
void gul::Stack<T>::load(const pugi::xml_node& node)
{
  pugi::xml_node child = node.first_child();
  Stack reverseStack;
  while(!child.empty())
  {
    T newInst;
    gul::XMLSerializable::performLoad(newInst, child);
    reverseStack.Push(newInst);
    child = child.next_sibling();
  }

  while(!reverseStack.IsEmpty())
  {
    this->Push(reverseStack.Pop());
  }
}
