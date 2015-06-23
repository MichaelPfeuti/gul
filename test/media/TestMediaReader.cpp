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
#include "MediaReader.h"
#include "ImageFileHandler.h"
#include "AudioFrame.h"
#include "VideoFrame.h"

namespace TestMediaReader
{

  int FirstFrame(const gul::String& file, float threshold)
  {
    gul::MediaReader loader(gul::CTestData::GetFilePath(gul::String("video"), file));
    loader.Open();

    gul::VideoFrame frame;
    loader.GetNext(frame);
    TEST_TRUE(loader.IsFrameValid());

    gul::Image first = gul::ImageFileHandler::Instance().Load(gul::CTestData::GetFilePath(gul::String("video"), gul::String("firefly-first.png")));

    TEST_EQUAL_IMAGE(frame, first, threshold);

    return EXIT_SUCCESS;
  }

  int MiddleFrame(const gul::String& file, float threshold)
  {
    gul::MediaReader loader(gul::CTestData::GetFilePath(gul::String("video"), file));
    loader.Open();

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

    TEST_EQUAL_IMAGE(frame, middle, threshold);

    return EXIT_SUCCESS;
  }

  int LastFrame(const gul::String& file, float threshold)
  {
    gul::MediaReader loader(gul::CTestData::GetFilePath(gul::String("video"), file));
    loader.Open();

    gul::VideoFrame frame;
    gul::VideoFrame framePrev;
    loader.GetNext(frame);
    while(loader.IsFrameValid())
    {
      framePrev = frame;
      loader.GetNext(frame);
    }

    gul::Image last = gul::ImageFileHandler::Instance().Load(gul::CTestData::GetFilePath(gul::String("video"), gul::String("firefly-last.png")));

    TEST_EQUAL_IMAGE(framePrev, last, threshold);

    return EXIT_SUCCESS;
  }


  int FrameCount(const gul::String& file, int count)
  {
    gul::MediaReader loader(gul::CTestData::GetFilePath(gul::String("video"), file));
    loader.Open();

    gul::VideoFrame frame;
    int frameCount = 0;
    loader.GetNext(frame);
    while(loader.IsFrameValid())
    {
      ++frameCount;
      loader.GetNext(frame);
    }

    TEST_EQUAL(frameCount, count);

    return EXIT_SUCCESS;
  }

  int FirstFrameMkv(void)
  {
    return FirstFrame("firefly.mkv", 0.f);
  }

  int MiddleFrameMkv(void)
  {
    return MiddleFrame("firefly.mkv", 0.f);
  }

  int LastFrameMkv(void)
  {
    return LastFrame("firefly.mkv", 0.f);
  }

  int FrameCountMkv(void)
  {
    return FrameCount("firefly.mkv", 50);
  }

  int FirstFrameMp4(void)
  {
    return FirstFrame("firefly.mp4", 0.001f);
  }

  int MiddleFrameMp4(void)
  {
    return MiddleFrame("firefly.mp4", 0.0025f);
  }

  int LastFrameMp4(void)
  {
    return LastFrame("firefly.mp4", 0.0035f);
  }

  int FrameCountMp4(void)
  {
    return FrameCount("firefly.mp4", 52);
  }

  int FirstFrameAvi(void)
  {
    return FirstFrame("firefly.avi", 0.0025f);
  }

  int MiddleFrameAvi(void)
  {
    return MiddleFrame("firefly.avi", 0.005f);
  }

  int LastFrameAvi(void)
  {
    return LastFrame("firefly.avi", 0.006f);
  }

  int FrameCountAvi(void)
  {
    return FrameCount("firefly.avi", 50);
  }

  int FirstFrameMov(void)
  {
    return FirstFrame("firefly.mov", 0.001f);
  }

  int MiddleFrameMov(void)
  {
    return MiddleFrame("firefly.mov", 0.0025f);
  }

  int LastFrameMov(void)
  {
    return LastFrame("firefly.mov", 0.0035f);
  }

  int FrameCountMov(void)
  {
    return FrameCount("firefly.mov", 52);
  }

  int FirstFrameOgv(void)
  {
    return FirstFrame("firefly.ogv", 0.0027f);
  }

  int MiddleFrameOgv(void)
  {
    return MiddleFrame("firefly.ogv", 0.005f);
  }

  int LastFrameOgv(void)
  {
    return LastFrame("firefly.ogv", 0.0061f);
  }

  int FrameCountOgv(void)
  {
    return FrameCount("firefly.ogv", 52);
  }

  int ReadTwice(void)
  {
    gul::MediaReader loader(gul::CTestData::GetFilePath(gul::String("video"), gul::String("firefly.mkv")));
    loader.Open();

    gul::VideoFrame frame;
    int frameCount = 0;
    loader.GetNext(frame);
    while(loader.IsFrameValid())
    {
      ++frameCount;
      loader.GetNext(frame);
    }
    TEST_EQUAL(frameCount, 50);
    loader.Close();

    loader.Open();
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

  int ReadMp3Cover(void)
  {
    gul::Image gt = gul::ImageFileHandler::Instance().Load(gul::CTestData::GetFilePath(gul::String("audio"), gul::String("acdcCover.png")));

    gul::MediaReader loader(gul::CTestData::GetFilePath(gul::String("audio"), gul::String("acdc.mp3")));
    TEST_TRUE(loader.Open());

    gul::VideoFrame frame;
    loader.GetNext(frame);
    TEST_EQUAL_IMAGE(frame, gt, 0.f);
    TEST_TRUE(loader.IsFrameValid());

    loader.GetNext(frame);
    TEST_FALSE(loader.IsFrameValid());

    loader.Close();

    return EXIT_SUCCESS;
  }
}

