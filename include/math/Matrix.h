#pragma once
#ifndef _GUL_MATH_MATRIX_H_
#define _GUL_MATH_MATRIX_H_
/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011-2014 Michael Pfeuti.
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

#include "RTTI.h"

namespace gul
{

  template<typename T>
  class MatrixT
  {
      DECLARE_RTTI(MatrixT)

    public:
      MatrixT(void);
      MatrixT(int rowCount, int colCount);
      MatrixT(int rowCount, int colCount, const T* pData);
      MatrixT(const MatrixT& rImage);
      virtual ~MatrixT(void);

      MatrixT& operator=(const MatrixT& other);

      int GetRowCount(void) const;
      int GetColCount(void) const;

      bool IsNull(void) const;

      const T& operator[](int row, int col) const;
      const T& operator[](int row, int col) const;
      T& operator[](int row, int col);

      const T* GetDataConst(void) const;
      const T* GetData(void) const;
      T* GetData(void);

    private:
      T* m_pData;
      int m_rowCount;
      int m_colCount;

  };

  typedef MatrixT<float> Matrix;
  typedef MatrixT<double> MatrixD;

}

SPECIALIZE_TPL_TRAITS(gul::MatrixT)

#include "../impl/math/Matrix.hpp"

#endif
