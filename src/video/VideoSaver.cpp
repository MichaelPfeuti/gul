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

#include "VideoSaver.h"
#include "Assert.h"
#include "VideoFrame.h"
#include "VideoLoader.h"

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

bool gul::VideoSaver::codecsAreRegistered = false;

gul::VideoSaver::VideoSaver(const gul::File& rVideoPath,
                            int width, int height,
                            int fps, int bitrate)
  : path(rVideoPath),
    pFormatCtx(nullptr),
    pVideoCodecCtx(nullptr),
    pSWSContext(nullptr),
    pVideoStream(nullptr),
    pFrame(nullptr),
    pFrameRGBA(nullptr),
    isClosed(true),
    videoWidth(width),
    videoHeight(height),
    videoFPS(fps),
    videoBitrate(bitrate),
    usePTSFromFrames(false)
{
  if(!codecsAreRegistered)
  {
    av_register_all();
    codecsAreRegistered = true;
  }
}

gul::VideoSaver::VideoSaver(const gul::File& rVideoPath)
  : path(rVideoPath),
    pFormatCtx(nullptr),
    pVideoCodecCtx(nullptr),
    pSWSContext(nullptr),
    pVideoStream(nullptr),
    pFrame(nullptr),
    pFrameRGBA(nullptr),
    isClosed(true),
    videoWidth(0),
    videoHeight(0),
    videoFPS(0),
    videoBitrate(0),
    usePTSFromFrames(true)
{
  if(!codecsAreRegistered)
  {
    av_register_all();
    codecsAreRegistered = true;
  }
}

gul::VideoSaver::~VideoSaver(void)
{
  if(!isClosed)
    CloseVideo();
}

void gul::VideoSaver::setSize(int width, int height)
{
  videoWidth = width;
  videoHeight = height;
}

bool gul::VideoSaver::openVideo(const AVFormatContext& rInputFormatCtx)
{
  ASSERT(isClosed);
  ASSERT(path.IsPathValid());
  ASSERT(videoWidth % 2 == 0);
  ASSERT(videoHeight % 2 == 0);

  /* allocate the output media context */
  avformat_alloc_output_context2(&pFormatCtx, nullptr, nullptr, path.GetPath().GetData());
  if(pFormatCtx == nullptr)
    FAIL("Format Output Context cannot be allocated!");

  /* find the video encoder */
  ASSERT_MSG(pFormatCtx->oformat->video_codec != CODEC_ID_NONE, "Not a video format!");
  pVideoCodec = avcodec_find_encoder(pFormatCtx->oformat->video_codec);
  if(pVideoCodec == nullptr)
    FAIL("Codec not found!");

  /* create the streams */
  for(unsigned int i = 0; i < rInputFormatCtx.nb_streams; ++i)
  {
    AVStream* pInputStream = rInputFormatCtx.streams[i];
    if(pInputStream->codec->codec_type == AVMEDIA_TYPE_VIDEO && pVideoStream == nullptr)
    {
      pVideoStream = avformat_new_stream(pFormatCtx, pVideoCodec);
      copyVideoEncoderCtxSettings(*pInputStream->codec);
    }
    else
    {
      AVCodec* pCodec = avcodec_find_decoder(pInputStream->codec->codec_id);
      AVStream* pStream = avformat_new_stream(pFormatCtx, pCodec);
      AVCodecContext* pCodecCtx = pStream->codec;
      avcodec_copy_context(pCodecCtx, pInputStream->codec);
      if(pFormatCtx->oformat->flags & AVFMT_GLOBALHEADER)
        pCodecCtx->flags |= CODEC_FLAG_GLOBAL_HEADER;
    }
  }

  if(pVideoStream == nullptr)
    FAIL("Video Stream could not be created!");

  /* open the codec */
  if(avcodec_open2(pVideoCodecCtx, pVideoCodec, nullptr) < 0)
    FAIL("Could not open codec!");

  allocateStructures();
  prepareOutputFile();

  isClosed = false;

  return true;
}

bool gul::VideoSaver::OpenVideo(void)
{
  ASSERT(isClosed);
  ASSERT(path.IsPathValid());
  ASSERT(videoWidth % 2 == 0);
  ASSERT(videoHeight % 2 == 0);
  ASSERT(videoFPS > 0);


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

  setDafaultVideoEncoderCtxSettings();

  /* open the codec */
  if(avcodec_open2(pVideoCodecCtx, pVideoCodec, nullptr) < 0)
    FAIL("Could not open codec!");

  allocateStructures();
  prepareOutputFile();

  isClosed = false;

  return true;
}

