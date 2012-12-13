/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011-2013 Michael Pfeuti.
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

DEFINE_TPL_RTTI(gul::Array)

template<typename T>
void gul::Array<T>::save(gul::XMLNode& node) const
{
  for(int i = 0; i < this->Size(); ++i)
  {
    gul::XMLNode childNode = node.AppendChild();
    gul::XMLSerializable::performSave(this->Get(i), childNode);
  }
}

template<typename T>
void gul::Array<T>::load(const gul::XMLNode& node)
{
  gul::XMLNode child = node.GetFirstChild();
  while(child.IsValid())
  {
    T newInst;
    performLoad(newInst, child);
    this->Add(newInst);
    child = child.GetNextSibling();
  }
}

