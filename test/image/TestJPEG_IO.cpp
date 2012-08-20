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
#include "JPEG_IO.h"
#include "Utils.h"

namespace TestJPEG_IO
{
  int Read(void)
  {
    gul::JPEG_IO jpegIO;
    gul::File colorImageSamplePath = gul::CTestData::GetFilePath(gul::String("colorImageSample.jpg"));
    gul::Image colorImageSampleImage = jpegIO.Load(colorImageSamplePath);

    TEST_TRUE(isEqualWithGroundTruth(colorImageSampleImage, gul::Image::IT_RGB));

    return EXIT_SUCCESS;
  }

  int WriteRead(void)
  {
    gul::JPEG_IO jpegIO;
    gul::Image image = getGroudTruth();
    gul::File colorImageSamplePath = gul::CTestData::GetTempFilePath(gul::String("colorImageSample.jpg"));
    jpegIO.Save(colorImageSamplePath, image);

    image = jpegIO.Load(colorImageSamplePath);
    TEST_TRUE(isEqualWithGroundTruth(image, gul::Image::IT_RGB));

    return EXIT_SUCCESS;
  }
}
