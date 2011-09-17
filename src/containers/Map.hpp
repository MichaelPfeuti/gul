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

template<typename K, typename V>
gul::Map<K,V>::Map(void)
{

}

template<typename K, typename V>
gul::Map<K,V>::~Map(void)
{

}

template<typename K, typename V>
int gul::Map<K,V>::Size(void) const
{
  return 0;
}

template<typename K, typename V>
bool gul::Map<K,V>::IsEmpty(void) const
{
  return false;
}

template<typename K, typename V>
V& gul::Map<K,V>::Get(const K& rKey)
{
    GUL_UNUSED_VAR(rKey);
  return *new V();
}

template<typename K, typename V>
const V& gul::Map<K,V>::Get(const K &rKey) const
{
  return V();
}

template<typename K, typename V>
void gul::Map<K,V>::Add(const K& rKey, const V& rValue)
{
    GUL_UNUSED_VAR(rKey);
    GUL_UNUSED_VAR(rValue);

}

template<typename K, typename V>
void gul::Map<K,V>::Remove(const K& rKey)
{
    GUL_UNUSED_VAR(rKey);
}

template<typename K, typename V>
void gul::Map<K,V>::Clear(void)
{

}

template<typename K, typename V>
bool gul::Map<K,V>::Contains(const K& rKey) const
{
    GUL_UNUSED_VAR(rKey);
  return false;
}

template<typename K, typename V>
gul::Container<K>* gul::Map<K,V>::GetKeys(void) const
{
  return nullptr;
}

template<typename K, typename V>
gul::Container<V>* gul::Map<K,V>::GetValues(void) const
{
  return nullptr;
}
