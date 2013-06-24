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

#include "CTestAssert.h"
#include "Image.h"

namespace TestImage
{

  int Constructor(void)
  {
    gul::Image img(50, 80, gul::Image::IF_RGBA);

    TEST_EQUAL(img.GetWidth(), 50);
    TEST_EQUAL(img.GetHeight(), 80);
    TEST_EQUAL(img.GetImageFormat(), gul::Image::IF_RGBA);
    TEST_NOT_NULL(img.GetDataConst());

    return EXIT_SUCCESS;
  }

  int CopyConstructor(void)
  {
    gul::Image img(50, 80, gul::Image::IF_RGBA);
    gul::Image copy = img;

    TEST_EQUAL(copy.GetWidth(), 50);
    TEST_EQUAL(copy.GetHeight(), 80);
    TEST_EQUAL(copy.GetImageFormat(), gul::Image::IF_RGBA);
    TEST_NOT_NULL(copy.GetDataConst());
    TEST_EQUAL(copy.GetDataConst(), img.GetDataConst());

    return EXIT_SUCCESS;
  }

  int Assignment(void)
  {
    gul::Image img(50, 80, gul::Image::IF_RGBA);
    gul::Image nullImg;
    nullImg = img;

    TEST_NOT_NULL(nullImg.GetDataConst());
    TEST_EQUAL(nullImg.GetDataConst(), img.GetDataConst());
    TEST_EQUAL(img.GetWidth(), 50);
    TEST_EQUAL(img.GetHeight(), 80);
    TEST_EQUAL(img.GetImageFormat(), gul::Image::IF_RGBA);
    TEST_EQUAL(nullImg.GetWidth(), 50);
    TEST_EQUAL(nullImg.GetHeight(), 80);
    TEST_EQUAL(nullImg.GetImageFormat(), gul::Image::IF_RGBA);

    return EXIT_SUCCESS;
  }

  int AssignmentSelf(void)
  {
    gul::Image first(50, 80, gul::Image::IF_RGBA);
    const unsigned char* pData = first.GetDataConst();
    gul::Image* pFirst = &first;

    first = *pFirst;
    TEST_NOT_NULL(pFirst->GetDataConst());
    TEST_EQUAL(pFirst->GetDataConst(), first.GetDataConst());
    TEST_EQUAL(pData, first.GetDataConst());
    TEST_EQUAL(pData, first.GetDataConst());
    TEST_EQUAL(first.GetWidth(), 50);
    TEST_EQUAL(first.GetHeight(), 80);
    TEST_EQUAL(first.GetImageFormat(), gul::Image::IF_RGBA);

    return EXIT_SUCCESS;
  }

  int AssignmentExchange(void)
  {
    gul::Image first(40, 80, gul::Image::IF_RGBA);
    gul::Image second(80, 160, gul::Image::IF_RGBA);
    gul::Image tmp;

    const unsigned char* pFirst = first.GetDataConst();
    const unsigned char* pSecond = second.GetDataConst();

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
    TEST_EQUAL(first.GetImageFormat(), gul::Image::IF_RGBA);
    TEST_EQUAL(second.GetWidth(), 40);
    TEST_EQUAL(second.GetHeight(), 80);
    TEST_EQUAL(second.GetImageFormat(), gul::Image::IF_RGBA);

    return EXIT_SUCCESS;
  }

