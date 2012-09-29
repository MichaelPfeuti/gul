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

#include "VideoLoader.h"
#include "Assert.h"

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

bool gul::VideoLoader::codecsAreRegistered = false;

gul::VideoLoader::VideoLoader(const gul::File& videoPath)
  : path(videoPath),
    pFormatCtx(nullptr),
    pCodecCtx(nullptr),
    pSWSContext(nullptr),
    pCodec(nullptr),
    pFrame(nullptr),
    pFrameRGBA(nullptr),
    pDataBufferRGBA(nullptr),
    isFrameValid(false)
{
  if(!codecsAreRegistered)
  {
    av_register_all();
    codecsAreRegistered = true;
  }
}


gul::VideoLoader::~VideoLoader(void)
{
  // Free RGBA memory
  av_free(pDataBufferRGBA);
  av_free(pFrameRGBA);

  // Free the frame buffer
  av_free(pFrame);

  // free swscale context
  av_free(pSWSContext);

  // Close the codec
  avcodec_close(pCodecCtx);

  // Close the video file
  avformat_close_input(&pFormatCtx);
}

bool gul::VideoLoader::OpenVideo(void)
{
  ASSERT(path.IsPathValid());

  // Open video file
  if(avformat_open_input(&pFormatCtx, path.GetPath().GetData(), nullptr, nullptr) != 0)
    FAIL("Couldn't open file");

  // Retrieve stream information
  if(avformat_find_stream_info(pFormatCtx, nullptr) < 0)
    FAIL("Couldn't find stream information");

  //av_dump_format(pFormatCtx, 0, path.GetData(), 0);

  // Find the best video stream
  videoStreamIndex =  av_find_best_stream(pFormatCtx, AVMEDIA_TYPE_VIDEO, -1, -1, &pCodec, 0);
  if(videoStreamIndex == AVERROR_STREAM_NOT_FOUND)
    FAIL("Didn't find a video stream");

  // Get a pointer to the codec context for the video stream
  pCodecCtx = pFormatCtx->streams[videoStreamIndex]->codec;

  // enable multithreading
  pCodecCtx->thread_count = 2;

  // Find the decoder for the video stream
  pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
  if(pCodec == nullptr)
    FAIL("Unsupported codec!\n");

  // Open codec
  if(avcodec_open2(pCodecCtx, pCodec, nullptr) < 0)
    FAIL("Could not open codec");

  // Allocate video frame
  pFrame = avcodec_alloc_frame();

  // Allocate an AVFrame structure
  pFrameRGBA = avcodec_alloc_frame();

  // Determine required buffer size and allocate buffer
  int numBytes;
  numBytes = avpicture_get_size(PIX_FMT_RGBA, pCodecCtx->width,
                                pCodecCtx->height);
  pDataBufferRGBA = (uint8_t*)av_malloc(numBytes * sizeof(uint8_t));

  // Assign appropriate parts of buffer to image planes in pFrameRGB
  // Note that pFrameRGBA is an AVFrame, but AVFrame is a superset
  // of AVPicture
  avpicture_fill((AVPicture*)pFrameRGBA, pDataBufferRGBA, PIX_FMT_RGBA,
                 pCodecCtx->width, pCodecCtx->height);


  // swscaler context
  pSWSContext = sws_getCachedContext(pSWSContext,
                                     pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,
                                     pCodecCtx->width, pCodecCtx->height, PIX_FMT_RGBA,
                                     SWS_BILINEAR, nullptr, nullptr, nullptr);

  return true;
}

bool gul::VideoLoader::readNextImage(gul::Image& image)
{
  // Read packets and generate frames
  int frameFinished;
  AVPacket packet;
  av_init_packet(&packet);
  while(av_read_frame(pFormatCtx, &packet) >= 0)
  {
    // Is this a packet from the video stream?
    if(packet.stream_index == videoStreamIndex)
    {
      // Decode video frame
      if(avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet) < 0)
        FAIL("Decoding failed!");

      // Did we get a video frame?
      if(frameFinished)
      {
        // Convert the image from its native format to RGB
        //Scale the raw data/convert it to our video buffer...
        if(sws_scale(pSWSContext,
                     pFrame->data, pFrame->linesize,
                     0, pCodecCtx->height,
                     pFrameRGBA->data, pFrameRGBA->linesize) <  pCodecCtx->height)
          FAIL("Image conversion failed!");

        setCurrentImage(image, pFrameRGBA);
        av_free_packet(&packet);

        return true;
      }
    }
    av_free_packet(&packet);
  }

  av_free_packet(&packet);

  if(decodeRemaining(image))
    return true;

  setCurrentImage(image, nullptr);
  return false;
}

bool gul::VideoLoader::decodeRemaining(gul::Image& image)
{
  int frameFinished = 0;
  AVPacket packet;
  av_init_packet(&packet);
  packet.data = nullptr;
  packet.size = 0;
  if(avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet) < 0)
    FAIL("Decoding failed!");

  // Did we get a video frame?
  if(frameFinished)
  {
    // Convert the image from its native format to RGB
    //Scale the raw data/convert it to our video buffer...
    if(sws_scale(pSWSContext,
                 pFrame->data, pFrame->linesize,
                 0, pCodecCtx->height,
                 pFrameRGBA->data, pFrameRGBA->linesize) <  pCodecCtx->height)
      FAIL("Image conversion failed!");

    setCurrentImage(image, pFrameRGBA);
    av_free_packet(&packet);
    return true;
  }
  av_free_packet(&packet);
  return false;
}

void gul::VideoLoader::setCurrentImage(gul::Image& image, const AVFrame* frame)
{
  const int channels = image.GetNumberOfChannels();
  const int width = image.GetWidth();
  for(int y = 0; y < image.GetHeight(); ++y)
  {
    for(int x = 0; x < width; ++x)
    {
      gul::RGBA rgba;
      if(frame != nullptr)
      {
         rgba = gul::RGBA(frame->data[0][ (x + y*width)*channels + 0],
                          frame->data[0][ (x + y*width)*channels + 1],
                          frame->data[0][ (x + y*width)*channels + 2],
                          frame->data[0][ (x + y*width)*channels + 3]);
      }
      image.SetPixel(x, y, rgba);
    }
  }
}

bool gul::VideoLoader::IsFrameValid(void) const
{
  return isFrameValid;
}

void gul::VideoLoader::GetNext(gul::Image& image)
{
  if(image.GetWidth() != pCodecCtx->width ||
     image.GetHeight() != pCodecCtx->height ||
     image.GetImageType() != gul::Image::IT_RGBA)
  {
    image = gul::Image(pCodecCtx->width, pCodecCtx->height, gul::Image::IT_RGBA);
  }
  isFrameValid = readNextImage(image);
}

gul::VideoSettings gul::VideoLoader::GetSettings(void) const
{
  return gul::VideoSettings(pCodecCtx->width, pCodecCtx->height,
                            pFormatCtx->bit_rate,
                            pFormatCtx->streams[videoStreamIndex]->time_base.num,
                            pFormatCtx->streams[videoStreamIndex]->time_base.den,
                            pCodecCtx->gop_size);
}