void gul::VideoSaver::copyVideoEncoderCtxSettings(const AVCodecContext& ctx)
{
  // Get a pointer to the codec context for the video stream
  pVideoCodecCtx = pVideoStream->codec;

  // enable multithreading
  pVideoCodecCtx->thread_count = 2;

  // bitrate modifier
  float bitrateModifier = (videoWidth * videoHeight) / static_cast<float>(ctx.width * ctx.height);

  /* initialize codec settings */
  avcodec_get_context_defaults3(pVideoCodecCtx, pVideoCodec);
  pVideoCodecCtx->codec_id = pFormatCtx->oformat->video_codec;
  pVideoCodecCtx->bit_rate = ctx.bit_rate * bitrateModifier;
  pVideoCodecCtx->bit_rate_tolerance = 0;
  pVideoCodecCtx->width    = videoWidth;
  pVideoCodecCtx->height   = videoHeight;
  pVideoCodecCtx->time_base = ctx.time_base;
  pVideoCodecCtx->time_base.num *= ctx.ticks_per_frame;
  pVideoCodecCtx->gop_size      = 12;
  pVideoCodecCtx->pix_fmt       = ctx.pix_fmt;
  pVideoCodecCtx->profile = ctx.profile;
  pVideoCodecCtx->level = FF_LEVEL_UNKNOWN;//ctx.level;
  if(pVideoCodecCtx->codec_id == CODEC_ID_MPEG2VIDEO)
    pVideoCodecCtx->max_b_frames = 2;
  if(pVideoCodecCtx->codec_id == CODEC_ID_MPEG1VIDEO)
    pVideoCodecCtx->mb_decision = FF_MB_DECISION_RD;
  if(pFormatCtx->oformat->flags & AVFMT_GLOBALHEADER)
    pVideoCodecCtx->flags |= CODEC_FLAG_GLOBAL_HEADER;
}

void gul::VideoSaver::setDafaultVideoEncoderCtxSettings(void)
{
  // Get a pointer to the codec context for the video stream
  pVideoCodecCtx = pVideoStream->codec;

  // enable multithreading
  pVideoCodecCtx->thread_count = 2;

  /* initialize codec settings */
  avcodec_get_context_defaults3(pVideoCodecCtx, pVideoCodec);
  pVideoCodecCtx->codec_id = pFormatCtx->oformat->video_codec;
  pVideoCodecCtx->bit_rate = videoBitrate;
  pVideoCodecCtx->bit_rate_tolerance = 0;
  pVideoCodecCtx->width    = videoWidth;
  pVideoCodecCtx->height   = videoHeight;
  pVideoCodecCtx->time_base.num = 1;
  pVideoCodecCtx->time_base.den = videoFPS;
  pVideoCodecCtx->gop_size      = 12;
  pVideoCodecCtx->pix_fmt       = PIX_FMT_YUV420P;
  if(pVideoCodecCtx->codec_id == CODEC_ID_MPEG2VIDEO)
    pVideoCodecCtx->max_b_frames = 2;
  if(pVideoCodecCtx->codec_id == CODEC_ID_MPEG1VIDEO)
    pVideoCodecCtx->mb_decision = FF_MB_DECISION_RD;
  if(pFormatCtx->oformat->flags & AVFMT_GLOBALHEADER)
    pVideoCodecCtx->flags |= CODEC_FLAG_GLOBAL_HEADER;
}

void gul::VideoSaver::allocateStructures(void)
{
  // Allocate video frame
  pFrame = avcodec_alloc_frame();
  pFrame->pts = 0;
  avpicture_alloc((AVPicture*)pFrame, pVideoCodecCtx->pix_fmt,
                  pVideoCodecCtx->width, pVideoCodecCtx->height);

  // Allocate an AVFrame structure
  pFrameRGBA = avcodec_alloc_frame();
  avpicture_alloc((AVPicture*)pFrameRGBA, PIX_FMT_RGBA,
                  pVideoCodecCtx->width, pVideoCodecCtx->height);

  // swscaler context
  pSWSContext = sws_getCachedContext(pSWSContext,
                                     pVideoCodecCtx->width, pVideoCodecCtx->height, PIX_FMT_RGBA,
                                     pVideoCodecCtx->width, pVideoCodecCtx->height, pVideoCodecCtx->pix_fmt,
                                     SWS_BILINEAR, nullptr, nullptr, nullptr);
}

