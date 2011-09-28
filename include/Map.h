#pragma once
#ifndef _GUL_CONTAINERS_MAP_H_
#define _GUL_CONTAINERS_MAP_H_
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

#include "Container.h"
#include "List.h"

namespace gul
{

template<typename K, typename V>
class Map
{
  public:
    Map(void);
    virtual ~Map(void);

    int Size(void) const;
    bool IsEmpty(void) const;

    V& Get(const K& rKey);
    const V& Get(const K &rKey) const;

    void Add(const K& rKey, const V& rValue);
    void Remove(const K& rKey);
    void Clear(void);

    bool Contains(const K& rKey) const;

    const Container<K>& GetKeys(void) const;
    const Container<V>& GetValues(void) const;

  private:
    List<K> keys;
    List<V> values;
};

}

#include "../src/containers/Map.hpp"

#endif
