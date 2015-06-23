#pragma once
#ifndef _GUL_CONTAINERS_MAP_BASIC_H_
#define _GUL_CONTAINERS_MAP_BASIC_H_
/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011-2015 Michael Pfeuti.
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

#include "ListBasic.h"

namespace gul
{

  template<typename K, typename V>
  class MapBasic
  {
    public:
      class Pair
      {
        public:
          K& GetKey(void);
          const K& GetKey(void) const ;

          V& GetValue(void);
          const V& GetValue(void) const;

        private:
          K* key;
          V* value;

          friend class MapBasic<K, V>::Iterator;
      };

      class Iterator
      {
        private:
          Iterator(const MapBasic<K, V>& map);

        public:
          bool HasNext(void) const;

          Pair Next(void);
          const Pair Next(void) const;

          Pair Get(void);
          const Pair Get(void) const;

        private:
          const MapBasic<K, V>& map;
          mutable int currentIndex;
          mutable Pair currentPair;

          friend class MapBasic<K, V>;
      };

      friend class Iterator;

    public:
      MapBasic(void);
      virtual ~MapBasic(void);

      int Size(void) const;
      bool IsEmpty(void) const;

      V& Get(const K& rKey);
      const V& Get(const K& rKey) const;

      void Add(const K& rKey, const V& rValue);
      void Remove(const K& rKey);
      void Clear(void);

      bool Contains(const K& rKey) const;

      Iterator GetIterator(void);
      const Iterator GetIterator(void) const;

    private:
      // TODO: dont implement the map with lists. when I change this we can put
      //       the load/save code in the list. Now this is not possible because
      //       we include the list via the map.
      ListBasic<K> keys;
      ListBasic<V> values;
  };

}

#include "impl/containers/MapBasic.hpp"

#endif
