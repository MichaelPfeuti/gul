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

#include "AnalyzerImageEquality.h"
#include "CTestAssert.h"
#include "UtilsImage.h"

namespace TestImageEquality
{
  int Equality(void)
  {
    TEST_TRUE(gul::AnalyzerImageEquality::Execute(gul::GetLenaAlpha(), gul::GetLenaAlpha()));

    return EXIT_SUCCESS;
  }

  int InequalityData(void)
  {
    gul::Image img = gul::GetLenaAlpha();
    img.GetData()[1] = 250;
    img.GetData()[3] = 0;
    img.GetData()[5] = 20;
    img.GetData()[6] = 250;
    TEST_FALSE(gul::AnalyzerImageEquality::Execute(gul::GetLenaAlpha(), img));

    return EXIT_SUCCESS;
  }

  int InequalityFormat(void)
  {
    gul::Image img = gul::GetLenaAlpha();
    gul::Image imgGray(img.GetWidth(), img.GetHeight(), gul::Image::IF_GRAY, img.GetDataConst());
    TEST_FALSE(gul::AnalyzerImageEquality::Execute(imgGray, img));

    return EXIT_SUCCESS;
  }
}
