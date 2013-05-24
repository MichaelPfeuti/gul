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
#include "ImageIO_TIFF.h"
#include "UtilsImage.h"
#include "AnalyzerImageEquality.h"

namespace TestImageIO_TIFF
{
  int Read(void)
  {
    gul::ImageIO_TIFF tiffIO;
    gul::File lenaPath = gul::CTestData::GetFilePath(gul::String("image"), gul::String("lena.tiff"));
    gul::Image lenaImage = tiffIO.Load(lenaPath);

    TEST_TRUE(gul::AnalyzerImageEquality::Execute(lenaImage, gul::GetLenaAlpha(), 0.001f));

    return EXIT_SUCCESS;
  }

  int WriteRead(void)
  {
    gul::ImageIO_TIFF tiffIO;
    gul::Image image = gul::GetLenaAlpha();
    gul::File lenaPath = gul::CTestData::GetTempFilePath(gul::String("lenaGT.tiff"));
    tiffIO.Save(lenaPath, image);

    image = tiffIO.Load(lenaPath);
    TEST_TRUE(gul::AnalyzerImageEquality::Execute(image, gul::GetLenaAlpha(), 0.001f));

    gul::File lenaSecondPath = gul::CTestData::GetTempFilePath(gul::String("lenaLoaded.tiff"));
    tiffIO.Save(lenaSecondPath, image);
    gul::Image imageSecond = tiffIO.Load(lenaSecondPath);
    TEST_TRUE(gul::AnalyzerImageEquality::Execute(image, imageSecond));

    return EXIT_SUCCESS;
  }

  int ReadDeflate(void)
  {
    gul::ImageIO_TIFF tiffIO;
    gul::File lenaPath = gul::CTestData::GetFilePath(gul::String("image"), gul::String("lena_deflate.tiff"));
    gul::Image lenaImage = tiffIO.Load(lenaPath);

    TEST_TRUE(gul::AnalyzerImageEquality::Execute(lenaImage, gul::GetLenaAlpha(), 0.001f));

    return EXIT_SUCCESS;
  }

  int ReadJPEG(void)
  {
    gul::ImageIO_TIFF tiffIO;
    gul::File lenaPath = gul::CTestData::GetFilePath(gul::String("image"), gul::String("lena_jpeg.tiff"));
    gul::Image lenaImage = tiffIO.Load(lenaPath);

    TEST_TRUE(gul::AnalyzerImageEquality::Execute(lenaImage, gul::GetLena(), 0.007f));

    return EXIT_SUCCESS;
  }

  int ReadPackBits(void)
  {
    gul::ImageIO_TIFF tiffIO;
    gul::File lenaPath = gul::CTestData::GetFilePath(gul::String("image"), gul::String("lena_packbits.tiff"));
    gul::Image lenaImage = tiffIO.Load(lenaPath);

    TEST_TRUE(gul::AnalyzerImageEquality::Execute(lenaImage, gul::GetLenaAlpha(), 0.001f));

    return EXIT_SUCCESS;
  }

  int ReadLZW(void)
  {
    gul::ImageIO_TIFF tiffIO;
    gul::File lenaPath = gul::CTestData::GetFilePath(gul::String("image"), gul::String("lena_lzw.tiff"));
    gul::Image lenaImage = tiffIO.Load(lenaPath);

    TEST_TRUE(gul::AnalyzerImageEquality::Execute(lenaImage, gul::GetLenaAlpha(), 0.001f));

    return EXIT_SUCCESS;
  }
}
