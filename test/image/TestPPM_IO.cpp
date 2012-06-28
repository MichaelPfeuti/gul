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

namespace TestPPM_IO
{
  int ReadWriteRGBASCII(void)
  {
    gul::PPM_IO jpegIO;
    gul::File lenaPath = gul::CTestData::GetFilePath(gul::String("lena_ascii.ppm"));
    gul::Image lenaImage = jpegIO.Load(lenaPath);

    gul::File lenaTmpPath = gul::CTestData::GetTempFilePath(gul::String("lena_rgb_ascii.ppm"));
    jpegIO.SetMode(gul::PPM_IO::PPM_ASCII);
    jpegIO.Save(lenaTmpPath, lenaImage);
    return EXIT_FAILURE;
  }

  int ReadWriteRGBBinary(void)
  {
    gul::PPM_IO jpegIO;
    gul::File lenaPath = gul::CTestData::GetFilePath(gul::String("lena_bin.ppm"));
    gul::Image lenaImage = jpegIO.Load(lenaPath);

    gul::File lenaTmpPath = gul::CTestData::GetTempFilePath(gul::String("lena_rgb_bin.ppm"));
    jpegIO.SetMode(gul::PPM_IO::PPM_BINARY);
    jpegIO.Save(lenaTmpPath, lenaImage);
    return EXIT_FAILURE;
  }

  int ReadWriteGreyscaleASCII(void)
  {
    gul::PPM_IO jpegIO;
    gul::File lenaPath = gul::CTestData::GetFilePath(gul::String("lena_ascii.pgm"));
    gul::Image lenaImage = jpegIO.Load(lenaPath);

    gul::File lenaTmpPath = gul::CTestData::GetTempFilePath(gul::String("lena_grey_ascii.ppm"));
    jpegIO.SetMode(gul::PPM_IO::PPM_ASCII);
    jpegIO.Save(lenaTmpPath, lenaImage);
    return EXIT_FAILURE;
  }

  int ReadWriteGreyscaleBinary(void)
  {
    gul::PPM_IO jpegIO;
    gul::File lenaPath = gul::CTestData::GetFilePath(gul::String("lena_bin.pgm"));
    gul::Image lenaImage = jpegIO.Load(lenaPath);

    gul::File lenaTmpPath = gul::CTestData::GetTempFilePath(gul::String("lena_grey_bin.ppm"));
    jpegIO.SetMode(gul::PPM_IO::PPM_BINARY);
    jpegIO.Save(lenaTmpPath, lenaImage);
    return EXIT_FAILURE;
  }

  int ReadWriteBlackAndWhiteASCII(void)
  {
    gul::PPM_IO jpegIO;
    gul::File lenaPath = gul::CTestData::GetFilePath(gul::String("lena_ascii.pbm"));
    gul::Image lenaImage = jpegIO.Load(lenaPath);

    gul::File lenaTmpPath = gul::CTestData::GetTempFilePath(gul::String("lena_bw_ascii.ppm"));
    jpegIO.SetMode(gul::PPM_IO::PPM_ASCII);
    jpegIO.Save(lenaTmpPath, lenaImage);
    return EXIT_FAILURE;
  }

  int ReadWriteBlackAndWhiteBinary(void)
  {
    gul::PPM_IO jpegIO;
    gul::File lenaPath = gul::CTestData::GetFilePath(gul::String("lena_bin.pbm"));
    gul::Image lenaImage = jpegIO.Load(lenaPath);

    gul::File lenaTmpPath = gul::CTestData::GetTempFilePath(gul::String("lena_bw_bin.ppm"));
    jpegIO.SetMode(gul::PPM_IO::PPM_BINARY);
    jpegIO.Save(lenaTmpPath, lenaImage);
    return EXIT_FAILURE;
  }
}
