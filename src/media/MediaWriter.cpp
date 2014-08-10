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

bool gul::MediaWriter::codecsAreRegistered = false;

gul::MediaWriter::MediaWriter(const gul::File& rVideoPath,
                              int width, int height,
                              int fps, int bitrate)
  : m_path(rVideoPath),
    m_pFormatCtx(nullptr),
    m_pVideoCodecCtx(nullptr),
    m_pSWSContext(nullptr),
    m_pVideoStream(nullptr),
    m_pFrame(nullptr),
    m_pFrameRGBA(nullptr),
    m_isClosed(true),
    m_videoWidth(width),
    m_videoHeight(height),
    m_videoFPS(fps),
    m_videoBitrate(bitrate),
    usePTSFromFrames(false)
{
  if(!codecsAreRegistered)
  {
    av_register_all();
    codecsAreRegistered = true;
  }
}

gul::MediaWriter::MediaWriter(const gul::File& rVideoPath)
  : m_path(rVideoPath),
    m_pFormatCtx(nullptr),
    m_pVideoCodecCtx(nullptr),
    m_pSWSContext(nullptr),
    m_pVideoStream(nullptr),
    m_pFrame(nullptr),
    m_pFrameRGBA(nullptr),
    m_isClosed(true),
    m_videoWidth(0),
    m_videoHeight(0),
    m_videoFPS(0),
    m_videoBitrate(0),
    usePTSFromFrames(true)
{
  if(!codecsAreRegistered)
  {
    av_register_all();
    codecsAreRegistered = true;
  }
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
    if(pInputStream->codec->codec_type == AVMEDIA_TYPE_VIDEO && m_pVideoStream == nullptr)
    {
      /* find the video encoder */
      GUL_ASSERT_MSG(m_pFormatCtx->oformat->video_codec != CODEC_ID_NONE, "Not a video format!");
      m_pVideoCodec = avcodec_find_encoder(pInputStream->codec->codec_id);
      if(m_pVideoCodec == nullptr)
        GUL_FAIL("Codec not found!");

      /* Create new stream and copy settings from input */
      m_pVideoStream = avformat_new_stream(m_pFormatCtx, m_pVideoCodec);
      copyVideoEncoderCtxSettings(*pInputStream->codec);

      /*
       * NOTE: This if statement is from ffmpeg.c
       *
       * Avi is a special case here because it supports variable fps but
       * having the fps and timebase differe significantly adds quite some
       * overhead
       */
      if(!strcmp(m_pFormatCtx->oformat->name, "avi"))
      {
        m_pVideoCodecCtx->time_base.num = pInputStream->r_frame_rate.den;
        m_pVideoCodecCtx->time_base.den = pInputStream->r_frame_rate.num;
        m_pVideoCodecCtx->ticks_per_frame = pInputStream->codec->ticks_per_frame;
      }

      m_pVideoStream->avg_frame_rate = pInputStream->avg_frame_rate;
      m_pVideoStream->disposition = pInputStream->disposition;
      m_pVideoStream->time_base = pInputStream->time_base;
    }
    else
    {
      AVCodec* pCodec = avcodec_find_encoder(pInputStream->codec->codec_id);
      AVStream* pStream = avformat_new_stream(m_pFormatCtx, pCodec);
      AVCodecContext* pCodecCtx = pStream->codec;
      avcodec_copy_context(pCodecCtx, pInputStream->codec);

      /*
       * NOTE: This if statement is from ffmpeg.c
       */
      if((pCodecCtx->block_align == 1 ||
          pCodecCtx->block_align == 1152 ||
          pCodecCtx->block_align == 576) && pCodecCtx->codec_id == AV_CODEC_ID_MP3)
        pCodecCtx->block_align = 0;
      if(pCodecCtx->codec_id == AV_CODEC_ID_AC3)
        pCodecCtx->block_align = 0;

      if(m_pFormatCtx->oformat->flags & AVFMT_GLOBALHEADER)
        pCodecCtx->flags |= CODEC_FLAG_GLOBAL_HEADER;
      if(!strcmp(m_pFormatCtx->oformat->name, "mp4"))
        pCodecCtx->codec_tag = 0; // this is neccessary for mp4 copying.
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
  GUL_ASSERT_MSG(m_pFormatCtx->oformat->video_codec != CODEC_ID_NONE, "Not a video format!");
  m_pVideoCodec = avcodec_find_encoder(m_pFormatCtx->oformat->video_codec);
  if(m_pVideoCodec == nullptr)
    GUL_FAIL("Codec not found!");

  /* create the video stream */
  m_pVideoStream = avformat_new_stream(m_pFormatCtx, m_pVideoCodec);
  if(m_pVideoStream == nullptr)
    GUL_FAIL("Video Stream could not be created!");

  setDafaultVideoEncoderCtxSettings();

  /* open the codec */
  if(avcodec_open2(m_pVideoCodecCtx, m_pVideoCodec, nullptr) < 0)
    GUL_FAIL("Could not open codec!");

  allocateStructures();
  prepareOutputFile();

  m_isClosed = false;

  return true;
}

void gul::MediaWriter::copyVideoEncoderCtxSettings(const AVCodecContext& ctx)
{
  // NOTE: most things are copied from the function transcode_init in ffmpeg.c

  // Get a pointer to the codec context for the video stream
  m_pVideoCodecCtx = m_pVideoStream->codec;

  // enable multithreading
  m_pVideoCodecCtx->thread_count = 2;

  // bitrate modifier
  float bitrateModifier = (m_videoWidth * m_videoHeight) / static_cast<float>(ctx.width * ctx.height);

  /* initialize codec settings */
  avcodec_get_context_defaults3(m_pVideoCodecCtx, m_pVideoCodec);
  m_pVideoCodecCtx->codec_id = ctx.codec_id;
  m_pVideoCodecCtx->codec_type = ctx.codec_type;
  if(!m_pVideoCodecCtx->codec_tag)
  {
    if(!m_pFormatCtx->oformat->codec_tag ||
       av_codec_get_id(m_pFormatCtx->oformat->codec_tag, ctx.codec_tag) == m_pVideoCodecCtx->codec_id ||
       av_codec_get_tag(m_pFormatCtx->oformat->codec_tag, ctx.codec_id) <= 0)
      m_pVideoCodecCtx->codec_tag = ctx.codec_tag;
  }
  m_pVideoCodecCtx->rc_max_rate    = ctx.rc_max_rate;
  m_pVideoCodecCtx->rc_buffer_size = ctx.rc_buffer_size;
  m_pVideoCodecCtx->field_order    = ctx.field_order;
  m_pVideoCodecCtx->extradata = static_cast<uint8_t*>(av_mallocz((uint64_t)ctx.extradata_size + FF_INPUT_BUFFER_PADDING_SIZE));
  m_pVideoCodecCtx->extradata_size = ctx.extradata_size;
  memcpy(m_pVideoCodecCtx->extradata, ctx.extradata, ctx.extradata_size);
  m_pVideoCodecCtx->bits_per_coded_sample  = ctx.bits_per_coded_sample;
  m_pVideoCodecCtx->bits_per_raw_sample    = ctx.bits_per_raw_sample;
  m_pVideoCodecCtx->chroma_sample_location = ctx.chroma_sample_location;
  m_pVideoCodecCtx->width    = m_videoWidth;
  m_pVideoCodecCtx->height   = m_videoHeight;
  m_pVideoCodecCtx->bit_rate = ctx.bit_rate * bitrateModifier;
  if(m_pVideoCodecCtx->bit_rate == 0)
  {
    // empirical bit rate guess
    m_pVideoCodecCtx->bit_rate = m_pVideoCodecCtx->width * m_pVideoCodecCtx->height * 8;
  }
  m_pVideoCodecCtx->time_base = ctx.time_base;
  m_pVideoCodecCtx->time_base.num *= ctx.ticks_per_frame;
  m_pVideoCodecCtx->gop_size      = 12;
  m_pVideoCodecCtx->pix_fmt       = ctx.pix_fmt;
  m_pVideoCodecCtx->profile = ctx.profile;
  m_pVideoCodecCtx->level = FF_LEVEL_UNKNOWN; //ctx.level;
  m_pVideoCodecCtx->has_b_frames = ctx.has_b_frames;
  if(m_pVideoCodecCtx->codec_id == CODEC_ID_MPEG2VIDEO)
    m_pVideoCodecCtx->max_b_frames = 2;
  if(m_pVideoCodecCtx->codec_id == CODEC_ID_MPEG1VIDEO)
    m_pVideoCodecCtx->mb_decision = FF_MB_DECISION_RD;
  if(m_pFormatCtx->oformat->flags & AVFMT_GLOBALHEADER)
    m_pVideoCodecCtx->flags |= CODEC_FLAG_GLOBAL_HEADER;
}

void gul::MediaWriter::setDafaultVideoEncoderCtxSettings(void)
{
  // Get a pointer to the codec context for the video stream
  m_pVideoCodecCtx = m_pVideoStream->codec;

  // enable multithreading
  m_pVideoCodecCtx->thread_count = 2;

  /* initialize codec settings */
  avcodec_get_context_defaults3(m_pVideoCodecCtx, m_pVideoCodec);
  m_pVideoCodecCtx->codec_id = m_pFormatCtx->oformat->video_codec;
  m_pVideoCodecCtx->bit_rate = m_videoBitrate;
  m_pVideoCodecCtx->width    = m_videoWidth;
  m_pVideoCodecCtx->height   = m_videoHeight;
  m_pVideoCodecCtx->time_base.num = 1;
  m_pVideoCodecCtx->time_base.den = m_videoFPS;
  m_pVideoCodecCtx->gop_size      = 12;
  m_pVideoCodecCtx->pix_fmt       = PIX_FMT_YUV420P;
  if(m_pVideoCodecCtx->codec_id == CODEC_ID_MPEG2VIDEO)
    m_pVideoCodecCtx->max_b_frames = 2;
  if(m_pVideoCodecCtx->codec_id == CODEC_ID_MPEG1VIDEO)
    m_pVideoCodecCtx->mb_decision = FF_MB_DECISION_RD;
  if(m_pFormatCtx->oformat->flags & AVFMT_GLOBALHEADER)
    m_pVideoCodecCtx->flags |= CODEC_FLAG_GLOBAL_HEADER;

  // set desired time_base for the muxer
  m_pVideoStream->time_base = m_pVideoCodecCtx->time_base;
}

void gul::MediaWriter::allocateStructures(void)
{
  // Allocate video frame
  m_pFrame = av_frame_alloc();
  m_pFrame->pts = 0;
  avpicture_alloc((AVPicture*)m_pFrame, m_pVideoCodecCtx->pix_fmt,
                  m_pVideoCodecCtx->width, m_pVideoCodecCtx->height);

  // Allocate an AVFrame structure
  m_pFrameRGBA = av_frame_alloc();
  avpicture_alloc((AVPicture*)m_pFrameRGBA, PIX_FMT_RGBA,
                  m_pVideoCodecCtx->width, m_pVideoCodecCtx->height);

  // swscaler context
  m_pSWSContext = sws_getCachedContext(m_pSWSContext,
                                       m_pVideoCodecCtx->width, m_pVideoCodecCtx->height, PIX_FMT_RGBA,
                                       m_pVideoCodecCtx->width, m_pVideoCodecCtx->height, m_pVideoCodecCtx->pix_fmt,
                                       SWS_BILINEAR, nullptr, nullptr, nullptr);
}

void gul::MediaWriter::prepareOutputFile(void)
{
  /* open the output file*/
  if(avio_open(&m_pFormatCtx->pb, m_path.GetPath().GetData(), AVIO_FLAG_WRITE) < 0)
    GUL_FAIL("Video file could not be opened");

  /* Write the stream header, if any. */
  int err = avformat_write_header(m_pFormatCtx, nullptr);
  if(err < 0)
  {
    char a[255];
    av_strerror(err, a, 255);
    GUL_FAIL(a);
  }
}

void gul::MediaWriter::CloseVideo(void)
{
  GUL_ASSERT(!m_isClosed);

  // flush encoder
  while(encodeAndSaveVideoFrame(nullptr));


  /* Write the trailer, if any. The trailer must be written before you
   * close the CodecContexts open when you wrote the header; otherwise
   * av_write_trailer() may try to use memory that was freed on
   * av_codec_close(). */
  av_write_trailer(m_pFormatCtx);

  // Free RGBA memory
  avpicture_free((AVPicture*)m_pFrameRGBA);
  av_free(m_pFrameRGBA);
  m_pFrameRGBA = nullptr;

  // Free the frame buffer
  avpicture_free((AVPicture*)m_pFrame);
  av_free(m_pFrame);
  m_pFrame = nullptr;

  // free swscale context
  sws_freeContext(m_pSWSContext);
  m_pSWSContext = nullptr;

  // Close the codec
  avcodec_close(m_pVideoCodecCtx);
  m_pVideoCodecCtx = nullptr;

  /* Free the streams. */
//  for (unsigned int i = 0; i < pFormatCtx->nb_streams; i++) {
//     av_freep(&pFormatCtx->streams[i]->codec);
//      av_freep(&pFormatCtx->streams[i]);
//  }

  /* Close the output file. */
  avio_flush(m_pFormatCtx->pb);
  avio_close(m_pFormatCtx->pb);

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

bool gul::MediaWriter::encodeAndSaveVideoFrame(AVFrame* pFrameToEncode)
{
  /* encode the image */
  AVPacket pkt;

  av_init_packet(&pkt);
  pkt.data = nullptr;    // packet data will be allocated by the encoder
  pkt.size = 0;
//  pkt.flags |= AV_PKT_FLAG_KEY;

  int gotPacket;
  if(avcodec_encode_video2(m_pVideoCodecCtx, &pkt, pFrameToEncode, &gotPacket) < 0)
    GUL_FAIL("Frame could not be encoded!");

  if(gotPacket)
  {
    // compute pts in stream time_base
    if(pkt.pts != AV_NOPTS_VALUE)
      pkt.pts = av_rescale_q(pkt.pts , m_pVideoCodecCtx->time_base, m_pVideoStream->time_base);
    if(pkt.dts != AV_NOPTS_VALUE)
      pkt.dts = av_rescale_q(pkt.dts, m_pVideoCodecCtx->time_base, m_pVideoStream->time_base);

    pkt.stream_index = m_pVideoStream->index;

    /* Write the compressed frame to the media file. */
    if(!writePacket(pkt))
      GUL_FAIL("Encoded packet could not be written!");

    av_free_packet(&pkt);
  }

  // was something written
  return gotPacket;
}

bool gul::MediaWriter::writePacket(AVPacket& rPacket)
{
  return av_interleaved_write_frame(m_pFormatCtx, &rPacket) >= 0;
}
