#pragma once
#ifndef _GUL_MEDIA_MEDIA_READER_H_
#define _GUL_MEDIA_MEDIA_READER_H_
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
  class AudioFrame;
  class MediaFrame;
  class VideoFrame;
  class MediaConverter;
}

class AVFormatContext;
class AVCodecContext;
class AVFrame;
class AVPacket;
class SwsContext;

namespace gul
{

  class GUL_EXPORT MediaReader
  {
    public:
      MediaReader(const gul::File& rPath);
      ~MediaReader(void);

      bool Open(void);
      void Close(void);

      bool IsFrameValid(void) const;

      // Video
      void GetNext(VideoFrame& rFrame);
      int GetWidth(void) const;
      int GetHeight(void) const;
      bool HasVideo(void) const;

      // Audio
      void GetNext(AudioFrame& rFrame);
      bool HasAudio(void) const;
      int GetChannels(void) const;
      int GetSampleRate(void) const;

      // Media
      void GetNext(MediaFrame& rFrame);

  private:
      // Shared API with MediaConverter
      AVPacket* getNextPacket(void);
      void freePacket(void);

      bool decodePacket(AVPacket& rPacket, VideoFrame& rFrame);
      bool decodePacket(AVPacket& rPacket, AudioFrame& rFrame);

      bool isVideoPacket(const AVPacket& rPacket) const;
      bool isAudioPacket(const AVPacket& rPacket) const;

      void allocateFrame(VideoFrame& rFrame) const;
      void allocateFrame(AudioFrame& rFrame) const;

      friend class gul::MediaConverter;

    private:
      //
      void allocateVideoStructures(void);
      void deleteVideoStructures(void);
      void setData(VideoFrame& rTargetFrame, const AVFrame* pSourceFrame) const;
      void setData(AudioFrame& rTargetFrame, const AVFrame* pSourceFrame) const;
      bool decodeRemaining(VideoFrame& rFrame);
      int openCodec(int type, AVCodecContext *&pContext);

    private:
      const gul::File m_path;
      AVFormatContext* m_pFormatCtx;
      SwsContext* m_pSWSContext;
      AVPacket* m_pPacket;
      AVFrame* m_pFrame;
      AVFrame* m_pFrameRGBA;
      uint8_t* m_pDataBufferRGBA;

      bool m_isFrameValid;
      bool m_isOpen;
      bool m_isPacketDataFreed;

      AVCodecContext* m_pVideoCodecCtx;
      int m_videoStreamIndex;

      AVCodecContext* m_pAudioCodecCtx;
      int m_audioStreamIndex;

      static bool codecsAreRegistered;
  };

}

#endif
