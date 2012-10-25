/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011-2012 Michael Pfeuti.
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
  : path(rVideoPath),
    pFormatCtx(nullptr),
    pVideoCodecCtx(nullptr),
    pSWSContext(nullptr),
    pPacket(nullptr),
    pFrame(nullptr),
    pFrameRGBA(nullptr),
    pDataBufferRGBA(nullptr),
    isFrameValid(false),
    isVideoOpen(false),
    isPacketDataFreed(true)
{
  if(!codecsAreRegistered)
  {
    av_register_all();
    codecsAreRegistered = true;
  }
}


gul::VideoLoader::~VideoLoader(void)
{
  if(isVideoOpen)
  {
    CloseVideo();
  }
}

void gul::VideoLoader::CloseVideo(void)
{
  // Free RGBA memory
  av_free(pDataBufferRGBA);
  av_free(pFrameRGBA);
  pDataBufferRGBA = nullptr;
  pFrameRGBA = nullptr;

  // Free the frame buffer
  av_free(pFrame);
  pFrame = nullptr;

  // free swscale context
  av_free(pSWSContext);
  pSWSContext = nullptr;

  // free packet
  if(!isPacketDataFreed)
    av_free_packet(pPacket);
  GUL_DELETE(pPacket);

  // Close the codec
  avcodec_close(pVideoCodecCtx);
  pVideoCodecCtx = nullptr;

  // Close the video file
  avformat_close_input(&pFormatCtx);
  pFormatCtx = nullptr;

  isFrameValid = false;
  isVideoOpen = false;
  isPacketDataFreed = true;
}

bool gul::VideoLoader::OpenVideo(void)
{
  ASSERT(!isVideoOpen);
  ASSERT(path.IsPathValid());

  // Open video file
  if(avformat_open_input(&pFormatCtx, path.GetPath().GetData(), nullptr, nullptr) != 0)
    FAIL("Couldn't open file");

  // Retrieve stream information
  if(avformat_find_stream_info(pFormatCtx, nullptr) < 0)
    FAIL("Couldn't find stream information");

  //av_dump_format(pFormatCtx, 0, path.GetData(), 0);

  // Find the best video stream
  videoStreamIndex =  av_find_best_stream(pFormatCtx, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
  if(videoStreamIndex == AVERROR_STREAM_NOT_FOUND)
    FAIL("Didn't find a video stream");

  // Get a pointer to the codec context for the video stream
  pVideoCodecCtx = pFormatCtx->streams[videoStreamIndex]->codec;

  // enable multithreading
  pVideoCodecCtx->thread_count = 2;

  // Find the decoder for the video stream
  AVCodec* pCodec = avcodec_find_decoder(pVideoCodecCtx->codec_id);
  if(pCodec == nullptr)
    FAIL("Unsupported codec!\n");

  // Open codec
  if(avcodec_open2(pVideoCodecCtx, pCodec, nullptr) < 0)
    FAIL("Could not open codec");

  // Allocate video frame
  pFrame = avcodec_alloc_frame();

  // Allocate an AVFrame structure
  pFrameRGBA = avcodec_alloc_frame();

  // Determine required buffer size and allocate buffer
  int numBytes;
  numBytes = avpicture_get_size(PIX_FMT_RGBA, pVideoCodecCtx->width,
                                pVideoCodecCtx->height);
  pDataBufferRGBA = (uint8_t*)av_malloc(numBytes * sizeof(uint8_t));

  // Assign appropriate parts of buffer to image planes in pFrameRGB
  // Note that pFrameRGBA is an AVFrame, but AVFrame is a superset
  // of AVPicture
  avpicture_fill((AVPicture*)pFrameRGBA, pDataBufferRGBA, PIX_FMT_RGBA,
                 pVideoCodecCtx->width, pVideoCodecCtx->height);


  // swscaler context
  pSWSContext = sws_getCachedContext(pSWSContext,
                                     pVideoCodecCtx->width, pVideoCodecCtx->height, pVideoCodecCtx->pix_fmt,
                                     pVideoCodecCtx->width, pVideoCodecCtx->height, PIX_FMT_RGBA,
                                     SWS_BILINEAR, nullptr, nullptr, nullptr);

  // packet into which to read piece
  pPacket = new AVPacket;
  av_init_packet(pPacket);
  isPacketDataFreed = true;

  isVideoOpen = true;
  return true;
}

bool gul::VideoLoader::readNextImage(gul::VideoFrame &rFrame)
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
  if(!isPacketDataFreed)
  {
    av_free_packet(pPacket);
    av_init_packet(pPacket);
  }

  if(av_read_frame(pFormatCtx, pPacket) < 0)
    return nullptr;

  isPacketDataFreed = false;
  return pPacket;
}

