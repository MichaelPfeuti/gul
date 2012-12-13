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
#include "ConverterImageToSBS.h"
#include "ImageFileHandler.h"
#include "AnalyzerImageEquality.h"

namespace TestImageToSBS
{
  int SameSize(void)
  {
    gul::Image left = gul::ImageFileHandler::Instance().Load(gul::CTestData::GetFilePath(gul::String("algorithms"),
                                                                                         gul::String("avatar_left.png")));
    gul::Image right = gul::ImageFileHandler::Instance().Load(gul::CTestData::GetFilePath(gul::String("algorithms"),
                                                                                          gul::String("avatar_right.png")));
    gul::Image gt = gul::ImageFileHandler::Instance().Load(gul::CTestData::GetFilePath(gul::String("algorithms"),
                                                                                       gul::String("avatar_sbs.png")));

    gul::Image sbs = gul::ConverterImageToSBS::Execute(left, right);
    TEST_TRUE(gul::AnalyzerImageEquality::Execute(sbs, gt));

    gul::ImageFileHandler::Instance().Save(gul::File("out.png"), sbs);

    return EXIT_SUCCESS;
  }

  int DifferentSize(void)
  {
    gul::Image left = gul::ImageFileHandler::Instance().Load(gul::CTestData::GetFilePath(gul::String("algorithms"),
                                                                                         gul::String("avatar_left.png")));
    gul::Image right = gul::ImageFileHandler::Instance().Load(gul::CTestData::GetFilePath(gul::String("algorithms"),
                                                                                          gul::String("avatar_right.png")));
    gul::Image gt = gul::ImageFileHandler::Instance().Load(gul::CTestData::GetFilePath(gul::String("algorithms"),
                                                                                       gul::String("avatar_sbs.png")));

    gul::Image sbs = gul::ConverterImageToSBS::Execute(left, right);
    gul::Image sbsRight = gul::ConverterImageToSBS::Execute(sbs, right);
    gul::Image gtRight = gul::ConverterImageToSBS::Execute(gt, right);
    TEST_TRUE(gul::AnalyzerImageEquality::Execute(sbsRight, gtRight));

    gul::ImageFileHandler::Instance().Save(gul::File("sbsRight.png"), sbsRight);
    gul::ImageFileHandler::Instance().Save(gul::File("gtRight.png"), gtRight);

    return EXIT_SUCCESS;
  }
}
