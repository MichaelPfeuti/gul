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

#include "VideoLoader.h"
#include "Assert.h"
#include "VideoFrame.h"

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

bool gul::VideoLoader::codecsAreRegistered = false;

gul::VideoLoader::VideoLoader(const gul::File& rVideoPath)
  : m_path(rVideoPath),
    m_pFormatCtx(nullptr),
    m_pVideoCodecCtx(nullptr),
    m_pSWSContext(nullptr),
    m_pPacket(nullptr),
    m_pFrame(nullptr),
    m_pFrameRGBA(nullptr),
    m_pDataBufferRGBA(nullptr),
    m_isFrameValid(false),
    m_isVideoOpen(false),
    m_isPacketDataFreed(true),
    m_currentFrameIndex(0)
{
  if(!codecsAreRegistered)
  {
    av_register_all();
    codecsAreRegistered = true;
  }
}


gul::VideoLoader::~VideoLoader(void)
{
  if(m_isVideoOpen)
  {
    CloseVideo();
  }
}

void gul::VideoLoader::CloseVideo(void)
{
  // Free RGBA memory
  av_free(m_pDataBufferRGBA);
  av_free(m_pFrameRGBA);
  m_pDataBufferRGBA = nullptr;
  m_pFrameRGBA = nullptr;

  // Free the frame buffer
  av_free(m_pFrame);
  m_pFrame = nullptr;

  // free swscale context
  av_free(m_pSWSContext);
  m_pSWSContext = nullptr;

  // free packet
  if(!m_isPacketDataFreed)
    av_free_packet(m_pPacket);
  GUL_DELETE(m_pPacket);

  // Close the codec
  avcodec_close(m_pVideoCodecCtx);
  m_pVideoCodecCtx = nullptr;

  // Close the video file
  avformat_close_input(&m_pFormatCtx);
  m_pFormatCtx = nullptr;

  m_isFrameValid = false;
  m_isVideoOpen = false;
  m_isPacketDataFreed = true;
  m_currentFrameIndex = 0;
}

bool gul::VideoLoader::OpenVideo(void)
{
  ASSERT(!m_isVideoOpen);
  ASSERT(m_path.IsPathValid());

  // Open video file
  if(avformat_open_input(&m_pFormatCtx, m_path.GetPath().GetData(), nullptr, nullptr) != 0)
    FAIL("Couldn't open file");

  // Retrieve stream information
  if(avformat_find_stream_info(m_pFormatCtx, nullptr) < 0)
    FAIL("Couldn't find stream information");

  //av_dump_format(pFormatCtx, 0, path.GetData(), 0);

  // Find the best video stream
  m_videoStreamIndex =  av_find_best_stream(m_pFormatCtx, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
  if(m_videoStreamIndex == AVERROR_STREAM_NOT_FOUND)
    FAIL("Didn't find a video stream");

  // Get a pointer to the codec context for the video stream
  m_pVideoCodecCtx = m_pFormatCtx->streams[m_videoStreamIndex]->codec;

  // enable multithreading
  m_pVideoCodecCtx->thread_count = 2;

  // Find the decoder for the video stream
  AVCodec* pCodec = avcodec_find_decoder(m_pVideoCodecCtx->codec_id);
  if(pCodec == nullptr)
    FAIL("Unsupported codec!\n");

  // Open codec
  if(avcodec_open2(m_pVideoCodecCtx, pCodec, nullptr) < 0)
    FAIL("Could not open codec");

  // Allocate video frame
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

  // packet into which to read piece
  m_pPacket = new AVPacket;
  av_init_packet(m_pPacket);
  m_isPacketDataFreed = true;

  m_isVideoOpen = true;
  return true;
}

bool gul::VideoLoader::readNextImage(gul::VideoFrame& rFrame)
{
  AVPacket* pNextPacket = getNextPacket();
  while(pNextPacket != nullptr)
  {
    if(isVideoPacket(*pNextPacket))
    {
      if(decodeVideoPacket(*pNextPacket, rFrame))
        return true;
    }
    pNextPacket = getNextPacket();
  }

  if(decodeRemaining(rFrame))
    return true;

  setImageData(rFrame, nullptr);
  return false;
}

AVPacket* gul::VideoLoader::getNextPacket(void)
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

bool gul::VideoLoader::decodeVideoPacket(AVPacket& rPacket, gul::VideoFrame& rFrame)
{
  ASSERT_MSG(rFrame.GetImageFormat() == gul::Image::IF_RGBA, "Video Frame is not RGBA!");

  int frameFinished;
  // Decode video frame
  if(avcodec_decode_video2(m_pVideoCodecCtx, m_pFrame, &frameFinished, &rPacket) < 0)
    FAIL("Decoding failed!");

  // Did we get a video frame?
  if(frameFinished)
  {
    setImageData(rFrame, m_pFrame);
    uint64_t pts = av_rescale_q(m_pFrame->pkt_pts, m_pFormatCtx->streams[m_videoStreamIndex]->time_base, m_pVideoCodecCtx->time_base);
    pts /= m_pFormatCtx->streams[m_videoStreamIndex]->codec->ticks_per_frame;
    rFrame.SetPresentationTime(pts);

    rFrame.SetFrameIndex(m_currentFrameIndex);
    ++m_currentFrameIndex;
  }

  return frameFinished;
}

bool gul::VideoLoader::isVideoPacket(const AVPacket& rPacket) const
{
  return rPacket.stream_index == m_videoStreamIndex;
}

bool gul::VideoLoader::decodeRemaining(VideoFrame& rFrame)
{
  AVPacket packet;
  av_init_packet(&packet);
  packet.data = nullptr;
  packet.size = 0;

  return decodeVideoPacket(packet, rFrame);
}

void gul::VideoLoader::setImageData(gul::VideoFrame& rTargetFrame, const AVFrame* pSourceFrame) const
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
      FAIL("Image conversion failed!");
  }
  else
  {
    memset(pData, 0, pitch*rTargetFrame.GetHeight());
  }
}

void gul::VideoLoader::allocateVideoFrame(VideoFrame& rFrame) const
{
  if(rFrame.GetWidth() != m_pVideoCodecCtx->width ||
     rFrame.GetHeight() != m_pVideoCodecCtx->height ||
     rFrame.GetImageFormat() != gul::Image::IF_RGBA)
  {
    rFrame = gul::VideoFrame(m_pVideoCodecCtx->width, m_pVideoCodecCtx->height, gul::Image::IF_RGBA);
  }
}

bool gul::VideoLoader::IsFrameValid(void) const
{
  return m_isFrameValid;
}

void gul::VideoLoader::GetNext(gul::VideoFrame& rFrame)
{
  ASSERT(m_isVideoOpen);

  allocateVideoFrame(rFrame);
  m_isFrameValid = readNextImage(rFrame);
}

int gul::VideoLoader::GetWidth(void) const
{
  ASSERT(m_isVideoOpen);
  return m_pVideoCodecCtx->width;
}

int gul::VideoLoader::GetHeight(void) const
{
  ASSERT(m_isVideoOpen);
  return m_pVideoCodecCtx->height;
}
