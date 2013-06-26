/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011-2013 Michael Pfeuti
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

#include "OnDemandMemory.h"
#include "Misc.h"

template<typename T>
gul::OnDemandMemory<T>::OnDemandMemory(int size)
  : m_size(size),
    m_pData(nullptr)
{
}

template<typename T>
gul::OnDemandMemory<T>::~OnDemandMemory(void)
{
  std::lock_guard<std::mutex> lock(m_mutex);
  GUL_DELETE_ARRAY(m_pData);
}

template<typename T>
T* gul::OnDemandMemory<T>::GetData(void)
{
  std::lock_guard<std::mutex> lock(m_mutex);
  if(m_pData == nullptr)
  {
    m_pData = new T[m_size];
  }

  return m_pData;
}

template<typename T>
const T* gul::OnDemandMemory<T>::GetData(void) const
{
  std::lock_guard<std::mutex> lock(m_mutex);
  if(m_pData == nullptr)
  {
    m_pData = new T[m_size];
  }

  return m_pData;
}