  int DeleteReferee(void)
  {
    gul::Image* ref1 = new gul::Image(50, 80, gul::Image::IF_RGBA);
    gul::Image* ref2 = new gul::Image(*ref1);

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

  int GetColor(void)
  {
    gul::Image img(10, 10, gul::Image::IF_RGBA);

    unsigned char old = img.GetColor(5, 5, 0);
    unsigned char changed = old + 128;
    for(int i = 0; i < img.GetNumberOfChannels(); ++i)
      img.GetColor(5, 5, i) = changed;

    for(int i = 0; i < img.GetNumberOfChannels(); ++i)
      TEST_NOT_EQUAL(img.GetColorConst(5, 5, i), old);

    for(int i = 0; i < img.GetNumberOfChannels(); ++i)
      TEST_EQUAL(img.GetColorConst(5, 5, i), changed);

    return EXIT_SUCCESS;
  }

  int GetColorSharedResource(void)
  {
    gul::Image img1(10, 10, gul::Image::IF_RGBA);
    img1.GetColor(5,5,2) = 50;
    gul::Image img2 = img1;

    img1.GetColorConst(5, 5, 0);
    TEST_NOT_NULL(img1.GetDataConst());
    TEST_NOT_NULL(img2.GetDataConst());
    TEST_EQUAL(img1.GetDataConst(), img2.GetDataConst());
    TEST_EQUAL(img1.GetColor(5, 5, 0), img2.GetColor(5, 5, 0));
    TEST_EQUAL(img1.GetColor(5, 5, 2), img2.GetColor(5, 5, 2));

    img1.GetColor(5, 5, 0) = 128;
    TEST_NOT_NULL(img1.GetDataConst());
    TEST_NOT_NULL(img2.GetDataConst());
    TEST_NOT_EQUAL(img1.GetDataConst(), img2.GetDataConst());
    TEST_NOT_EQUAL(img1.GetColor(5, 5, 0), img2.GetColor(5, 5, 0));
    TEST_EQUAL(img1.GetColor(5, 5, 2), img2.GetColor(5, 5, 2));

    return EXIT_SUCCESS;
  }

  int GetData(void)
  {
    gul::Image img1(10, 10, gul::Image::IF_RGBA);
    gul::Image img2 = img1;
    const gul::Image img3 = img1;

    unsigned char* pData2 = img2.GetData();
    const unsigned char* pData3 = img3.GetData();

    TEST_NOT_NULL(pData2);
    TEST_NOT_NULL(pData3);
    TEST_NOT_EQUAL(pData2, pData3);
    TEST_EQUAL(pData3, img1.GetDataConst());
    TEST_EQUAL(pData2, img2.GetDataConst());
    TEST_EQUAL(pData3, img3.GetDataConst());

    return EXIT_SUCCESS;
  }

  int GetDataConst(void)
  {
    gul::Image img1(10, 10, gul::Image::IF_RGBA);
    gul::Image img2 = img1;
    const gul::Image img3 = img1;

    const unsigned char* pData2 = img2.GetDataConst();
    const unsigned char* pData3 = img3.GetData();

    TEST_NOT_NULL(pData2);
    TEST_NOT_NULL(pData3);
    TEST_EQUAL(pData2, pData3);
    TEST_EQUAL(pData3, img1.GetDataConst());
    TEST_EQUAL(pData2, img2.GetDataConst());
    TEST_EQUAL(pData3, img3.GetDataConst());

    return EXIT_SUCCESS;
  }

  int NoCopySingleReferee(void)
  {
    gul::Image img1(10, 10, gul::Image::IF_RGBA);
    gul::Image img2 = img1;

    const unsigned char* pOldData1 = img1.GetDataConst();
    const unsigned char* pOldData2 = img2.GetDataConst();
    TEST_EQUAL(pOldData1, pOldData2);

    unsigned char* pData1 = img1.GetData();
    TEST_NOT_NULL(pData1);
    TEST_NOT_EQUAL(pData1, pOldData1);

    unsigned char* pData2 = img2.GetData();
    TEST_NOT_NULL(pData2);
    TEST_EQUAL(pOldData2, img2.GetDataConst());

    return EXIT_SUCCESS;
  }

  int ReuseDataRefereeWhenSameSize(void)
  {
    gul::Image img1(10, 10, gul::Image::IF_RGBA);
    gul::Image img2 = img1;

    const unsigned char* pOldData1 = img1.GetDataConst();
    const unsigned char* pOldData2 = img2.GetDataConst();
    TEST_EQUAL(pOldData1, pOldData2);

    img1.GetData();
    TEST_NOT_EQUAL(img1.GetDataConst(), img2.GetDataConst());

    img2 = img1;
    TEST_NOT_EQUAL(img1.GetDataConst(), img2.GetDataConst());
    TEST_EQUAL(pOldData2, img2.GetDataConst());

    return EXIT_SUCCESS;
  }
}
