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
#include "VideoFrame.h"

namespace TestVideoLoader
{

  int FirstFrame(void)
  {
    gul::VideoLoader loader(gul::CTestData::GetFilePath(gul::String("video"), gul::String("firefly.mkv")));
    loader.OpenVideo();

    gul::VideoFrame frame;
    loader.GetNext(frame);
    TEST_TRUE(loader.IsFrameValid());

    gul::Image first = gul::ImageFileHandler::Instance().Load(gul::CTestData::GetFilePath(gul::String("video"), gul::String("firefly-first.png")));

    TEST_TRUE(gul::AnalyzerImageEquality::Execute(first, frame));

    return EXIT_SUCCESS;
  }

  int MiddleFrame(void)
  {
    gul::VideoLoader loader(gul::CTestData::GetFilePath(gul::String("video"), gul::String("firefly.mkv")));
    loader.OpenVideo();

    gul::VideoFrame frame;
    int frameCount = 1;

    loader.GetNext(frame);
    TEST_TRUE(loader.IsFrameValid());
    while(loader.IsFrameValid() && frameCount < 32)
    {
      loader.GetNext(frame);
      ++frameCount;
      TEST_TRUE(loader.IsFrameValid());
    }

    gul::Image middle = gul::ImageFileHandler::Instance().Load(gul::CTestData::GetFilePath(gul::String("video"), gul::String("firefly-middle.png")));

    TEST_TRUE(gul::AnalyzerImageEquality::Execute(middle, frame));

    return EXIT_SUCCESS;
  }

  int LastFrame(void)
  {
    gul::VideoLoader loader(gul::CTestData::GetFilePath(gul::String("video"), gul::String("firefly.mkv")));
    loader.OpenVideo();

    gul::VideoFrame frame;
    gul::VideoFrame framePrev;
    loader.GetNext(frame);
    while(loader.IsFrameValid())
    {
      framePrev = frame;
      loader.GetNext(frame);
    }

    gul::Image last = gul::ImageFileHandler::Instance().Load(gul::CTestData::GetFilePath(gul::String("video"), gul::String("firefly-last.png")));

    TEST_TRUE(gul::AnalyzerImageEquality::Execute(last, framePrev));

    return EXIT_SUCCESS;
  }


  int FrameCount(void)
  {
    gul::VideoLoader loader(gul::CTestData::GetFilePath(gul::String("video"), gul::String("firefly.mkv")));
    loader.OpenVideo();

    gul::VideoFrame frame;
    int frameCount = 0;
    loader.GetNext(frame);
    while(loader.IsFrameValid())
    {
      ++frameCount;
      loader.GetNext(frame);
    }
    TEST_EQUAL(frameCount, 50);

    return EXIT_SUCCESS;
  }

  int ReadMp4(void)
  {
    gul::VideoLoader loader(gul::CTestData::GetFilePath(gul::String("video"), gul::String("firefly.mp4")));
    loader.OpenVideo();

    gul::VideoFrame frame;
    int frameCount = 0;
    loader.GetNext(frame);
    while(loader.IsFrameValid())
    {
      ++frameCount;
      loader.GetNext(frame);
    }
    TEST_EQUAL(frameCount, 50);

    return EXIT_SUCCESS;
  }

  int ReadTwice(void)
  {
    gul::VideoLoader loader(gul::CTestData::GetFilePath(gul::String("video"), gul::String("firefly.mkv")));
    loader.OpenVideo();

    gul::VideoFrame frame;
    int frameCount = 0;
    loader.GetNext(frame);
    while(loader.IsFrameValid())
    {
      ++frameCount;
      loader.GetNext(frame);
    }
    TEST_EQUAL(frameCount, 50);
    loader.CloseVideo();

    loader.OpenVideo();
    frameCount = 0;
    loader.GetNext(frame);
    while(loader.IsFrameValid())
    {
      ++frameCount;
      loader.GetNext(frame);
    }
    TEST_EQUAL(frameCount, 50);

    return EXIT_SUCCESS;
  }
}

