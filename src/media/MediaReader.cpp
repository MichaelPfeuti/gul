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

#include "MediaReader.h"
#include "Assert.h"
#include "AudioFrame.h"
#include "VideoFrame.h"
#include "MediaFrame.h"

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

bool gul::MediaReader::codecsAreRegistered = false;

gul::MediaReader::MediaReader(const gul::File& rPath)
  : m_path(rPath),
    m_pFormatCtx(nullptr),
    m_pSWSContext(nullptr),
    m_pPacket(nullptr),
    m_pFrame(nullptr),
    m_pFrameRGBA(nullptr),
    m_pDataBufferRGBA(nullptr),
    m_isFrameValid(false),
    m_isOpen(false),
    m_isPacketDataFreed(true),
    m_pVideoCodecCtx(nullptr),
    m_videoStreamIndex(AVERROR_STREAM_NOT_FOUND),
    m_pAudioCodecCtx(nullptr),
    m_audioStreamIndex(AVERROR_STREAM_NOT_FOUND)
{
  if(!codecsAreRegistered)
  {
    av_register_all();
    codecsAreRegistered = true;
  }
}


gul::MediaReader::~MediaReader(void)
{
  if(m_isOpen)
  {
    Close();
  }
}

void gul::MediaReader::deleteVideoStructures(void)
{
  av_free(m_pDataBufferRGBA);
  av_free(m_pFrameRGBA);
  m_pDataBufferRGBA = nullptr;
  m_pFrameRGBA = nullptr;

  // Free the frame buffer
  av_free(m_pFrame);
  m_pFrame = nullptr;

  // free swscale context
  sws_freeContext(m_pSWSContext);
  m_pSWSContext = nullptr;
}

void gul::MediaReader::Close(void)
{
  // free packet
  if(m_isOpen)
  {
    if(!m_isPacketDataFreed)
      av_free_packet(m_pPacket);
    GUL_DELETE(m_pPacket);
  }

  // Close the codecs
  if(HasVideo())
  {
    avcodec_close(m_pVideoCodecCtx);
    m_pVideoCodecCtx = nullptr;
    m_videoStreamIndex = AVERROR_STREAM_NOT_FOUND;

    // Free RGBA memory
    deleteVideoStructures();
  }
  if(HasAudio())
  {
    avcodec_close(m_pAudioCodecCtx);
    m_pAudioCodecCtx = nullptr;
    m_audioStreamIndex = AVERROR_STREAM_NOT_FOUND;
  }

  // Close the video file
  avformat_close_input(&m_pFormatCtx);
  m_pFormatCtx = nullptr;

  m_isFrameValid = false;
  m_isOpen = false;
  m_isPacketDataFreed = true;
}

void gul::MediaReader::allocateVideoStructures(void)
{
  m_pFrame = avcodec_alloc_frame();

  // Allocate an AVFrame structure
  m_pFrameRGBA = avcodec_alloc_frame();

  // Determine required buffer size and allocate buffer
  int numBytes;
  numBytes = avpicture_get_size(PIX_FMT_RGBA, m_pVideoCodecCtx->width,
                                m_pVideoCodecCtx->height);
  m_pDataBufferRGBA = (uint8_t*)av_malloc(numBytes * sizeof(uint8_t));

  // Assign appropriate parts of buffer to image planes in pFrameRGB
  // Note that pFrameRGBA is an AVFrame, but AVFrame is a superset
  // of AVPicture
  avpicture_fill((AVPicture*)m_pFrameRGBA, m_pDataBufferRGBA, PIX_FMT_RGBA,
                 m_pVideoCodecCtx->width, m_pVideoCodecCtx->height);


  // swscaler context
  m_pSWSContext = sws_getCachedContext(m_pSWSContext,
                                     m_pVideoCodecCtx->width, m_pVideoCodecCtx->height, m_pVideoCodecCtx->pix_fmt,
                                     m_pVideoCodecCtx->width, m_pVideoCodecCtx->height, PIX_FMT_RGBA,
                                     SWS_BILINEAR, nullptr, nullptr, nullptr);
}

bool gul::MediaReader::Open(void)
{
  GUL_ASSERT(!m_isOpen);
  GUL_ASSERT(m_path.IsPathValid());

  // Open video file
  if(avformat_open_input(&m_pFormatCtx, m_path.GetPath().GetData(), nullptr, nullptr) != 0)
    GUL_FAIL("Couldn't open file");

  // Retrieve stream information
  if(avformat_find_stream_info(m_pFormatCtx, nullptr) < 0)
    GUL_FAIL("Couldn't find stream information");

  //av_dump_format(pFormatCtx, 0, path.GetData(), 0);

  m_videoStreamIndex = openCodec(AVMEDIA_TYPE_VIDEO, m_pVideoCodecCtx);
  m_audioStreamIndex = openCodec(AVMEDIA_TYPE_AUDIO, m_pAudioCodecCtx);

  if(m_videoStreamIndex != AVERROR_STREAM_NOT_FOUND )
  {
    allocateVideoStructures();
  }

  if(m_audioStreamIndex != AVERROR_STREAM_NOT_FOUND)
  {
    m_pAudioCodecCtx->request_sample_fmt = AV_SAMPLE_FMT_S16;
  }

  m_isOpen = m_videoStreamIndex != AVERROR_STREAM_NOT_FOUND ||
             m_audioStreamIndex != AVERROR_STREAM_NOT_FOUND;


  if(m_isOpen)
  {
    // packet into which to read piece
    m_pPacket = new AVPacket;
    av_init_packet(m_pPacket);
    m_isPacketDataFreed = true;
  }

  return m_isOpen;
}