void gul::VideoSaver::prepareOutputFile(void)
{
  /* open the output file*/
  if(avio_open(&pFormatCtx->pb, path.GetPath().GetData(), AVIO_FLAG_WRITE) < 0)
    FAIL("Video file could not be opened");

  /* Write the stream header, if any. */
  if(avformat_write_header(pFormatCtx, nullptr) < 0)
  {
    FAIL("Error occurred when opening output file!");
  }
}

void gul::VideoSaver::CloseVideo(void)
{
  ASSERT(!isClosed);

  // flush encoder
  while(encodeAndSaveVideoFrame(nullptr));


  /* Write the trailer, if any. The trailer must be written before you
   * close the CodecContexts open when you wrote the header; otherwise
   * av_write_trailer() may try to use memory that was freed on
   * av_codec_close(). */
  av_write_trailer(pFormatCtx);

  // Free RGBA memory
  avpicture_free((AVPicture*)pFrameRGBA);
  av_free(pFrameRGBA);
  pFrameRGBA = nullptr;

  // Free the frame buffer
  avpicture_free((AVPicture*)pFrame);
  av_free(pFrame);
  pFrame = nullptr;

  // free swscale context
  sws_freeContext(pSWSContext);
  pSWSContext = nullptr;

  // Close the codec
  avcodec_close(pVideoCodecCtx);
  pVideoCodecCtx = nullptr;

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
  pFormatCtx = nullptr;

  isClosed = true;
}

void gul::VideoSaver::fillFrameRGBA(const gul::VideoFrame& rFrame)
{
  const int channels = rFrame.GetNumberOfChannels();
  const int width = rFrame.GetWidth();
  for(int y = 0; y < rFrame.GetHeight(); ++y)
  {
    for(int x = 0; x < width; ++x)
    {
      gul::RGBA rgba = rFrame.GetPixel(x, y);
      pFrameRGBA->data[0][(x + y * width)*channels + 0] = rgba.GetRed() * 255;
      pFrameRGBA->data[0][(x + y * width)*channels + 1] = rgba.GetGreen() * 255;
      pFrameRGBA->data[0][(x + y * width)*channels + 2] = rgba.GetBlue() * 255;
      pFrameRGBA->data[0][(x + y * width)*channels + 3] = rgba.GetAlpha() * 255;
    }
  }
}

void gul::VideoSaver::AddFrame(const gul::VideoFrame& rFrame)
{
  ASSERT_MSG(rFrame.GetHeight() == pVideoCodecCtx->height, "Image height does not match video height!");
  ASSERT_MSG(rFrame.GetWidth() == pVideoCodecCtx->width, "Image width does not match video width!");

  fillFrameRGBA(rFrame);
  // Convert the image from RGBA to its native format
  //Scale the raw data/convert it to our video buffer...
  if(sws_scale(pSWSContext,
               pFrameRGBA->data, pFrameRGBA->linesize,
               0, pVideoCodecCtx->height,
               pFrame->data, pFrame->linesize) < pVideoCodecCtx->height)
    FAIL("Image conversion failed!");

  if(usePTSFromFrames)
  {
    pFrame->pts = rFrame.GetPresentationTime();
    encodeAndSaveVideoFrame(pFrame);
  }
  else
  {
    encodeAndSaveVideoFrame(pFrame);
    pFrame->pts++;
  }
}

bool gul::VideoSaver::encodeAndSaveVideoFrame(AVFrame* pFrameToEncode)
{
  /* encode the image */
  AVPacket pkt;

  av_init_packet(&pkt);
  pkt.data = nullptr;    // packet data will be allocated by the encoder
  pkt.size = 0;
  pkt.stream_index = pVideoStream->index;
  pkt.flags |= AV_PKT_FLAG_KEY;

  int gotPacket;
  if(avcodec_encode_video2(pVideoCodecCtx, &pkt, pFrameToEncode, &gotPacket) < 0)
    FAIL("Frame could not be encoded!");

  if(gotPacket)
  {
    // compute pts in stream time_base
    if(pkt.pts != AV_NOPTS_VALUE && !usePTSFromFrames)
      pkt.pts = av_rescale_q(pkt.pts , pVideoCodecCtx->time_base, pVideoStream->time_base);

    /* Write the compressed frame to the media file. */
    if(!writePacket(pkt))
      FAIL("Encoded packet could not be written!");

    av_free_packet(&pkt);
  }

  // was something written
  return gotPacket;
}

bool gul::VideoSaver::writePacket(AVPacket& rPacket)
{
  return av_interleaved_write_frame(pFormatCtx, &rPacket) >= 0;
}
