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
#include "CTestData.h"
#include "PPM_IO.h"
#include "Utils.h"
#include "ConverterImageToGrayscale.h"
#include "ConverterImageToBW.h"
#include "AnalyzerImageEquality.h"

namespace TestPPM_IO
{
  int ReadRGBASCII(void)
  {
    gul::PPM_IO ppmIO;
    gul::File lenaPath = gul::CTestData::GetFilePath(gul::String("image"), gul::String("lena_ascii.ppm"));
    gul::Image lenaImage = ppmIO.Load(lenaPath);

    TEST_TRUE(gul::AnalyzerImageEquality::Execute(lenaImage, GetLenaGT()));
    return EXIT_SUCCESS;
  }

  int WriteReadRGBASCII(void)
  {
    gul::PPM_IO ppmIO;
    gul::Image image = GetLenaGT();
    gul::File lenaPath = gul::CTestData::GetTempFilePath(gul::String("lena.ppm"));
    ppmIO.SetMode(gul::PPM_IO::PPM_ASCII);
    ppmIO.Save(lenaPath, image);

    image = ppmIO.Load(lenaPath);
    TEST_TRUE(gul::AnalyzerImageEquality::Execute(image, GetLenaGT()));

    return EXIT_SUCCESS;
  }

  int ReadRGBBinary(void)
  {
    gul::PPM_IO ppmIO;
    gul::Image image = GetLenaGT();
    gul::File lenaPath = gul::CTestData::GetFilePath(gul::String("image"), gul::String("lena_bin.ppm"));
    gul::Image lenaImage = ppmIO.Load(lenaPath);

    TEST_TRUE(gul::AnalyzerImageEquality::Execute(lenaImage, GetLenaGT()));
    return EXIT_SUCCESS;
  }

  int WriteReadRGBBinary(void)
  {
    gul::PPM_IO ppmIO;
    gul::Image image = GetLenaGT();
    gul::File lenaPath = gul::CTestData::GetTempFilePath(gul::String("lena.ppm"));
    ppmIO.SetMode(gul::PPM_IO::PPM_BINARY);
    ppmIO.Save(lenaPath, image);

    image = ppmIO.Load(lenaPath);
    TEST_TRUE(gul::AnalyzerImageEquality::Execute(image, GetLenaGT()));

    return EXIT_SUCCESS;
  }

  int ReadGreyscaleASCII(void)
  {
    gul::PPM_IO ppmIO;
    gul::File lenaPath = gul::CTestData::GetFilePath(gul::String("image"), gul::String("lena_ascii.pgm"));
    gul::Image lenaImage = ppmIO.Load(lenaPath);

    TEST_TRUE(gul::AnalyzerImageEquality::Execute(lenaImage, GetLenaGrayscaleGT()));
    return EXIT_SUCCESS;
  }

  int ReadGreyscaleBinary(void)
  {
    gul::PPM_IO ppmIO;
    gul::File lenaPath = gul::CTestData::GetFilePath(gul::String("image"), gul::String("lena_bin.pgm"));
    gul::Image lenaImage = ppmIO.Load(lenaPath);

    TEST_TRUE(gul::AnalyzerImageEquality::Execute(lenaImage, GetLenaGrayscaleGT()));
    return EXIT_SUCCESS;
  }

  int ReadBlackAndWhiteASCII(void)
  {
    gul::PPM_IO ppmIO;
    gul::File lenaPath = gul::CTestData::GetFilePath(gul::String("image"), gul::String("lena_ascii.pbm"));
    gul::Image lenaImage = ppmIO.Load(lenaPath);

    TEST_TRUE(gul::AnalyzerImageEquality::Execute(lenaImage, GetLenaBWGT()));
    return EXIT_SUCCESS;
  }

  int ReadBlackAndWhiteBinary(void)
  {
    gul::PPM_IO ppmIO;
    gul::File lenaPath = gul::CTestData::GetFilePath(gul::String("image"), gul::String("lena_bin.pbm"));
    gul::Image lenaImage = ppmIO.Load(lenaPath);

    gul::Image gtBW = gul::ConverterImageToBW::Execute(GetLenaGT());
    TEST_TRUE(gul::AnalyzerImageEquality::Execute(lenaImage, GetLenaBWGT()));
    return EXIT_SUCCESS;
  }
}