int gul::MediaReader::openCodec(int type, AVCodecContext*& pContext)
{
  AVMediaType mediaType = static_cast<AVMediaType>(type);
  int index = av_find_best_stream(m_pFormatCtx, mediaType, -1, -1, nullptr, 0);
  if(index != AVERROR_STREAM_NOT_FOUND)
  {
    pContext = m_pFormatCtx->streams[index]->codec;
    pContext->thread_count = 4;
    AVCodec* pVideoCodec = avcodec_find_decoder(pContext->codec_id);
    if(pVideoCodec == nullptr)
      return AVERROR_STREAM_NOT_FOUND;

    if(avcodec_open2(pContext, pVideoCodec, nullptr) < 0)
      return AVERROR_STREAM_NOT_FOUND;
  }

  return index;
}

AVPacket* gul::MediaReader::getNextPacket(void)
{
  if(!m_isPacketDataFreed)
  {
    av_free_packet(m_pPacket);
    av_init_packet(m_pPacket);
  }

  if(av_read_frame(m_pFormatCtx, m_pPacket) < 0)
    return nullptr;

  m_isPacketDataFreed = false;
  return m_pPacket;
}

bool gul::MediaReader::decodePacket(AVPacket& rPacket, gul::VideoFrame& rFrame)
{
  GUL_ASSERT_MSG(rFrame.GetImageFormat() == gul::Image::IF_RGBA, "Video Frame is not RGBA!");

  int frameFinished;
  // Decode video frame
  int len;
  if((len = avcodec_decode_video2(m_pVideoCodecCtx, m_pFrame, &frameFinished, &rPacket)) < 0)
    GUL_FAIL("Video decoding failed!");

  fprintf(stderr, "%d %d\n", len, rPacket.size);

  // Did we get a frame?
  if(frameFinished)
  {
    setData(rFrame, m_pFrame);

    AVRational timeBase = m_pFormatCtx->streams[m_videoStreamIndex]->time_base;
    double pts = AV_NOPTS_VALUE == m_pFrame->pkt_pts ? m_pVideoCodecCtx->frame_number : m_pFrame->pkt_pts;
    rFrame.SetPresentationTime(pts*timeBase.num/timeBase.den);
    rFrame.SetFrameIndex(m_pVideoCodecCtx->frame_number);
  }

  return frameFinished;
}

bool gul::MediaReader::decodePacket(AVPacket& rPacket, gul::AudioFrame& rFrame)
{
  int frameFinished;
  // Decode audio frame
  int len;
  if((len = avcodec_decode_audio4(m_pAudioCodecCtx, m_pFrame, &frameFinished, &rPacket)) < 0)
    GUL_FAIL("Audio decoding failed!");

  fprintf(stderr, "%d: %d %d\n", m_pAudioCodecCtx->frame_number, len, rPacket.size);

  // Did we get a frame?
  if(frameFinished)
  {
    setData(rFrame, m_pFrame);

    AVRational timeBase = m_pFormatCtx->streams[m_audioStreamIndex]->time_base;
    double pts = AV_NOPTS_VALUE == m_pFrame->pkt_pts ? m_pAudioCodecCtx->frame_number : m_pFrame->pkt_pts;
    rFrame.SetPresentationTime(pts*timeBase.num/timeBase.den);
    rFrame.SetFrameIndex(m_pAudioCodecCtx->frame_number);
  }

  return frameFinished;
}

bool gul::MediaReader::isVideoPacket(const AVPacket& rPacket) const
{
  return rPacket.stream_index == m_videoStreamIndex;
}

bool gul::MediaReader::isAudioPacket(const AVPacket& rPacket) const
{
  return rPacket.stream_index == m_audioStreamIndex;
}

bool gul::MediaReader::decodeRemaining(VideoFrame& rFrame)
{
  AVPacket packet;
  av_init_packet(&packet);
  packet.data = nullptr;
  packet.size = 0;

  return decodePacket(packet, rFrame);
}

