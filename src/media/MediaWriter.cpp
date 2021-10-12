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

#include "MediaWriter.h"
#include "Assert.h"
#include "VideoFrame.h"
#include "MediaReader.h"

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

gul::MediaWriter::MediaWriter(const gul::File& rVideoPath,
                              int width, int height,
                              int fps, int bitrate)
  : m_path(rVideoPath),
    m_pFormatCtx(nullptr),
    m_pVideoCodecCtx(nullptr),
    m_pSWSContext(nullptr),
    m_pVideoStream(nullptr),
    m_pFrame(nullptr),
    m_isClosed(true),
    m_videoWidth(width),
    m_videoHeight(height),
    m_videoFPS(fps),
    m_videoBitrate(bitrate),
    usePTSFromFrames(false)
{
}

gul::MediaWriter::MediaWriter(const gul::File& rVideoPath)
  : m_path(rVideoPath),
    m_pFormatCtx(nullptr),
    m_pVideoCodecCtx(nullptr),
    m_pSWSContext(nullptr),
    m_pVideoStream(nullptr),
    m_pFrame(nullptr),
    m_isClosed(true),
    m_videoWidth(0),
    m_videoHeight(0),
    m_videoFPS(0),
    m_videoBitrate(0),
    usePTSFromFrames(true)
{
}

gul::MediaWriter::~MediaWriter(void)
{
  if(!m_isClosed)
    CloseVideo();
}

void gul::MediaWriter::setSize(int width, int height)
{
  m_videoWidth = width;
  m_videoHeight = height;
}

bool gul::MediaWriter::openVideo(const AVFormatContext& rInputFormatCtx)
{
  GUL_ASSERT(m_isClosed);
  GUL_ASSERT(m_path.IsPathValid());
  GUL_ASSERT(m_videoWidth % 2 == 0);
  GUL_ASSERT(m_videoHeight % 2 == 0);

  /* allocate the output media context */
  avformat_alloc_output_context2(&m_pFormatCtx, nullptr, nullptr, m_path.GetPath().GetData());
  if(m_pFormatCtx == nullptr)
    GUL_FAIL("Format Output Context cannot be allocated!");


  /* create the streams */
  for(unsigned int i = 0; i < rInputFormatCtx.nb_streams; ++i)
  {
    AVStream* pInputStream = rInputFormatCtx.streams[i];
    if(pInputStream->codecpar->codec_type == AVMEDIA_TYPE_VIDEO && m_pVideoStream == nullptr)
    {
      /* find the video encoder */
      GUL_ASSERT_MSG(m_pFormatCtx->oformat->video_codec != AV_CODEC_ID_NONE, "Not a video format!");
      m_pVideoCodec = avcodec_find_encoder(pInputStream->codecpar->codec_id);
      if(m_pVideoCodec == nullptr)
      {
        GUL_FAIL("Codec not found!");
      }

      /* Create new stream and copy settings from input */
      m_pVideoStream = avformat_new_stream(m_pFormatCtx, m_pVideoCodec);
      m_videoBitrate = rInputFormatCtx.bit_rate;

      m_pVideoCodecCtx = avcodec_alloc_context3(m_pVideoCodec);
      if(avcodec_parameters_to_context(m_pVideoCodecCtx, pInputStream->codecpar) < 0)
      {
        GUL_FAIL("Codec Parameters could not be set");
      }
      setDafaultVideoEncoderCtxSettings();
      m_pVideoCodecCtx->time_base = av_inv_q(pInputStream->avg_frame_rate);


      /*
       * NOTE: This if statement is from ffmpeg.c
       *
       * Avi is a special case here because it supports variable fps but
       * having the fps and timebase differe significantly adds quite some
       * overhead
       */
//      if(!strcmp(m_pFormatCtx->oformat->name, "avi"))
//      {
//        m_pVideoCodecCtx->time_base.num = pInputStream->r_frame_rate.den;
//        m_pVideoCodecCtx->time_base.den = pInputStream->r_frame_rate.num;
//        m_pVideoCodecCtx->ticks_per_frame = pInputStream->codec->ticks_per_frame;
//      }
//      avcodec_parameters_copy(m_pVideoStream->codecpar, pInputStream->codecpar);
//      m_pVideoStream->avg_frame_rate = pInputStream->avg_frame_rate;
//      m_pVideoStream->disposition = pInputStream->disposition;
//      m_pVideoStream->time_base = pInputStream->time_base;
//      m_pVideoStream->r_frame_rate = pInputStream->r_frame_rate;
    }
    else
    {
      AVCodec* pCodec = avcodec_find_encoder(pInputStream->codecpar->codec_id);
      AVStream* pStream = avformat_new_stream(m_pFormatCtx, pCodec);
      avcodec_parameters_copy(pStream->codecpar, pInputStream->codecpar);
//      AVCodecContext* pCodecCtx = avcodec_alloc_context3(pCodec);
//      avcodec_get_context_defaults3(pCodecCtx, pCodec);
//      if(avcodec_parameters_to_context(pCodecCtx, pInputStream->codecpar) < 0)
//      {
//        GUL_FAIL("Codec Parameters could not be set");
//      }

//      /*
//       * NOTE: This if statement is from ffmpeg.c
//       */
//      if((pCodecCtx->block_align == 1 ||
//          pCodecCtx->block_align == 1152 ||
//          pCodecCtx->block_align == 576) && pCodecCtx->codec_id == AV_CODEC_ID_MP3)
//        pCodecCtx->block_align = 0;
//      if(pCodecCtx->codec_id == AV_CODEC_ID_AC3)
//        pCodecCtx->block_align = 0;

//      if(!strcmp(m_pFormatCtx->oformat->name, "mp4"))
//        pCodecCtx->codec_tag = 0; // this is neccessary for mp4 copying.
    }
  }

  if(m_pVideoStream == nullptr)
    GUL_FAIL("Video Stream could not be created!");

  /* open the codec */
  int err = avcodec_open2(m_pVideoCodecCtx, m_pVideoCodec, nullptr);
  if(err < 0)
  {
    char a[255];
    av_strerror(err, a, 255);
    GUL_FAIL(a);
  }

  allocateStructures();
  prepareOutputFile();

  m_isClosed = false;

  return true;
}

