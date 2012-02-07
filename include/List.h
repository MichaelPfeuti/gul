#pragma once
#ifndef _GUL_CONTAINERS_LIST_H_
#define _GUL_CONTAINERS_LIST_H_
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
#include "3rdParty/pugi/pugixml.hpp"


namespace gul
{

  template<typename T>
  class List : public Container<T>
  {
    public:
      List(void);
      explicit List(int initSize);

      template<typename U>
      explicit List(const Container<U>& rContainer);

      virtual ~List(void);

      List(const List& rList);
      List& operator=(const List& rList);

      int Size(void) const;
      bool IsEmpty(void) const;

      void Add(const T& element);
      void Add(const T& element, int index);

      T& Get(int index);
      const T& Get(int index) const;

      bool Contains(const T& element) const;
      int IndexOf(const T& element) const;

      void Remove(int index);
      void RemoveElement(const T& element);

      void Clear(void);

    private:
      virtual void Save(pugi::xml_node& node, bool resetMode) const;
      virtual void* Load(const pugi::xml_node& node, bool resetMode) const;
      template<typename> friend class XMLSerializable;

    private:
      void copyAllData(const List& rList);

    private:
      template<typename U>
      struct ListElement
      {
        ListElement(U d)
          : data(d), pPrev(nullptr), pNext(nullptr) {}
        ListElement(U d, ListElement* pP, ListElement* pN)
          : data(d), pPrev(pP), pNext(pN) {}

        U data;
        ListElement* pPrev;
        ListElement* pNext;
      };

      ListElement<T>* pHead;
      ListElement<T>* pTail;
      int size;
  };

}

#include "impl/containers/List.hpp"

#endif