void gul::MediaReader::setData(gul::VideoFrame& rTargetFrame, const AVFrame* pSourceFrame) const
{
  uint8_t* pData = rTargetFrame.GetData();
  int pitch = rTargetFrame.GetPitch();

  if(pSourceFrame != nullptr)
  {
    // Convert the image from its native format to RGBA
    //Scale the raw data/convert it to our video buffer...
    if(sws_scale(m_pSWSContext,
                 pSourceFrame->data, pSourceFrame->linesize,
                 0, m_pVideoCodecCtx->height,
                 &pData, &pitch) <  m_pVideoCodecCtx->height)
      GUL_FAIL("Image conversion failed!");
  }
  else
  {
    memset(pData, 0, pitch*rTargetFrame.GetHeight());
  }
}

void gul::MediaReader::setData(gul::AudioFrame& rTargetFrame, const AVFrame* pSourceFrame) const
{
  int16_t* s16Data = reinterpret_cast<int16_t*>(pSourceFrame->data[0]);
  rTargetFrame.SetData(s16Data, pSourceFrame->nb_samples);
  int frameSize = av_samples_get_buffer_size(NULL, GetChannels(),
                                             pSourceFrame->nb_samples,
                                             AV_SAMPLE_FMT_S16, 1);
  fprintf(stderr, "%d %d\n", frameSize, pSourceFrame->nb_samples);
}


void gul::MediaReader::allocateFrame(VideoFrame& rFrame) const
{
  if(rFrame.GetWidth() != m_pVideoCodecCtx->width ||
     rFrame.GetHeight() != m_pVideoCodecCtx->height ||
     rFrame.GetImageFormat() != gul::Image::IF_RGBA)
  {
    rFrame = gul::VideoFrame(m_pVideoCodecCtx->width, m_pVideoCodecCtx->height, gul::Image::IF_RGBA);
  }
}

void gul::MediaReader::allocateFrame(AudioFrame& rFrame) const
{
  if(rFrame.GetChannels() != m_pAudioCodecCtx->channels ||
     rFrame.GetSampleRate() != m_pAudioCodecCtx->sample_rate)
  {
    rFrame = gul::AudioFrame(m_pAudioCodecCtx->channels, m_pAudioCodecCtx->sample_rate);
  }
}

bool gul::MediaReader::IsFrameValid(void) const
{
  return m_isFrameValid;
}

void gul::MediaReader::GetNext(gul::VideoFrame& rFrame)
{
  GUL_ASSERT(HasVideo());

  allocateFrame(rFrame);

  AVPacket* pNextPacket = getNextPacket();
  while(pNextPacket != nullptr)
  {
    if(isVideoPacket(*pNextPacket))
    {
      if(decodePacket(*pNextPacket, rFrame))
      {
        m_isFrameValid= true;
        return;
      }
    }
    pNextPacket = getNextPacket();
  }

  m_isFrameValid = decodeRemaining(rFrame);

  if(!IsFrameValid())
    setData(rFrame, nullptr);
}

void gul::MediaReader::GetNext(AudioFrame& rFrame)
{
  GUL_ASSERT(HasAudio());

  allocateFrame(rFrame);

  AVPacket* pNextPacket = getNextPacket();
  while(pNextPacket != nullptr)
  {
    if(isAudioPacket(*pNextPacket))
    {
      if(decodePacket(*pNextPacket, rFrame))
      {
        m_isFrameValid= true;
        return;
      }
    }
    pNextPacket = getNextPacket();
  }

  // TODO: set null value
  m_isFrameValid = false;
}

void gul::MediaReader::GetNext(MediaFrame& rFrame)
{
  GUL_ASSERT(m_isOpen);
//  AVPacket* packet = getNextPacket();
//  if(packet != nullptr && isVideoPacket(*packet))
//  {
//    GetNext(rFrame.GetVideoFrame());
//    rFrame.SetHasAudioFrame(false);
//    rFrame.SetHasVideoFrame(true);
//  }
//  else if(packet != nullptr && isAudioPacket(*packet))
//  {
//    GetNext(rFrame.GetAudioFrame());
//    rFrame.SetHasAudioFrame(true);
//    rFrame.SetHasVideoFrame(false);
//  }
//  else
//  {
//    rFrame.SetHasAudioFrame(false);
//    rFrame.SetHasVideoFrame(false);
//  }
}

int gul::MediaReader::GetWidth(void) const
{
  GUL_ASSERT(HasVideo());
  return m_pVideoCodecCtx->width;
}

int gul::MediaReader::GetHeight(void) const
{
  GUL_ASSERT(HasVideo());
  return m_pVideoCodecCtx->height;
}

bool gul::MediaReader::HasAudio(void) const
{
  GUL_ASSERT(m_isOpen);
  return m_audioStreamIndex != AVERROR_STREAM_NOT_FOUND;
}

bool gul::MediaReader::HasVideo(void) const
{
  GUL_ASSERT(m_isOpen);
  return m_videoStreamIndex != AVERROR_STREAM_NOT_FOUND;
}

int gul::MediaReader::GetChannels(void) const
{
  GUL_ASSERT(HasAudio());
  return m_pAudioCodecCtx->channels;
}

int gul::MediaReader::GetSampleRate(void) const
{
  GUL_ASSERT(HasAudio());
  return m_pAudioCodecCtx->sample_rate;
}
