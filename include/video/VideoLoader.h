#pragma once
#ifndef _GUL_VIDEO_VIDEO_LOADER_H_
#define _GUL_VIDEO_VIDEO_LOADER_H_
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

#include <cstdint>

#include "File.h"
namespace gul
{
  class VideoFrame;
  class VideoConverter;
}

class AVFormatContext;
class AVCodecContext;
class AVFrame;
class AVPacket;
class SwsContext;


namespace gul
{

  class GUL_EXPORT VideoLoader
  {
    public:
      VideoLoader(const gul::File& rVideoPath);
      ~VideoLoader(void);

      bool OpenVideo(void);
      void CloseVideo(void);
      bool IsFrameValid(void) const;
      void GetNext(VideoFrame& rFrame);
      int GetWidth(void) const;
      int GetHeight(void) const;

    private:
      AVPacket* getNextPacket(void);
      void freePacket(void);
      bool decodeVideoPacket(AVPacket& rPacket, VideoFrame& rFrame);
      bool isVideoPacket(const AVPacket& rPacket) const;
      void allocateVideoFrame(VideoFrame& rFrame) const;
      friend class gul::VideoConverter;

    private:
      bool readNextImage(VideoFrame& rFrame);
      void setImageData(VideoFrame& rTargetFrame, const AVFrame* pSourceFrame) const;
      bool decodeRemaining(VideoFrame& rFrame);

    private:
      const gul::File m_path;
      AVFormatContext* m_pFormatCtx;
      AVCodecContext* m_pVideoCodecCtx;
      SwsContext* m_pSWSContext;
      AVPacket* m_pPacket;
      AVFrame* m_pFrame;
      AVFrame* m_pFrameRGBA;
      uint8_t* m_pDataBufferRGBA;
      bool m_isFrameValid;
      bool m_isVideoOpen;
      bool m_isPacketDataFreed;
      int m_videoStreamIndex;
      int m_currentFrameIndex;
      static bool codecsAreRegistered;
  };

}

#endif