bool gul::VideoLoader::decodeVideoPacket(AVPacket& rPacket, gul::VideoFrame &rFrame)
{
  int frameFinished;
  // Decode video frame
  if(avcodec_decode_video2(pVideoCodecCtx, pFrame, &frameFinished, &rPacket) < 0)
    FAIL("Decoding failed!");

  // Did we get a video frame?
  if(frameFinished)
  {
    // Convert the image from its native format to RGB
    //Scale the raw data/convert it to our video buffer...
    if(sws_scale(pSWSContext,
                 pFrame->data, pFrame->linesize,
                 0, pVideoCodecCtx->height,
                 pFrameRGBA->data, pFrameRGBA->linesize) <  pVideoCodecCtx->height)
      FAIL("Image conversion failed!");

    setImageData(rFrame, pFrameRGBA);
    //uint64_t pts = av_rescale_q(pFrame->pkt_pts, pFormatCtx->streams[videoStreamIndex]->time_base, pVideoCodecCtx->time_base);
    rFrame.SetPresentationTime(pFrame->pkt_pts);
  }

  return frameFinished;
}

bool gul::VideoLoader::isVideoPacket(const AVPacket& rPacket) const
{
  return rPacket.stream_index == videoStreamIndex;
}

bool gul::VideoLoader::decodeRemaining(VideoFrame &rFrame)
{
  AVPacket packet;
  av_init_packet(&packet);
  packet.data = nullptr;
  packet.size = 0;

  return decodeVideoPacket(packet, rFrame);
}

void gul::VideoLoader::setImageData(gul::VideoFrame &rTargetFrame, const AVFrame* pSourceFrame) const
{
  const int channels = rTargetFrame.GetNumberOfChannels();
  const int width = rTargetFrame.GetWidth();
  for(int y = 0; y < rTargetFrame.GetHeight(); ++y)
  {
    for(int x = 0; x < width; ++x)
    {
      gul::RGBA rgba;
      if(pSourceFrame != nullptr)
      {
        rgba = gul::RGBA(pSourceFrame->data[0][(x + y * width) * channels + 0],
                         pSourceFrame->data[0][(x + y * width) * channels + 1],
                         pSourceFrame->data[0][(x + y * width) * channels + 2],
                         pSourceFrame->data[0][(x + y * width) * channels + 3]);
      }
      rTargetFrame.SetPixel(x, y, rgba);
    }
  }
}

void gul::VideoLoader::allocateVideoFrame(VideoFrame &rFrame) const
{
  if(rFrame.GetWidth() != pVideoCodecCtx->width ||
     rFrame.GetHeight() != pVideoCodecCtx->height ||
     rFrame.GetImageType() != gul::Image::IT_RGBA)
  {
    rFrame = gul::VideoFrame(pVideoCodecCtx->width, pVideoCodecCtx->height, gul::Image::IT_RGBA);
  }
}

bool gul::VideoLoader::IsFrameValid(void) const
{
  return isFrameValid;
}

void gul::VideoLoader::GetNext(gul::VideoFrame &rFrame)
{
  ASSERT(isVideoOpen);

  allocateVideoFrame(rFrame);
  isFrameValid = readNextImage(rFrame);
}

int gul::VideoLoader::GetWidth(void) const
{
  ASSERT(isVideoOpen);
  return pVideoCodecCtx->width;
}

int gul::VideoLoader::GetHeight(void) const
{
  ASSERT(isVideoOpen);
  return pVideoCodecCtx->height;
}
