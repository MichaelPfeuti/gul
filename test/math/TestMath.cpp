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

#include "CTestAssert.h"
#include "Math.h"

namespace TestMath
{
  int Min(void)
  {
    float minf = -23.2f;
    float maxf = 223.2f;

    TEST_EQUAL(gul::min(minf, maxf), minf);

    int mini = -23;
    int maxi = 223;

    TEST_EQUAL(gul::min(mini, maxi), mini);

    unsigned char minuc = 23;
    unsigned char maxuc = 223;

    TEST_EQUAL(gul::min(minuc, maxuc), minuc);

    double maxd = 223.2f;
    double resultd = gul::min<double>(minf, maxd);
    double resultf = gul::min<float>(minf, maxd);

    TEST_EQUAL(resultd, minf);
    TEST_EQUAL(resultf, minf);

    return EXIT_SUCCESS;
  }

  int Max(void)
  {
    float minf = -23.2f;
    float maxf = 223.2f;

    TEST_EQUAL(gul::max(minf, maxf), maxf);

    int mini = -23;
    int maxi = 223;

    TEST_EQUAL(gul::max(mini, maxi), maxi);

    unsigned char minuc = 23;
    unsigned char maxuc = 223;

    TEST_EQUAL(gul::max(minuc, maxuc), maxuc);

    double maxd = 223.2f;
    double resultd = gul::max<double>(minf, maxd);
    double resultf = gul::max<float>(minf, maxd);

    TEST_EQUAL(resultd, maxd);
    TEST_EQUAL(resultf, maxd);

    return EXIT_SUCCESS;
  }

  int Abs(void)
  {
    TEST_EQUAL(gul::abs(0.0), 0.0);
    TEST_EQUAL(gul::abs(-0.1), 0.1);
    TEST_EQUAL(gul::abs(0.1), 0.1);
    TEST_EQUAL(gul::abs(-0.5), 0.5);
    TEST_EQUAL(gul::abs(0.5), 0.5);

    return EXIT_SUCCESS;
  }

  int AbsoluteDifference(void)
  {
    TEST_EQUAL(gul::absoluteDifference(0.0, 0.5), 0.5);
    TEST_EQUAL(gul::absoluteDifference(0.5, 0.0), 0.5);
    TEST_EQUAL(gul::absoluteDifference(-0.1, 0.5), 0.6);
    TEST_EQUAL(gul::absoluteDifference(0.1, -0.5), 0.6);

    return EXIT_SUCCESS;
  }
}

