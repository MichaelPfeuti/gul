#pragma once
#ifndef _GUL_VIDEO_VIDEO_SAVER_H_
#define _GUL_VIDEO_VIDEO_SAVER_H_
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

#include "File.h"

#include <cstdint>

namespace gul
{
  class Image;
}
class AVFormatContext;
class AVCodecContext;
class AVCodec;
class AVFrame;
class SwsContext;
class AVStream;


namespace gul
{

  class VideoSaver
  {
    public:
      VideoSaver(const gul::File& videoPath, int width, int height, int fps = 30, int bitrate = 4000000);
      ~VideoSaver(void);

      bool OpenVideo(void);
      void CloseVideo(void);
      void AddImage(const gul::Image& image);

    private:
      void fillFrameRGBA(const gul::Image& image);
      bool encodeAndSave(AVFrame* pFrameToEncode);

    private:
      const gul::File path;
      AVFormatContext* pFormatCtx;
      AVCodecContext* pCodecCtx;
      SwsContext* pSWSContext;
      AVStream* pVideoStream;
      AVCodec* pVideoCodec;
      AVFrame* pFrame;
      AVFrame* pFrameRGBA;
      bool isClosed;
      int videoWidth;
      int videoHeight;
      int videoFPS;
      int videoBitrate;

      static bool codecsAreRegistered;
  };

}

#endif
