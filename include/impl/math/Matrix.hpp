/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011-2015 Michael Pfeuti
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

#include "Matrix.h"
#include "Misc.h"

DEFINE_TPL_RTTI(gul::MatrixT);

template<typename T>
gul::MatrixT<T>::MatrixT(void)
  : m_pData(nullptr),
    m_rowCount(0),
    m_colCount(0)
{
}

template<typename T>
gul::MatrixT<T>::MatrixT(int rowCount, int colCount)
  : m_pData(nullptr),
    m_rowCount(rowCount),
    m_colCount(colCount)
{
  m_pData = new T[m_rowCount*m_colCount];
}

template<typename T>
gul::MatrixT<T>::MatrixT(int rowCount, int colCount, const T* pData)
  : m_pData(nullptr),
    m_rowCount(rowCount),
    m_colCount(colCount)
{
  m_pData = new T[m_rowCount*m_colCount];
  memcpy(m_pData, pData, sizeof(T)*m_rowCount * m_colCount);
}

template<typename T>
gul::MatrixT<T>::MatrixT(const MatrixT &rImage)
  : m_pData(nullptr),
    m_rowCount(rImage.m_rowCount),
    m_colCount(rImage.m_colCount)
{
  m_pData = new T[m_rowCount*m_colCount];
  memcpy(m_pData, rImage.GetData(), sizeof(T)*m_rowCount * m_colCount);
}

template<typename T>
gul::MatrixT<T>::~MatrixT(void)
{
  GUL_DELETE_ARRAY(m_pData);
}


template<typename T>
int gul::MatrixT<T>::GetRowCount(void) const
{
  return m_rowCount;
}

template<typename T>
int gul::MatrixT<T>::GetColCount(void) const
{
  return m_colCount;
}

template<typename T>
bool gul::MatrixT<T>::IsNull(void) const
{
  return m_colCount == 0 || m_rowCount == 0;
}
