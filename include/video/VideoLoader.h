#pragma once
#ifndef _GUL_VIDEO_VIDEO_LOADER_H_
#define _GUL_VIDEO_VIDEO_LOADER_H_
/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011-2012#FIRST AND LAST NAME#.
**
** Contact: #FIRST AND LAST NAME# (#EMAIL#)
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
** #FIRST AND LAST NAME# at #EMAIL#.
**
***************************************************************************/

#include <cstdint>

#include "File.h"
#include "Image.h"
#include "VideoSettings.h"

class AVFormatContext;
class AVCodecContext;
class AVCodec;
class AVFrame;
class SwsContext;


namespace gul
{

  class VideoLoader
  {
    public:
      VideoLoader(const gul::File& videoPath);
      ~VideoLoader(void);

      bool OpenVideo(void);
      bool IsFrameValid(void) const;
      void GetNext(Image &image);
      gul::VideoSettings GetSettings(void) const;

    private:
      bool readNextImage(Image &image);
      void setCurrentImage(gul::Image& image, const AVFrame* frame);
      bool decodeRemaining(Image &image);

    private:
      const gul::File path;
      AVFormatContext* pFormatCtx;
      AVCodecContext* pCodecCtx;
      SwsContext* pSWSContext;
      AVCodec* pCodec;
      AVFrame* pFrame;
      AVFrame* pFrameRGBA;
      uint8_t* pDataBufferRGBA;
      bool isFrameValid;
      int videoStreamIndex;
      static bool codecsAreRegistered;
  };

}

#endif
