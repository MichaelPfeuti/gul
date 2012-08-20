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

namespace TestPPM_IO
{
  int ReadRGBASCII(void)
  {
    gul::PPM_IO ppmIO;
    gul::File colorImageSamplePath = gul::CTestData::GetFilePath(gul::String("colorImageSample_ascii.ppm"));
    gul::Image colorImageSampleImage = ppmIO.Load(colorImageSamplePath);

    TEST_TRUE(isEqualWithGroundTruth(colorImageSampleImage, gul::Image::IT_RGB));
    return EXIT_SUCCESS;
  }

  int WriteReadRGBASCII(void)
  {
    gul::PPM_IO ppmIO;
    gul::Image image = getGroudTruth();
    gul::File colorImageSamplePath = gul::CTestData::GetTempFilePath(gul::String("colorImageSample.ppm"));
    ppmIO.SetMode(gul::PPM_IO::PPM_ASCII);
    ppmIO.Save(colorImageSamplePath, image);

    image = ppmIO.Load(colorImageSamplePath);
    TEST_TRUE(isEqualWithGroundTruth(image, gul::Image::IT_RGB));

    return EXIT_SUCCESS;
  }

  int ReadRGBBinary(void)
  {
    gul::PPM_IO ppmIO;
    gul::File colorImageSamplePath = gul::CTestData::GetFilePath(gul::String("colorImageSample_bin.ppm"));
    gul::Image colorImageSampleImage = ppmIO.Load(colorImageSamplePath);

    TEST_TRUE(isEqualWithGroundTruth(colorImageSampleImage, gul::Image::IT_RGB));
    return EXIT_SUCCESS;
  }

  int WriteReadRGBBinary(void)
  {
    gul::PPM_IO ppmIO;
    gul::Image image = getGroudTruth();
    gul::File colorImageSamplePath = gul::CTestData::GetTempFilePath(gul::String("colorImageSample.ppm"));
    ppmIO.SetMode(gul::PPM_IO::PPM_BINARY);
    ppmIO.Save(colorImageSamplePath, image);

    image = ppmIO.Load(colorImageSamplePath);
    TEST_TRUE(isEqualWithGroundTruth(image, gul::Image::IT_RGB));

    return EXIT_SUCCESS;
  }

  int ReadGreyscaleASCII(void)
  {
    gul::PPM_IO ppmIO;
    gul::File colorImageSamplePath = gul::CTestData::GetFilePath(gul::String("colorImageSample_ascii.pgm"));
    gul::Image colorImageSampleImage = ppmIO.Load(colorImageSamplePath);

    TEST_TRUE(isEqualWithGroundTruth(colorImageSampleImage, gul::Image::IT_GREY));
    return EXIT_SUCCESS;
  }

  int ReadGreyscaleBinary(void)
  {
    gul::PPM_IO ppmIO;
    gul::File colorImageSamplePath = gul::CTestData::GetFilePath(gul::String("colorImageSample_bin.pgm"));
    gul::Image colorImageSampleImage = ppmIO.Load(colorImageSamplePath);

    TEST_TRUE(isEqualWithGroundTruth(colorImageSampleImage, gul::Image::IT_GREY));
    return EXIT_SUCCESS;
  }

  int ReadBlackAndWhiteASCII(void)
  {
    gul::PPM_IO ppmIO;
    gul::File colorImageSamplePath = gul::CTestData::GetFilePath(gul::String("colorImageSample_ascii.pbm"));
    gul::Image colorImageSampleImage = ppmIO.Load(colorImageSamplePath);

    TEST_TRUE(isEqualWithGroundTruth(colorImageSampleImage, gul::Image::IT_GREY));
    return EXIT_SUCCESS;
  }

  int ReadBlackAndWhiteBinary(void)
  {
    gul::PPM_IO ppmIO;
    gul::File colorImageSamplePath = gul::CTestData::GetFilePath(gul::String("colorImageSample_bin.pbm"));
    gul::Image colorImageSampleImage = ppmIO.Load(colorImageSamplePath);

    TEST_TRUE(isEqualWithGroundTruth(colorImageSampleImage, gul::Image::IT_GREY));
    return EXIT_SUCCESS;
  }
}
