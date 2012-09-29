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
#include "VideoSaver.h"
#include "ImageFileHandler.h"

namespace TestVideoSaver
{
  int WriteReadAndCountFrames(const gul::File& video)
  {
    gul::Image first = gul::ImageFileHandler::Instance().Load(gul::CTestData::GetFilePath(gul::String("video"), gul::String("firefly-first.png")));
    gul::VideoSaver saver(video, gul::VideoSettings(first.GetWidth(), first.GetHeight()));
    saver.OpenVideo();
    for(int i = 0; i < 15; ++i)
    {
      saver.AddImage(first);
    }
    gul::Image middle = gul::ImageFileHandler::Instance().Load(gul::CTestData::GetFilePath(gul::String("video"), gul::String("firefly-middle.png")));
    for(int i = 0; i < 15; ++i)
    {
      saver.AddImage(middle);
    }
    gul::Image last = gul::ImageFileHandler::Instance().Load(gul::CTestData::GetFilePath(gul::String("video"), gul::String("firefly-last.png")));
    for(int i = 0; i < 15; ++i)
    {
      saver.AddImage(last);
    }
    saver.CloseVideo();

    gul::VideoLoader loader(video);
    loader.OpenVideo();
    gul::Image frame;
    int frameCount = 0;
    loader.GetNext(frame);
    while(loader.IsFrameValid())
    {
      ++frameCount;
      loader.GetNext(frame);
    }

    TEST_EQUAL(frameCount, 45);

    return EXIT_SUCCESS;
  }

  int WriteReadMp4(void)
  {
    return WriteReadAndCountFrames(gul::CTestData::GetTempFilePath(gul::String("frameCount.mp4")));
  }

  int WriteReadMatroska(void)
  {
    return WriteReadAndCountFrames(gul::CTestData::GetTempFilePath(gul::String("frameCount.mkv")));
  }

  int CopyAndCompare(void)
  {
    gul::VideoLoader loader(gul::CTestData::GetFilePath(gul::String("video"), gul::String("firefly.mkv")));
    loader.OpenVideo();
    gul::VideoSaver saver(gul::CTestData::GetTempFilePath(gul::String("test.mp4")), loader.GetSettings());
    saver.OpenVideo();

    gul::Image frame;
    int i = 0;
    loader.GetNext(frame);
    while(loader.IsFrameValid())
    {
      saver.AddImage(frame);
      ++i;
      fprintf(stderr, "%d\n", i);
      loader.GetNext(frame);
    }

    return EXIT_SUCCESS;
  }
}

