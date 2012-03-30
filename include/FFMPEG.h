#pragma once
#ifndef _GUL_VIDEO_FFMPEG_H_
#define _GUL_VIDEO_FFMPEG_H_
/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011 #FIRST AND LAST NAME#.
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

#include "String.h"

#include <cstdint>

class AVFormatContext;
class AVCodecContext;
class AVCodec;
class AVFrame;
class SwsContext;


namespace gul
{

  class FFMPEG
  {
    public:
      FFMPEG(const gul::String& videoPath);
      ~FFMPEG(void);

      void OpenVideo(void);
  private:
      void SaveFrame(int width, int height, int iFrame);
    private:
      const gul::String path;
      AVFormatContext* pFormatCtx;
      AVCodecContext* pCodecCtx;
      SwsContext* pSWSContext;
      AVCodec* pCodec;
      AVFrame* pFrame;
      AVFrame* pFrameRGBA;
      uint8_t* pDataBufferRGBA;

      static bool codecsAreRegistered;
  };

}

#endif
