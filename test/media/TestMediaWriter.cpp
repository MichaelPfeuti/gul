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
#include "MediaReader.h"
#include "MediaWriter.h"
#include "ImageFileHandler.h"
#include "VideoFrame.h"

namespace TestMediaWriter
{
  bool WriteVideoData(const gul::File& video)
  {
    gul::String path = gul::CTestData::GetFilePath(gul::String("video"), gul::String("frame1.png"));
    gul::Image frame = gul::ImageFileHandler::Instance().Load(path);
    gul::MediaWriter saver(video, frame.GetWidth(), frame.GetHeight());
    saver.OpenVideo();
    for(int i = 1; i <= 52; ++i)
    {
      path = gul::CTestData::GetFilePath(gul::String("video"), gul::String("frame%.png").Arg(i));
      frame = gul::ImageFileHandler::Instance().Load(path);
      saver.AddFrame(frame);
    }
    saver.CloseVideo();

    return true;
  }

  int FirstFrame(const gul::String& file, float threshold)
  {
    gul::File video = gul::CTestData::GetTempFilePath(file);
    TEST_TRUE(WriteVideoData(video));

    gul::MediaReader loader(video);
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
    gul::File video = gul::CTestData::GetTempFilePath(file);
    TEST_TRUE(WriteVideoData(video));

    gul::MediaReader loader(video);
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
    gul::File video = gul::CTestData::GetTempFilePath(file);
    TEST_TRUE(WriteVideoData(video));

    gul::MediaReader loader(video);
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
    gul::File video = gul::CTestData::GetTempFilePath(file);
    TEST_TRUE(WriteVideoData(video));

    gul::MediaReader loader(video);
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
    return FirstFrame("firstFrame.mkv", 0.0037f);
  }

  int MiddleFrameMkv(void)
  {
    return MiddleFrame("middleFrame.mkv", 0.0043f);
  }

  int LastFrameMkv(void)
  {
    return LastFrame("lastFrame.mkv", 0.005f);
  }

  int FrameCountMkv(void)
  {
    return FrameCount("frameCount.mkv", 52);
  }

  int FirstFrameMp4(void)
  {
    return FirstFrame("firstFrame.mp4", 0.0037f);
  }

  int MiddleFrameMp4(void)
  {
    return MiddleFrame("middleFrame.mp4", 0.0043f);
  }

  int LastFrameMp4(void)
  {
    return LastFrame("lastFrame.mp4", 0.005f);
  }

  int FrameCountMp4(void)
  {
    return FrameCount("frameCount.mp4", 52);
  }

  int FirstFrameAvi(void)
  {
    return FirstFrame("firstFrame.avi", 0.0042f);
  }

  int MiddleFrameAvi(void)
  {
    return MiddleFrame("middleFrame.avi", 0.0046f);
  }

  int LastFrameAvi(void)
  {
    return LastFrame("lastFrame.avi", 0.0055f);
  }

  int FrameCountAvi(void)
  {
    return FrameCount("frameCount.avi", 52);
  }

  int FirstFrameMov(void)
  {
    return FirstFrame("firstFrame.mov", 0.0037f);
  }

  int MiddleFrameMov(void)
  {
    return MiddleFrame("middleFrame.mov", 0.0043f);
  }

  int LastFrameMov(void)
  {
    return LastFrame("lastFrame.mov", 0.005f);
  }

  int FrameCountMov(void)
  {
    return FrameCount("frameCount.mov", 52);
  }

  int FirstFrameOgv(void)
  {
    return FirstFrame("firstFrame.ogv", 0.0044f);
  }

  int MiddleFrameOgv(void)
  {
    return MiddleFrame("middleFrame.ogv", 0.0055f);
  }

  int LastFrameOgv(void)
  {
    return LastFrame("lastFrame.ogv", 0.0066f);
  }

  int FrameCountOgv(void)
  {
    return FrameCount("frameCount.ogv", 52);
  }
}

