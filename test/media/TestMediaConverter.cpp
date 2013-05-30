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
#include "ImageFileHandler.h"
#include "AnalyzerImageEquality.h"
#include "MediaConverter.h"
#include "VideoFrame.h"
#include "VideoFrameManipulator.h"
#include "VFM2DToSBSDelay.h"

namespace TestMediaConverter
{
  class CopyManipulator : public gul::VideoFrameManipulator
  {
      virtual void Execute(const gul::Image& input, gul::Image& output)
      {
        output = input;
      }

      virtual int GetResultWidth(int width) const
      {
        return width;
      }
      virtual int GetResultHeight(int height) const
      {
        return height;
      }
  };

  int Copy(const gul::String& file, float threshold, int gtCount)
  {
    gul::File output = gul::CTestData::GetTempFilePath(file);
    CopyManipulator manipulator;
    gul::MediaConverter converter(gul::CTestData::GetFilePath(gul::String("video"), file));
    converter.Init(output, manipulator);
    converter.Execute();

    gul::Image first = gul::ImageFileHandler::Instance().Load(gul::CTestData::GetFilePath(gul::String("video"), gul::String("firefly-first.png")));
    gul::Image middle = gul::ImageFileHandler::Instance().Load(gul::CTestData::GetFilePath(gul::String("video"), gul::String("firefly-middle.png")));
    gul::Image last = gul::ImageFileHandler::Instance().Load(gul::CTestData::GetFilePath(gul::String("video"), gul::String("firefly-last.png")));

    gul::MediaReader loader(output);
    loader.Open();
    gul::VideoFrame frame;
    gul::VideoFrame prevFrame;

    loader.GetNext(frame);
    TEST_TRUE(loader.IsFrameValid());
    TEST_TRUE(gul::AnalyzerImageEquality::Execute(first, frame, threshold));

    int count = 0;
    while(loader.IsFrameValid())
    {
      if(++count == 32)
      {
        TEST_TRUE(loader.IsFrameValid());
        TEST_TRUE(gul::AnalyzerImageEquality::Execute(middle, frame, threshold));
      }
      prevFrame = frame;
      loader.GetNext(frame);
    }

    TEST_EQUAL(count, gtCount);
    TEST_TRUE(gul::AnalyzerImageEquality::Execute(last, prevFrame, threshold));

    return EXIT_SUCCESS;
  }

  int CopyMkv(void)
  {
    return Copy("firefly.mkv", 0.006, 50);
  }

  int CopyMp4(void)
  {
    return Copy("firefly.mp4", 0.006, 52);
  }

  int CopyAvi(void)
  {
    return Copy("firefly.avi", 0.007, 50);
  }

  int CopyMov(void)
  {
    return Copy("firefly.mov", 0.006, 52);
  }

  int CopyOgv(void)
  {
    return Copy("firefly.ogv", 0.01, 52);
  }


  int Inane2DToSBS(void)
  {
    gul::File output = gul::CTestData::GetTempFilePath(gul::String("fireflySBSDelay.mkv"));
    gul::VFM2DToSBSDelay manipulator;
    manipulator.SetParameter(2);
    gul::MediaConverter converter(gul::CTestData::GetFilePath(gul::String("video"), gul::String("firefly.mkv")));
    converter.Init(output, manipulator);
    converter.Execute();

    return EXIT_SUCCESS;
  }
}

