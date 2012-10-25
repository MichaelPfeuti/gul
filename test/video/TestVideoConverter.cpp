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
#include "VideoLoader.h"
#include "ImageFileHandler.h"
#include "AnalyzerImageEquality.h"
#include "VideoConverter.h"
#include "VideoFrame.h"
#include "VideoFrameManipulator.h"

namespace TestVideoConverter
{
  class CopyManipulator : public gul::VideoFrameManipulator
  {
    virtual void Execute(const gul::Image& input, gul::Image& output)
    {
      output = input;
    }

    virtual int GetResultWidth(int width) const { return width; }
    virtual int GetResultHeight(int height) const { return height; }
  };

  int Copy(void)
  {
    gul::File output = gul::CTestData::GetTempFilePath(gul::String("converter.mkv"));
    CopyManipulator manipulator;
    gul::VideoConverter converter(gul::CTestData::GetFilePath(gul::String("video"), gul::String("firefly.mkv")));
    converter.Init(output, manipulator);
    converter.Execute();

    gul::Image first = gul::ImageFileHandler::Instance().Load(gul::CTestData::GetFilePath(gul::String("video"), gul::String("firefly-first.png")));
    gul::Image middle = gul::ImageFileHandler::Instance().Load(gul::CTestData::GetFilePath(gul::String("video"), gul::String("firefly-middle.png")));
    gul::Image last = gul::ImageFileHandler::Instance().Load(gul::CTestData::GetFilePath(gul::String("video"), gul::String("firefly-last.png")));

    gul::VideoLoader loader(output);
    loader.OpenVideo();
    gul::VideoFrame frame;
    gul::VideoFrame prevFrame;

    loader.GetNext(frame);
    TEST_TRUE(loader.IsFrameValid());
    TEST_TRUE(gul::AnalyzerImageEquality::Execute(first, frame, 0.005f));


    int count = 0;
    while(loader.IsFrameValid())
    {
      if(++count == 32)
      {
        TEST_TRUE(loader.IsFrameValid());
        TEST_TRUE(gul::AnalyzerImageEquality::Execute(middle, frame, 0.005f));
      }
      prevFrame = frame;
      loader.GetNext(frame);
    }

    TEST_EQUAL(count, 50);
    TEST_TRUE(gul::AnalyzerImageEquality::Execute(last, prevFrame, 0.005f));

    return EXIT_SUCCESS;
  }
}

