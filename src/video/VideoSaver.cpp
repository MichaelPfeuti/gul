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

#include "VideoSaver.h"
#include "Assert.h"
#include "Image.h"

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

bool gul::VideoSaver::codecsAreRegistered = false;

gul::VideoSaver::VideoSaver(const gul::File& videoPath,
                            int width, int height,
                            int fps, int bitrate)
  : path(videoPath),
    pFormatCtx(nullptr),
    pCodecCtx(nullptr),
    pSWSContext(nullptr),
    pVideoStream(nullptr),
    pVideoCodec(nullptr),
    pFrame(nullptr),
    pFrameRGBA(nullptr),
    isClosed(true),
    videoWidth(width),
    videoHeight(height),
    videoFPS(fps),
    videoBitrate(bitrate)
{
  if(!codecsAreRegistered)
  {
    av_register_all();
    codecsAreRegistered = true;
  }
}

bool gul::VideoSaver::OpenVideo(void)
{
  ASSERT(isClosed);
  ASSERT(path.IsPathValid());
  ASSERT(videoWidth % 2 == 0);
  ASSERT(videoHeight % 2 == 0);
  ASSERT(videoFPS > 0);

  isClosed = false;

  /* allocate the output media context */
  avformat_alloc_output_context2(&pFormatCtx, nullptr, nullptr, path.GetPath().GetData());
  if(pFormatCtx == nullptr)
    FAIL("Format Output Context cannot be allocated!");

  /* find the video encoder */
  ASSERT_MSG(pFormatCtx->oformat->video_codec != CODEC_ID_NONE, "Not a video format!");
  pVideoCodec = avcodec_find_encoder(pFormatCtx->oformat->video_codec);
  if(pVideoCodec == nullptr)
    FAIL("Codec not found!");

  /* create the video stream */
  pVideoStream = avformat_new_stream(pFormatCtx, pVideoCodec);
  if(pVideoStream == nullptr)
    FAIL("Video Stream could not be created!");

  // Get a pointer to the codec context for the video stream
  pCodecCtx = pVideoStream->codec;

  // enable multithreading
  pCodecCtx->thread_count = 2;

  /* initialize codec settings */
  avcodec_get_context_defaults3(pCodecCtx, pVideoCodec);
  pCodecCtx->codec_id = pFormatCtx->oformat->video_codec;
  pCodecCtx->bit_rate = videoBitrate;
  pCodecCtx->bit_rate_tolerance = 0;
  pCodecCtx->width    = videoWidth;
  pCodecCtx->height   = videoHeight;
  pCodecCtx->time_base.num = 1;
  pCodecCtx->time_base.den = videoFPS;
  pCodecCtx->gop_size      = 12;
  pCodecCtx->pix_fmt       = PIX_FMT_YUV420P;
  if(pCodecCtx->codec_id == CODEC_ID_MPEG2VIDEO)
    pCodecCtx->max_b_frames = 2;
  if(pCodecCtx->codec_id == CODEC_ID_MPEG1VIDEO)
    pCodecCtx->mb_decision = 2;
  if(pFormatCtx->oformat->flags & AVFMT_GLOBALHEADER)
    pCodecCtx->flags |= CODEC_FLAG_GLOBAL_HEADER;

  /* open the codec */
  if(avcodec_open2(pCodecCtx, pVideoCodec, nullptr) < 0)
    FAIL("Could not open codec!");

  // Allocate video frame
  pFrame = avcodec_alloc_frame();
  pFrame->pts = 0;
  avpicture_alloc((AVPicture*)pFrame, pCodecCtx->pix_fmt,
                  pCodecCtx->width, pCodecCtx->height);

  // Allocate an AVFrame structure
  pFrameRGBA = avcodec_alloc_frame();
  avpicture_alloc((AVPicture*)pFrameRGBA, PIX_FMT_RGBA,
                  pCodecCtx->width, pCodecCtx->height);

  /* open the output file*/
  if(avio_open(&pFormatCtx->pb, path.GetPath().GetData(), AVIO_FLAG_WRITE) < 0)
    FAIL("Video file could not be opened");

  /* Write the stream header, if any. */
  if(avformat_write_header(pFormatCtx, nullptr) < 0)
  {
    FAIL("Error occurred when opening output file!");
  }

  // swscaler context
  pSWSContext = sws_getCachedContext(pSWSContext,
                                     pCodecCtx->width, pCodecCtx->height, PIX_FMT_RGBA,
                                     pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,
                                     SWS_BILINEAR, nullptr, nullptr, nullptr);

  return true;
}

