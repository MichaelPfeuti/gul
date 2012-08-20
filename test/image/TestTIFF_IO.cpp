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
#include "TIFF_IO.h"
#include "Utils.h"

namespace TestTIFF_IO
{
  int Read(void)
  {
    gul::TIFF_IO tiffIO;
    gul::File colorImageSamplePath = gul::CTestData::GetFilePath(gul::String("colorImageSample.tiff"));
    gul::Image colorImageSampleImage = tiffIO.Load(colorImageSamplePath);

    TEST_TRUE(isEqualWithGroundTruth(colorImageSampleImage));

    return EXIT_SUCCESS;
  }

  int WriteRead(void)
  {
    gul::TIFF_IO tiffIO;
    gul::Image image = getGroudTruth();
    gul::File colorImageSamplePath = gul::CTestData::GetTempFilePath(gul::String("colorImageSample.tiff"));
    tiffIO.Save(colorImageSamplePath, image);

    image = tiffIO.Load(colorImageSamplePath);
    TEST_TRUE(isEqualWithGroundTruth(image));

    return EXIT_SUCCESS;
  }

  int ReadDeflate(void)
  {
    gul::TIFF_IO tiffIO;
    gul::File colorImageSamplePath = gul::CTestData::GetFilePath(gul::String("colorImageSample_deflate.tiff"));
    gul::Image colorImageSampleImage = tiffIO.Load(colorImageSamplePath);

    TEST_TRUE(isEqualWithGroundTruth(colorImageSampleImage));

    return EXIT_SUCCESS;
  }

  int ReadJPEG(void)
  {
    gul::TIFF_IO tiffIO;
    gul::File colorImageSamplePath = gul::CTestData::GetFilePath(gul::String("colorImageSample_jpeg.tiff"));
    gul::Image colorImageSampleImage = tiffIO.Load(colorImageSamplePath);

    TEST_TRUE(isEqualWithGroundTruth(colorImageSampleImage));

    return EXIT_SUCCESS;
  }
}
