#pragma once
#ifndef _GUL_MEDIA_MEDIA_WRITER_H_
#define _GUL_MEDIA_MEDIA_WRITER_H_
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

#include "File.h"

#include <cstdint>

namespace gul
{
  class VideoFrame;
  class MediaReader;
  class MediaConverter;
}
class AVFormatContext;
class AVCodecContext;
class AVFrame;
class AVPacket;
class AVCodec;
class SwsContext;
class AVStream;
class AVCodecParameters;


namespace gul
{

  class GUL_EXPORT MediaWriter
  {
    public:
      MediaWriter(const gul::File& rVideoPath, int width, int height, int fps = 30, int bitrate = 4000000);
      ~MediaWriter(void);

      bool OpenVideo(void);
      void CloseVideo(void);
      void AddFrame(const gul::VideoFrame& rFrame);

    private:
      MediaWriter(const gul::File& rVideoPath);
      void setSize(int width, int height);
      bool openVideo(const AVFormatContext& rInputFormatCtx);
      void writePacket(AVPacket& rPacket);
      friend class gul::MediaConverter;

    private:
      void setDafaultVideoEncoderCtxSettings(void);
      void fillFrameRGBA(const gul::VideoFrame& rFrame);
      void encodeAndSaveVideoFrame(AVFrame* pFrameToEncode);
      void allocateStructures(void);
      void prepareOutputFile(void);

    private:
      const gul::File m_path;
      AVFormatContext* m_pFormatCtx;
      AVCodecContext* m_pVideoCodecCtx;
      SwsContext* m_pSWSContext;
      AVStream* m_pVideoStream;
      AVCodec* m_pVideoCodec;
      AVFrame* m_pFrame;
      AVPacket* m_pPacket;
      bool m_isClosed;
      int m_videoWidth;
      int m_videoHeight;
      int m_videoFPS;
      int m_videoBitrate;
      const bool usePTSFromFrames;
  };

}

#endif