gul::VideoSaver::~VideoSaver(void)
{
  if(!isClosed)
    CloseVideo();
}

void gul::VideoSaver::CloseVideo(void)
{
  ASSERT(!isClosed);

  // flush encoder
  while(encodeAndSave(nullptr));


  /* Write the trailer, if any. The trailer must be written before you
   * close the CodecContexts open when you wrote the header; otherwise
   * av_write_trailer() may try to use memory that was freed on
   * av_codec_close(). */
  av_write_trailer(pFormatCtx);

  // Free RGBA memory
  avpicture_free((AVPicture*)pFrameRGBA);
  av_free(pFrameRGBA);

  // Free the frame buffer
  avpicture_free((AVPicture*)pFrame);
  av_free(pFrame);

  // free swscale context
  sws_freeContext(pSWSContext);

  // Close the codec
  avcodec_close(pCodecCtx);

  /* Free the streams. */
//  for (unsigned int i = 0; i < pFormatCtx->nb_streams; i++) {
//     av_freep(&pFormatCtx->streams[i]->codec);
//      av_freep(&pFormatCtx->streams[i]);
//  }

  /* Close the output file. */
  avio_flush(pFormatCtx->pb);
  avio_close(pFormatCtx->pb);

  /* free the stream */
  avformat_free_context(pFormatCtx);

  isClosed = true;
}

void gul::VideoSaver::fillFrameRGBA(const gul::Image& image)
{
  const int channels = image.GetNumberOfChannels();
  const int width = image.GetWidth();
  for(int y = 0; y < image.GetHeight(); ++y)
  {
    for(int x = 0; x < width; ++x)
    {
      gul::RGBA rgba = image.GetPixel(x, y);
      pFrameRGBA->data[0][(x + y * width)*channels + 0] = rgba.GetRed() * 255;
      pFrameRGBA->data[0][(x + y * width)*channels + 1] = rgba.GetGreen() * 255;
      pFrameRGBA->data[0][(x + y * width)*channels + 2] = rgba.GetBlue() * 255;
      pFrameRGBA->data[0][(x + y * width)*channels + 3] = rgba.GetAlpha() * 255;
    }
  }
}

void gul::VideoSaver::AddImage(const gul::Image& image)
{
  ASSERT_MSG(image.GetHeight() == pCodecCtx->height, "Image height does not match video height!");
  ASSERT_MSG(image.GetWidth() == pCodecCtx->width, "Image width does not match video width!");

  fillFrameRGBA(image);
  // Convert the image from RGBA to its native format
  //Scale the raw data/convert it to our video buffer...
  if(sws_scale(pSWSContext,
               pFrameRGBA->data, pFrameRGBA->linesize,
               0, pCodecCtx->height,
               pFrame->data, pFrame->linesize) < pCodecCtx->height)
    FAIL("Image conversion failed!");

  encodeAndSave(pFrame);
  pFrame->pts++;
}

bool gul::VideoSaver::encodeAndSave(AVFrame* pFrameToEncode)
{
  /* encode the image */
  AVPacket pkt;

  av_init_packet(&pkt);
  pkt.data = nullptr;    // packet data will be allocated by the encoder
  pkt.size = 0;
  pkt.stream_index = pVideoStream->index;

  int gotPacket;
  if(avcodec_encode_video2(pCodecCtx, &pkt, pFrameToEncode, &gotPacket) < 0)
    FAIL("Frame could not be encoded!");

  if(pkt.pts != AV_NOPTS_VALUE)
    pkt.pts = av_rescale_q(pkt.pts , pCodecCtx->time_base, pVideoStream->time_base);

  if(gotPacket)
  {
    /* Write the compressed frame to the media file. */
    if(av_write_frame(pFormatCtx, &pkt) < 0)
      FAIL("Encoded packet could not be written!");

    av_free_packet(&pkt);
  }

  // was something written
  return gotPacket;
}
