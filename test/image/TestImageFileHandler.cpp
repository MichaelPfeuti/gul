/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011-2015 Michael Pfeuti.
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
#include "UtilsImage.h"
#include "ImageFileHandler.h"

namespace TestImageFileHandler
{
  int LoadJPEG(void)
  {
    gul::File jpegFile = gul::CTestData::GetFilePath(gul::String("image"), gul::String("lena.jpeg"));
    gul::File jpgFile = gul::CTestData::GetFilePath(gul::String("image"), gul::String("lena.jpg"));
    gul::File jpeFile = gul::CTestData::GetFilePath(gul::String("image"), gul::String("lena.jpe"));

    gul::Image image = gul::ImageFileHandler::Instance().Load(jpegFile);
    TEST_FALSE(image.IsNull());

    image = gul::ImageFileHandler::Instance().Load(jpgFile);
    TEST_FALSE(image.IsNull());

    image = gul::ImageFileHandler::Instance().Load(jpeFile);
    TEST_FALSE(image.IsNull());

    return EXIT_SUCCESS;
  }

  int SaveJPEG(void)
  {
    gul::Image image = gul::GetLena();

    gul::File jpegFile = gul::CTestData::GetTempFilePath(gul::String("lena.jpeg"));
    gul::File jpgFile = gul::CTestData::GetTempFilePath(gul::String("lena.jpg"));
    gul::File jpeFile = gul::CTestData::GetTempFilePath(gul::String("lena.jpe"));

    gul::ImageFileHandler::Instance().Save(jpegFile, image);
    TEST_TRUE(jpegFile.Exists());

    gul::ImageFileHandler::Instance().Save(jpgFile, image);
    TEST_TRUE(jpegFile.Exists());

    gul::ImageFileHandler::Instance().Save(jpeFile, image);
    TEST_TRUE(jpegFile.Exists());

    return EXIT_SUCCESS;
  }

  int LoadPNG(void)
  {
    gul::File pngFile = gul::CTestData::GetFilePath(gul::String("image"), gul::String("lena.png"));

    gul::Image image = gul::ImageFileHandler::Instance().Load(pngFile);
    TEST_FALSE(image.IsNull());

    return EXIT_SUCCESS;
  }

  int SavePNG(void)
  {
    gul::Image image = gul::GetLena();

    gul::File pngFile = gul::CTestData::GetTempFilePath(gul::String("lena.png"));

    gul::ImageFileHandler::Instance().Save(pngFile, image);
    TEST_TRUE(pngFile.Exists());

    return EXIT_SUCCESS;
  }

  int LoadPPM(void)
  {
    gul::File ppmFile = gul::CTestData::GetFilePath(gul::String("image"), gul::String("lena_ascii.ppm"));
    gul::File pgmFile = gul::CTestData::GetFilePath(gul::String("image"), gul::String("lena_ascii.pgm"));
    gul::File pbmFile = gul::CTestData::GetFilePath(gul::String("image"), gul::String("lena_ascii.pbm"));

    gul::Image image = gul::ImageFileHandler::Instance().Load(ppmFile);
    TEST_FALSE(image.IsNull());

    image = gul::ImageFileHandler::Instance().Load(pgmFile);
    TEST_FALSE(image.IsNull());

    image = gul::ImageFileHandler::Instance().Load(pbmFile);
    TEST_FALSE(image.IsNull());

    return EXIT_SUCCESS;
  }

  int SavePPM(void)
  {
    gul::Image image = gul::GetLena();

    gul::File ppmFile = gul::CTestData::GetTempFilePath(gul::String("lena.ppm"));
    gul::File pgmFile = gul::CTestData::GetTempFilePath(gul::String("lena.pgm"));
    gul::File pbmFile = gul::CTestData::GetTempFilePath(gul::String("lena.pbm"));

    gul::ImageFileHandler::Instance().Save(ppmFile, image);
    TEST_TRUE(ppmFile.Exists());

    gul::ImageFileHandler::Instance().Save(pgmFile, image);
    TEST_TRUE(pgmFile.Exists());

    gul::ImageFileHandler::Instance().Save(pbmFile, image);
    TEST_TRUE(pbmFile.Exists());

    return EXIT_SUCCESS;
  }

  int LoadTIFF(void)
  {
    gul::File tifFile = gul::CTestData::GetFilePath(gul::String("image"), gul::String("lena.tif"));
    gul::File tiffFile = gul::CTestData::GetFilePath(gul::String("image"), gul::String("lena.tiff"));

    gul::Image image = gul::ImageFileHandler::Instance().Load(tifFile);
    TEST_FALSE(image.IsNull());

    image = gul::ImageFileHandler::Instance().Load(tiffFile);
    TEST_FALSE(image.IsNull());

    return EXIT_SUCCESS;
  }

  int SaveTIFF(void)
  {
    gul::Image image = gul::GetLena();

    gul::File tifFile = gul::CTestData::GetTempFilePath(gul::String("lena.tif"));
    gul::File tiffFile = gul::CTestData::GetTempFilePath(gul::String("lena.tiff"));

    gul::ImageFileHandler::Instance().Save(tifFile, image);
    TEST_TRUE(tifFile.Exists());

    gul::ImageFileHandler::Instance().Save(tiffFile, image);
    TEST_TRUE(tiffFile.Exists());

    return EXIT_SUCCESS;
  }
}
