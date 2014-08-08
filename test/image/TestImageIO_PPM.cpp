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
#include "CTestData.h"
#include "ImageIO_PPM.h"
#include "UtilsImage.h"

namespace TestImageIO_PPM
{
  int ReadRGBASCII(void)
  {
    gul::ImageIO_PPM ppmIO;
    gul::File lenaPath = gul::CTestData::GetFilePath(gul::String("image"), gul::String("lena_ascii.ppm"));
    gul::Image lenaImage = ppmIO.Load(lenaPath);

    TEST_EQUAL_IMAGE(lenaImage, gul::GetLena(), 0.f);
    return EXIT_SUCCESS;
  }

  int WriteReadRGBASCII(void)
  {
    gul::ImageIO_PPM ppmIO;
    gul::Image image = gul::GetLena();
    gul::File lenaPath = gul::CTestData::GetTempFilePath(gul::String("lena.ppm"));
    ppmIO.SetMode(gul::ImageIO_PPM::PPM_ASCII);
    ppmIO.Save(lenaPath, image);

    image = ppmIO.Load(lenaPath);
    TEST_EQUAL_IMAGE(image, gul::GetLena(), 0.f);

    return EXIT_SUCCESS;
  }

  int ReadRGBBinary(void)
  {
    gul::ImageIO_PPM ppmIO;
    gul::Image image = gul::GetLena();
    gul::File lenaPath = gul::CTestData::GetFilePath(gul::String("image"), gul::String("lena_bin.ppm"));
    gul::Image lenaImage = ppmIO.Load(lenaPath);

    TEST_EQUAL_IMAGE(lenaImage, gul::GetLena(), 0.f);
    return EXIT_SUCCESS;
  }

  int WriteReadRGBBinary(void)
  {
    gul::ImageIO_PPM ppmIO;
    gul::Image image = gul::GetLena();
    gul::File lenaPath = gul::CTestData::GetTempFilePath(gul::String("lena.ppm"));
    ppmIO.SetMode(gul::ImageIO_PPM::PPM_BINARY);
    ppmIO.Save(lenaPath, image);

    image = ppmIO.Load(lenaPath);
    TEST_EQUAL_IMAGE(image, gul::GetLena(), 0.f);

    return EXIT_SUCCESS;
  }

  int ReadGreyscaleASCII(void)
  {
    gul::ImageIO_PPM ppmIO;
    gul::File lenaPath = gul::CTestData::GetFilePath(gul::String("image"), gul::String("lena_ascii.pgm"));
    gul::Image lenaImage = ppmIO.Load(lenaPath);

    TEST_EQUAL_IMAGE(lenaImage, gul::GetLenaGrayscale(), 0.f);
    return EXIT_SUCCESS;
  }

  int ReadGreyscaleBinary(void)
  {
    gul::ImageIO_PPM ppmIO;
    gul::File lenaPath = gul::CTestData::GetFilePath(gul::String("image"), gul::String("lena_bin.pgm"));
    gul::Image lenaImage = ppmIO.Load(lenaPath);

    TEST_EQUAL_IMAGE(lenaImage, gul::GetLenaGrayscale(), 0.f);
    return EXIT_SUCCESS;
  }

  int ReadBlackAndWhiteASCII(void)
  {
    gul::ImageIO_PPM ppmIO;
    gul::File lenaPath = gul::CTestData::GetFilePath(gul::String("image"), gul::String("lena_ascii.pbm"));
    gul::Image lenaImage = ppmIO.Load(lenaPath);

    TEST_EQUAL_IMAGE(lenaImage, gul::GetLenaBin(), 0.f);
    return EXIT_SUCCESS;
  }

  int ReadBlackAndWhiteBinary(void)
  {
    gul::ImageIO_PPM ppmIO;
    gul::File lenaPath = gul::CTestData::GetFilePath(gul::String("image"), gul::String("lena_bin.pbm"));
    gul::Image lenaImage = ppmIO.Load(lenaPath);

    TEST_EQUAL_IMAGE(lenaImage, gul::GetLenaBin(), 0.f);
    return EXIT_SUCCESS;
  }
}