bool gul::MediaWriter::OpenVideo(void)
{
  GUL_ASSERT(m_isClosed);
  GUL_ASSERT(m_path.IsPathValid());
  GUL_ASSERT(m_videoWidth % 2 == 0);
  GUL_ASSERT(m_videoHeight % 2 == 0);
  GUL_ASSERT(m_videoFPS > 0);

  /* allocate the output media context */
  avformat_alloc_output_context2(&m_pFormatCtx, nullptr, nullptr, m_path.GetPath().GetData());
  if(m_pFormatCtx == nullptr)
    GUL_FAIL("Format Output Context cannot be allocated!");

  /* find the video encoder */
  GUL_ASSERT_MSG(m_pFormatCtx->oformat->video_codec != AV_CODEC_ID_NONE, "Not a video format!");
  m_pVideoCodec = avcodec_find_encoder(m_pFormatCtx->oformat->video_codec);
  if(m_pVideoCodec == nullptr)
    GUL_FAIL("Codec not found!");

  /* create the video stream */
  m_pVideoStream = avformat_new_stream(m_pFormatCtx, m_pVideoCodec);
  if(m_pVideoStream == nullptr)
    GUL_FAIL("Video Stream could not be created!");

  // Get a pointer to the codec context for the video stream
  m_pVideoCodecCtx = avcodec_alloc_context3(m_pVideoCodec);
  setDafaultVideoEncoderCtxSettings();

  /* open the codec */
  if(avcodec_open2(m_pVideoCodecCtx, m_pVideoCodec, nullptr) < 0)
    GUL_FAIL("Could not open codec!");

  allocateStructures();
  prepareOutputFile();

  m_isClosed = false;

  return true;
}

void gul::MediaWriter::setDafaultVideoEncoderCtxSettings(void)
{
  // enable multithreading
  m_pVideoCodecCtx->thread_count = 4;

  // set the settings for the encoder
  m_pVideoCodecCtx->bit_rate = m_videoBitrate;
  m_pVideoCodecCtx->width    = m_videoWidth;
  m_pVideoCodecCtx->height   = m_videoHeight;
  m_pVideoCodecCtx->time_base = (AVRational){ 1, m_videoFPS };
  m_pVideoCodecCtx->gop_size      = 12;
  m_pVideoCodecCtx->pix_fmt       = AV_PIX_FMT_YUV420P;
  if(m_pVideoCodecCtx->codec_id == AV_CODEC_ID_MPEG2VIDEO)
  {
    m_pVideoCodecCtx->max_b_frames = 2;
  }
  if(m_pVideoCodecCtx->codec_id == AV_CODEC_ID_MPEG1VIDEO)
  {
    m_pVideoCodecCtx->mb_decision = FF_MB_DECISION_RD;
  }
  if (m_pFormatCtx->oformat->flags & AVFMT_GLOBALHEADER)
  {
      m_pVideoCodecCtx->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
  }
}

void gul::MediaWriter::allocateStructures(void)
{
  // Allocate packet
  m_pPacket = av_packet_alloc();

  // Allocate video frame
  m_pFrame = av_frame_alloc();
  m_pFrame->pts = 0;
  m_pFrame->width = m_pVideoCodecCtx->width;
  m_pFrame->height = m_pVideoCodecCtx->height;
  m_pFrame->format = m_pVideoCodecCtx->pix_fmt;
  if(av_frame_get_buffer(m_pFrame, 0) < 0)
  {
    GUL_FAIL("AVFrame buffer could not be allocated!");
  }

  // swscaler context
  m_pSWSContext = sws_getCachedContext(m_pSWSContext,
                                       m_pVideoCodecCtx->width, m_pVideoCodecCtx->height, AV_PIX_FMT_RGBA,
                                       m_pVideoCodecCtx->width, m_pVideoCodecCtx->height, m_pVideoCodecCtx->pix_fmt,
                                       SWS_BILINEAR, nullptr, nullptr, nullptr);
}

