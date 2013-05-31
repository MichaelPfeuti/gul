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

#include "Assert.h"
#include "Misc.h"

template<typename K, typename V>
gul::MapBasic<K, V>::MapBasic(void)
  : keys(),
    values()
{
}

template<typename K, typename V>
gul::MapBasic<K, V>::~MapBasic(void)
{
}

template<typename K, typename V>
int gul::MapBasic<K, V>::Size(void) const
{
  GUL_ASSERT(this->keys.Size() == this->values.Size());
  return this->keys.Size();
}

template<typename K, typename V>
bool gul::MapBasic<K, V>::IsEmpty(void) const
{
  return this->Size() == 0;
}

template<typename K, typename V>
V& gul::MapBasic<K, V>::Get(const K& rKey)
{
  GUL_ASSERT(this->keys.Contains(rKey));

  int idx = this->keys.IndexOf(rKey);
  return this->values.Get(idx);
}

template<typename K, typename V>
const V& gul::MapBasic<K, V>::Get(const K& rKey) const
{
  GUL_ASSERT(this->keys.Contains(rKey));

  // TODO: duplication
  int idx = this->keys.IndexOf(rKey);
  return this->values.Get(idx);
}

template<typename K, typename V>
void gul::MapBasic<K, V>::Add(const K& rKey, const V& rValue)
{
  if(this->keys.Contains(rKey))
  {
    int idx = this->keys.IndexOf(rKey);
    this->values.Remove(idx);
    this->values.Add(rValue, idx);
  }
  else
  {
    this->keys.Add(rKey);
    this->values.Add(rValue);
  }
}

template<typename K, typename V>
void gul::MapBasic<K, V>::Remove(const K& rKey)
{
  GUL_ASSERT(this->keys.Contains(rKey));

  int idx = this->keys.IndexOf(rKey);
  this->keys.Remove(idx);
  this->values.Remove(idx);
}

template<typename K, typename V>
void gul::MapBasic<K, V>::Clear(void)
{
  this->keys.Clear();
  this->values.Clear();
}

template<typename K, typename V>
bool gul::MapBasic<K, V>::Contains(const K& rKey) const
{
  return this->keys.Contains(rKey);
}

template<typename K, typename V>
typename gul::MapBasic<K, V>::Iterator gul::MapBasic<K, V>::GetIterator(void)
{
  return Iterator(*this);
}

template<typename K, typename V>
const typename gul::MapBasic<K, V>::Iterator gul::MapBasic<K, V>::GetIterator(void) const
{
  return Iterator(*this);
}

template<typename K, typename V>
K& gul::MapBasic<K, V>::Pair::GetKey(void)
{
  return *this->key;
}

template<typename K, typename V>
const K& gul::MapBasic<K, V>::Pair::GetKey(void) const
{
  return *this->key;
}

template<typename K, typename V>
V& gul::MapBasic<K, V>::Pair::GetValue(void)
{
  return *this->value;
}

template<typename K, typename V>
const V& gul::MapBasic<K, V>::Pair::GetValue(void) const
{
  return *this->value;
}



template<typename K, typename V>
gul::MapBasic<K, V>::Iterator::Iterator(const gul::MapBasic<K, V>& m)
  : map(m),
    currentIndex(-1)
{
}

template<typename K, typename V>
bool gul::MapBasic<K, V>::Iterator::HasNext(void) const
{
  return currentIndex < map.Size() - 1;
}

template<typename K, typename V>
typename gul::MapBasic<K, V>::Pair gul::MapBasic<K, V>::Iterator::Next(void)
{
  ++currentIndex;
  currentPair.key = &const_cast<K&>(this->map.keys.Get(currentIndex));
  currentPair.value = &const_cast<V&>(this->map.values.Get(currentIndex));
  return currentPair;
}

template<typename K, typename V>
const typename gul::MapBasic<K, V>::Pair gul::MapBasic<K, V>::Iterator::Next(void) const
{
  ++currentIndex;
  currentPair.key = &const_cast<K&>(this->map.keys.Get(currentIndex));
  currentPair.value = &const_cast<V&>(this->map.values.Get(currentIndex));
  return currentPair;
}

template<typename K, typename V>
typename gul::MapBasic<K, V>::Pair gul::MapBasic<K, V>::Iterator::Get(void)
{
  return currentPair;
}

template<typename K, typename V>
const typename gul::MapBasic<K, V>::Pair gul::MapBasic<K, V>::Iterator::Get(void) const
{
  return currentPair;
}
