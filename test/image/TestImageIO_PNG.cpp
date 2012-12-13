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
#include "ImageIO_PNG.h"
#include "Utils.h"
#include "AnalyzerImageEquality.h"

namespace TestImageIO_PNG
{
  int Read(void)
  {
    gul::ImageIO_PNG pngIO;
    gul::File lenaPath = gul::CTestData::GetFilePath(gul::String("image"), gul::String("lena.png"));
    gul::Image lenaImage = pngIO.Load(lenaPath);

    TEST_TRUE(gul::AnalyzerImageEquality::Execute(lenaImage, GetLenaAlphaGT()));

    return EXIT_SUCCESS;
  }

  int WriteRead(void)
  {
    gul::ImageIO_PNG pngIO;
    gul::Image image = GetLenaAlphaGT();
    gul::File lenaPath = gul::CTestData::GetTempFilePath(gul::String("lena.png"));
    pngIO.Save(lenaPath, image);

    image = pngIO.Load(lenaPath);
    TEST_TRUE(gul::AnalyzerImageEquality::Execute(image, GetLenaAlphaGT()));

    return EXIT_SUCCESS;
  }

  int ReadInterlaced(void)
  {
    gul::ImageIO_PNG pngIO;
    gul::File lenaPath = gul::CTestData::GetFilePath(gul::String("image"), gul::String("lena_interlaced.png"));
    gul::Image lenaImage = pngIO.Load(lenaPath);

    TEST_TRUE(gul::AnalyzerImageEquality::Execute(lenaImage, GetLenaAlphaGT()));

    return EXIT_SUCCESS;
  }
}
