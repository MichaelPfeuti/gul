#pragma once
#ifndef _GUL_MEDIA_MEDIA_READER_H_
#define _GUL_MEDIA_MEDIA_READER_H_
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
class SwrContext;

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
      bool readNextPacket(void);
      AVPacket* getPacket(void);
      bool decodePacket(AVCodecContext* pContext) const;

      bool getNextFrame(VideoFrame& rFrame);
      bool videoDecodingNeeded() const;

      friend class gul::MediaConverter;

    private:
      bool getNextFrame(AudioFrame& rFrame);
      bool getNextFrame(MediaFrame& rFrame);

      void allocateFrame(VideoFrame& rFrame) const;
      void allocateFrame(AudioFrame& rFrame) const;

      bool audioDecodingNeeded() const;


      void allocateVideoStructures(void);
      void allocateAudioStructures(void);

      void deleteVideoStructures(void);
      void deleteAudioStructures(void);

      void setData(VideoFrame& rTargetFrame, const AVFrame* pSourceFrame) const;
      void setData(AudioFrame& rTargetFrame, AVFrame* pSourceFrame) const;
      int openCodec(int type, AVCodecContext*& pContext) const;

    private:
      const gul::File m_path;
      AVFormatContext* m_pFormatCtx;
      AVPacket* m_pPacket;
      AVFrame* m_pFrame;
      AVFrame* m_pFrameRGBA;
      uint8_t* m_pDataBufferRGBA;

      bool m_isFrameValid;
      bool m_isOpen;

      AVCodecContext* m_pVideoCodecCtx;
      int m_videoStreamIndex;
      SwsContext* m_pSWSContext;

      AVCodecContext* m_pAudioCodecCtx;
      int m_audioStreamIndex;
      SwrContext* m_pSWRContext;
  };

}

#endif