void gul::MediaWriter::prepareOutputFile(void)
{
  /* open the output file*/
  if(avio_open(&m_pFormatCtx->pb, m_path.GetPath().GetData(), AVIO_FLAG_WRITE) < 0)
    GUL_FAIL("Video file could not be opened");

  /* copy all context setting to the stream */
  m_pVideoStream->time_base = m_pVideoCodecCtx->time_base;
  if(avcodec_parameters_from_context(m_pVideoStream->codecpar, m_pVideoCodecCtx) < 0)
  {
    GUL_FAIL("FFMPEG: Parameters could not be copied into stream");
  }

  /* Write the stream header, if any. */
  int err = avformat_write_header(m_pFormatCtx, nullptr);
  if(err < 0)
  {
    char a[AV_ERROR_MAX_STRING_SIZE];
    av_strerror(err, a, AV_ERROR_MAX_STRING_SIZE);
    GUL_FAIL(a);
  }
}

void gul::MediaWriter::CloseVideo(void)
{
  GUL_ASSERT(!m_isClosed);

  // flush encoder
  encodeAndSaveVideoFrame(nullptr);

  /* Write the trailer, if any. The trailer must be written before you
   * close the CodecContexts open when you wrote the header; otherwise
   * av_write_trailer() may try to use memory that was freed on
   * av_codec_close(). */
  av_write_trailer(m_pFormatCtx);

  avcodec_free_context(&m_pVideoCodecCtx);
  av_frame_free(&m_pFrame);
  av_packet_free(&m_pPacket);

  sws_freeContext(m_pSWSContext);
  m_pSWSContext = nullptr;

  /* Close the output file. */
  //avio_flush(m_pFormatCtx->pb);
  avio_closep(&m_pFormatCtx->pb);

  /* free the stream */
  avformat_free_context(m_pFormatCtx);
  m_pFormatCtx = nullptr;

  m_isClosed = true;
}

void gul::MediaWriter::AddFrame(const gul::VideoFrame& rFrame)
{
  GUL_ASSERT_MSG(rFrame.GetHeight() == m_pVideoCodecCtx->height, "Image height does not match video height!");
  GUL_ASSERT_MSG(rFrame.GetWidth() == m_pVideoCodecCtx->width, "Image width does not match video width!");

  const unsigned char* pData = rFrame.GetData();
  int pitch = rFrame.GetPitch();

  // Convert the image from RGBA to its native format
  //Scale the raw data/convert it to our video buffer...
  av_frame_make_writable(m_pFrame);
  if(sws_scale(m_pSWSContext,
               &pData, &pitch,
               0, m_pVideoCodecCtx->height,
               m_pFrame->data, m_pFrame->linesize) < m_pVideoCodecCtx->height)
    GUL_FAIL("Image conversion failed!");

  if(usePTSFromFrames)
  {
    m_pFrame->pts = rFrame.GetFrameIndex();
    encodeAndSaveVideoFrame(m_pFrame);
  }
  else
  {
    encodeAndSaveVideoFrame(m_pFrame);
    m_pFrame->pts++;
  }
}

void gul::MediaWriter::encodeAndSaveVideoFrame(AVFrame* pFrameToEncode)
{
  if(avcodec_send_frame(m_pVideoCodecCtx, pFrameToEncode) < 0)
  {
    GUL_FAIL("Frame could not be encoded!");
  }

  while(avcodec_receive_packet(m_pVideoCodecCtx, m_pPacket) == 0)
  {
    // compute pts in stream time_base
    //if(m_pPacket->pts != AV_NOPTS_VALUE)
    //  m_pPacket->pts = av_rescale_q(m_pPacket->pts, m_pVideoCodecCtx->time_base, m_pVideoStream->time_base);
//    if(m_pPacket->dts != AV_NOPTS_VALUE)
//      m_pPacket->dts = av_rescale_q(m_pPacket->dts, m_pVideoCodecCtx->time_base, m_pVideoStream->time_base);

    av_packet_rescale_ts(m_pPacket, m_pVideoCodecCtx->time_base, m_pVideoStream->time_base);
    m_pPacket->stream_index = m_pVideoStream->index;

    writePacket(*m_pPacket);
  }
}

void gul::MediaWriter::writePacket(AVPacket& pPacket)
{
  /* Write the compressed frame to the media file. */
  int ret = av_interleaved_write_frame(m_pFormatCtx, &pPacket);
  if(ret < 0)
  {
    char error[AV_ERROR_MAX_STRING_SIZE];
    av_make_error_string(error, AV_ERROR_MAX_STRING_SIZE, ret);
    GUL_LOG_ERROR(error);
    GUL_FAIL("Encoded packet could not be written!");
  }

  av_packet_unref(m_pPacket);
}
