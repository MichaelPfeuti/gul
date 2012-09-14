/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011-2012 Michael Pfeuti.
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

#include "CTestAssert.h"
#include "Image.h"

namespace TestImage
{

  int Constructor(void)
  {
    gul::Image img(50,80, gul::Image::IT_RGBA);

    TEST_EQUAL(img.GetWidth(), 50);
    TEST_EQUAL(img.GetHeight(), 80);
    TEST_EQUAL(img.GetImageType(), gul::Image::IT_RGBA);
    TEST_NOT_NULL(img.GetDataConst());

    return EXIT_SUCCESS;
  }

  int CopyConstructor(void)
  {
    gul::Image img(50,80, gul::Image::IT_RGBA);
    gul::Image copy = img;

    TEST_EQUAL(copy.GetWidth(), 50);
    TEST_EQUAL(copy.GetHeight(), 80);
    TEST_EQUAL(copy.GetImageType(), gul::Image::IT_RGBA);
    TEST_NOT_NULL(copy.GetDataConst());
    TEST_EQUAL(copy.GetDataConst(), img.GetDataConst());

    return EXIT_SUCCESS;
  }

  int Assignment(void)
  {
    gul::Image img(50,80, gul::Image::IT_RGBA);
    gul::Image nullImg;
    nullImg = img;

    TEST_NOT_NULL(nullImg.GetDataConst());
    TEST_EQUAL(nullImg.GetDataConst(), img.GetDataConst());
    TEST_EQUAL(img.GetWidth(), 50);
    TEST_EQUAL(img.GetHeight(), 80);
    TEST_EQUAL(img.GetImageType(), gul::Image::IT_RGBA);
    TEST_EQUAL(nullImg.GetWidth(), 50);
    TEST_EQUAL(nullImg.GetHeight(), 80);
    TEST_EQUAL(nullImg.GetImageType(), gul::Image::IT_RGBA);

    return EXIT_SUCCESS;
  }

  int AssignmentSelf(void)
  {
    gul::Image first(50,80, gul::Image::IT_RGBA);
    const float* pData = first.GetDataConst();
    gul::Image *pFirst = &first;

    first = *pFirst;
    TEST_NOT_NULL(pFirst->GetDataConst());
    TEST_EQUAL(pFirst->GetDataConst(), first.GetDataConst());
    TEST_EQUAL(pData, first.GetDataConst());
    TEST_EQUAL(pData, first.GetDataConst());
    TEST_EQUAL(first.GetWidth(), 50);
    TEST_EQUAL(first.GetHeight(), 80);
    TEST_EQUAL(first.GetImageType(), gul::Image::IT_RGBA);

    return EXIT_SUCCESS;
  }

  int AssignmentExchange(void)
  {
    gul::Image first(40,80, gul::Image::IT_RGBA);
    gul::Image second(80, 160, gul::Image::IT_RGBA);
    gul::Image tmp;

    const float* pFirst = first.GetDataConst();
    const float* pSecond = second.GetDataConst();

    tmp = first;
    TEST_EQUAL(first.GetDataConst(), tmp.GetDataConst());
    TEST_NOT_EQUAL(first.GetDataConst(), second.GetDataConst());
    TEST_EQUAL(pFirst, first.GetDataConst());
    TEST_EQUAL(pFirst, tmp.GetDataConst());
    TEST_EQUAL(pSecond, second.GetDataConst());

    first = second;
    TEST_NOT_EQUAL(first.GetDataConst(), tmp.GetDataConst());
    TEST_EQUAL(first.GetDataConst(), second.GetDataConst());
    TEST_EQUAL(pSecond, first.GetDataConst());
    TEST_EQUAL(pFirst, tmp.GetDataConst());
    TEST_EQUAL(pSecond, second.GetDataConst());

    second = tmp;
    TEST_EQUAL(second.GetDataConst(), tmp.GetDataConst());
    TEST_NOT_EQUAL(first.GetDataConst(), second.GetDataConst());
    TEST_EQUAL(pSecond, first.GetDataConst());
    TEST_EQUAL(pFirst, tmp.GetDataConst());
    TEST_EQUAL(pFirst, second.GetDataConst());

    TEST_EQUAL(first.GetWidth(), 80);
    TEST_EQUAL(first.GetHeight(), 160);
    TEST_EQUAL(first.GetImageType(), gul::Image::IT_RGBA);
    TEST_EQUAL(second.GetWidth(), 40);
    TEST_EQUAL(second.GetHeight(), 80);
    TEST_EQUAL(second.GetImageType(), gul::Image::IT_RGBA);

    return EXIT_SUCCESS;
  }

  int DeleteReferee(void)
  {
    gul::Image *ref1 = new gul::Image(50,80, gul::Image::IT_RGBA);
    gul::Image *ref2 = new gul::Image(*ref1);

    TEST_NOT_NULL(ref2->GetDataConst());
    TEST_EQUAL(ref2->GetDataConst(), ref1->GetDataConst());


    GUL_DELETE(ref1);
    TEST_NULL(ref1);
    // this delete only works when the memory was not yet
    // deleted from the first delete.
    GUL_DELETE(ref2);
    TEST_NULL(ref2);

    return EXIT_SUCCESS;
  }
}
