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

#include "MediaReader.h"
#include "Assert.h"
#include "AudioFrame.h"
#include "VideoFrame.h"
#include "MediaFrame.h"
#include "Log.h"

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libswresample/swresample.h>
#include <libavutil/opt.h>
#include <libavutil/imgutils.h>
}

gul::MediaReader::MediaReader(const gul::File& rPath)
  : m_path(rPath),
    m_pFormatCtx(nullptr),
    m_pPacket(nullptr),
    m_pFrame(nullptr),
    m_pFrameRGBA(nullptr),
    m_pDataBufferRGBA(nullptr),
    m_isFrameValid(false),
    m_isOpen(false),
    m_pVideoCodecCtx(nullptr),
    m_videoStreamIndex(AVERROR_STREAM_NOT_FOUND),
    m_pSWSContext(nullptr),
    m_pAudioCodecCtx(nullptr),
    m_audioStreamIndex(AVERROR_STREAM_NOT_FOUND),
    m_pSWRContext(nullptr)
{
}


gul::MediaReader::~MediaReader(void)
{
  if(m_isOpen)
  {
    Close();
  }
}

void gul::MediaReader::Close(void)
{
  // free packet
  if(m_pPacket != nullptr)
  {
    av_packet_unref(m_pPacket);
  }
  av_packet_free(&m_pPacket);

  // Close the codecs
  if(HasVideo())
  {
    avcodec_free_context(&m_pVideoCodecCtx);
    m_videoStreamIndex = AVERROR_STREAM_NOT_FOUND;

    // Free RGBA memory
    deleteVideoStructures();
  }
  if(HasAudio())
  {
    avcodec_free_context(&m_pAudioCodecCtx);
    m_audioStreamIndex = AVERROR_STREAM_NOT_FOUND;

    deleteAudioStructures();
  }

  // Close the video file
  avformat_close_input(&m_pFormatCtx);

  m_isFrameValid = false;
  m_isOpen = false;
}

void gul::MediaReader::allocateVideoStructures(void)
{
  // TODO: check if av_frame_get_buffer works
  m_pFrame = av_frame_alloc();

  // Allocate an AVFrame structure
  m_pFrameRGBA = av_frame_alloc();

  // Determine required buffer size and allocate buffer
  int numBytes;

  numBytes = av_image_get_buffer_size(AV_PIX_FMT_RGBA, m_pVideoCodecCtx->width,
                                      m_pVideoCodecCtx->height, 1);
  void* pData = av_malloc(static_cast<size_t>(numBytes) * sizeof(uint8_t));
  m_pDataBufferRGBA = static_cast<uint8_t*>(pData);

  // Assign appropriate parts of buffer to image planes in pFrameRGB
  av_image_fill_arrays(m_pFrameRGBA->data, m_pFrameRGBA->linesize, m_pDataBufferRGBA, AV_PIX_FMT_RGBA,
                       m_pVideoCodecCtx->width, m_pVideoCodecCtx->height, 1);

  // swscaler context
  m_pSWSContext = sws_getCachedContext(m_pSWSContext,
                                       m_pVideoCodecCtx->width, m_pVideoCodecCtx->height, m_pVideoCodecCtx->pix_fmt,
                                       m_pVideoCodecCtx->width, m_pVideoCodecCtx->height, AV_PIX_FMT_RGBA,
                                       SWS_BILINEAR, nullptr, nullptr, nullptr);
}

void gul::MediaReader::allocateAudioStructures(void)
{
  m_pSWRContext = swr_alloc();
  av_opt_set_int(m_pSWRContext, "out_channel_layout", AV_CH_LAYOUT_STEREO,  0);
  av_opt_set_sample_fmt(m_pSWRContext, "out_sample_fmt", AV_SAMPLE_FMT_S16,  0);
}

bool gul::MediaReader::Open(void)
{
  GUL_ASSERT(!m_isOpen);
  GUL_ASSERT(m_path.IsPathValid());

  // Open video file
  //m_pFormatCtx->flags |= AVFMT_FLAG_GENPTS;
  int ret = avformat_open_input(&m_pFormatCtx, m_path.GetPath().GetData(), nullptr, nullptr);
  if(ret != 0)
  {
    char error[AV_ERROR_MAX_STRING_SIZE];
    av_make_error_string(error, AV_ERROR_MAX_STRING_SIZE, ret);
    GUL_LOG_WARNING("File could not be opened. FFMPEG error: ", error);
    return false;
  }

  // Retrieve stream information

  if(avformat_find_stream_info(m_pFormatCtx, nullptr) < 0)
  {
    GUL_LOG_WARNING("No Video stream found");
    return false;
  }

  av_dump_format(m_pFormatCtx, 0, m_path.GetPath().GetData(), 0);

  m_videoStreamIndex = openCodec(AVMEDIA_TYPE_VIDEO, m_pVideoCodecCtx);
  m_audioStreamIndex = openCodec(AVMEDIA_TYPE_AUDIO, m_pAudioCodecCtx);

  if(m_videoStreamIndex != AVERROR_STREAM_NOT_FOUND)
  {
    allocateVideoStructures();
  }

  if(m_audioStreamIndex != AVERROR_STREAM_NOT_FOUND)
  {
    allocateAudioStructures();
  }

  m_isOpen = m_videoStreamIndex != AVERROR_STREAM_NOT_FOUND ||
             m_audioStreamIndex != AVERROR_STREAM_NOT_FOUND;


  if(m_isOpen)
  {
    m_pPacket = av_packet_alloc();
    GUL_LOG_INFO("Opened media successfully.");
  }
  else
  {
    GUL_LOG_WARNING("Media contains no audio nor video data.");
  }

  return m_isOpen;
}

void gul::MediaReader::deleteVideoStructures(void)
{
  av_freep(&m_pDataBufferRGBA);
  av_frame_free(&m_pFrameRGBA);

  // Free the frame buffer
  av_frame_free(&m_pFrame);

  // free swscale context
  sws_freeContext(m_pSWSContext);
  m_pSWSContext = nullptr;
}

void gul::MediaReader::deleteAudioStructures(void)
{
  swr_free(&m_pSWRContext);
}

int gul::MediaReader::openCodec(int type, AVCodecContext*& pContext) const
{
  AVMediaType mediaType = static_cast<AVMediaType>(type);
  int index = av_find_best_stream(m_pFormatCtx, mediaType, -1, -1, nullptr, 0);
  if(index != AVERROR_STREAM_NOT_FOUND)
  {
    AVCodecParameters* pParams = m_pFormatCtx->streams[index]->codecpar;
    AVCodec* pVideoCodec = avcodec_find_decoder(pParams->codec_id);
    if(pVideoCodec == nullptr)
    {
      GUL_LOG_WARNING("Reqired codec could not be found.");
      return AVERROR_STREAM_NOT_FOUND;
    }
    pContext = avcodec_alloc_context3(pVideoCodec);
    if(pContext == nullptr)
    {
      GUL_LOG_WARNING("Video Codec Context could not be allocated.");
      return AVERROR_STREAM_NOT_FOUND;
    }
    if(avcodec_parameters_to_context(pContext, pParams) < 0)
    {
      GUL_LOG_WARNING("Codec Parameters could not be copied.");
      return AVERROR_STREAM_NOT_FOUND;
    }
    // TODO: don't hardcode!
    pContext->thread_count = 4;
    pContext->framerate = av_guess_frame_rate(m_pFormatCtx, m_pFormatCtx->streams[index], NULL);
    if(avcodec_open2(pContext, pVideoCodec, nullptr) < 0)
    {
      GUL_LOG_WARNING("Reqired codec could not be opened.");
      return AVERROR_STREAM_NOT_FOUND;
    }
  }

  return index;
}

bool gul::MediaReader::readNextPacket(void)
{
  // no more data to read and decode
  if(m_pPacket == nullptr){
    return false;
  }

  av_packet_unref(m_pPacket);
  int ret = av_read_frame(m_pFormatCtx, m_pPacket);
  if(ret == AVERROR_EOF)
  {
    av_packet_unref(m_pPacket);
    av_packet_free(&m_pPacket);
    return true;
  }
  else if (ret == 0)
  {
    return true;
  }

  char error[AV_ERROR_MAX_STRING_SIZE];
  av_make_error_string(error, AV_ERROR_MAX_STRING_SIZE, ret);
  GUL_LOG_ERROR("FFMPEG error: ", error);

  return false;
}

AVPacket* gul::MediaReader::getPacket(void)
{
  return m_pPacket;
}

bool gul::MediaReader::decodePacket(AVCodecContext* pContext) const
{
  int ret = avcodec_send_packet(pContext, m_pPacket);

  if(ret != 0) {
    char error[AV_ERROR_MAX_STRING_SIZE];
    av_make_error_string(error, AV_ERROR_MAX_STRING_SIZE, ret);
    GUL_LOG_ERROR(error);
  }
  return ret == 0;
}

bool gul::MediaReader::getNextFrame(gul::VideoFrame& rFrame)
{
  GUL_ASSERT_MSG(rFrame.GetImageFormat() == gul::Image::IF_RGBA, "Video Frame is not RGBA!");

  int ret = avcodec_receive_frame(m_pVideoCodecCtx, m_pFrame);
  if(ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
  {
    return false;
  }
  else if(ret == 0)
  {
    setData(rFrame, m_pFrame);

    AVRational timeBase = m_pFormatCtx->streams[m_videoStreamIndex]->time_base;
    //double pts = AV_NOPTS_VALUE == m_pFrame->pkt_pts ? m_pVideoCodecCtx->frame_number : m_pFrame->pkt_pts;
    float pts =  m_pFrame->pts;
    rFrame.SetPresentationTime(pts * timeBase.num / timeBase.den);
    rFrame.SetFrameIndex(static_cast<uint64_t>(m_pVideoCodecCtx->frame_number));
    return true;
  }
  else
  {
    char error[AV_ERROR_MAX_STRING_SIZE];
    av_make_error_string(error, AV_ERROR_MAX_STRING_SIZE, ret);
    GUL_LOG_ERROR(error);
    GUL_LOG_WARNING("Video decoding failed!");
    return false;
  }
}

bool gul::MediaReader::getNextFrame(gul::AudioFrame& rFrame)
{
  int ret = avcodec_receive_frame(m_pAudioCodecCtx, m_pFrame);
  if(ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
  {
    return false;
  }
  else if(ret == 0)
  {
    setData(rFrame, m_pFrame);

    AVRational timeBase = m_pFormatCtx->streams[m_audioStreamIndex]->time_base;
    float pts = AV_NOPTS_VALUE == m_pFrame->pts ? m_pAudioCodecCtx->frame_number : m_pFrame->pts;
    rFrame.SetPresentationTime(pts * timeBase.num / timeBase.den);
    rFrame.SetFrameIndex(static_cast<uint64_t>(m_pAudioCodecCtx->frame_number));
    return true;
  }
  else
  {
    char error[AV_ERROR_MAX_STRING_SIZE];
    av_make_error_string(error, AV_ERROR_MAX_STRING_SIZE, ret);
    GUL_LOG_ERROR(error);
    GUL_LOG_WARNING("Video decoding failed!");
    return false;
  }
}

bool gul::MediaReader::getNextFrame(MediaFrame &rFrame)
{
  bool valid = getNextFrame(rFrame.GetVideoFrame());
  rFrame.SetHasVideoFrame(valid);
  rFrame.SetHasAudioFrame(false);
  if(!valid)
  {
    valid = getNextFrame(rFrame.GetAudioFrame());
    rFrame.SetHasAudioFrame(valid);
    rFrame.SetHasVideoFrame(false);
  }

  return valid;
}

bool gul::MediaReader::videoDecodingNeeded() const
{
  return m_pPacket == nullptr || m_pPacket->stream_index == m_videoStreamIndex;
}

bool gul::MediaReader::audioDecodingNeeded() const
{
  return m_pPacket == nullptr || m_pPacket->stream_index == m_audioStreamIndex;
}

void gul::MediaReader::setData(gul::VideoFrame& rTargetFrame, const AVFrame* pSourceFrame) const
{
  uint8_t* pData = rTargetFrame.GetData();
  int pitch = rTargetFrame.GetPitch();

  if(pSourceFrame != nullptr)
  {
    // Convert the image from its native format to RGBA
    // Scale the raw data/convert it to our video buffer...
    if(sws_scale(m_pSWSContext,
                 pSourceFrame->data, pSourceFrame->linesize,
                 0, m_pVideoCodecCtx->height,
                 &pData, &pitch) <  m_pVideoCodecCtx->height)
      GUL_FAIL("Image conversion failed!");
  }
  else
  {
    memset(pData, 0, static_cast<size_t>(pitch * rTargetFrame.GetHeight()));
  }
}

void gul::MediaReader::setData(gul::AudioFrame& rTargetFrame, AVFrame* pSourceFrame) const
{
  rTargetFrame.ResizeData(pSourceFrame->nb_samples);
  uint8_t* outData = reinterpret_cast<uint8_t*>(rTargetFrame.GetData());
  const uint8_t** inData = const_cast<const uint8_t**>(pSourceFrame->data);

  if(pSourceFrame->channel_layout)
  {
    av_opt_set_int(m_pSWRContext, "in_channel_layout",  static_cast<int>(pSourceFrame->channel_layout), 0);
  }
  else
  {
    av_opt_set_int(m_pSWRContext, "in_channel_layout", AV_CH_LAYOUT_STEREO, 0);
  }

  av_opt_set_int(m_pSWRContext, "in_sample_rate", pSourceFrame->sample_rate, 0);
  av_opt_set_int(m_pSWRContext, "out_sample_rate", pSourceFrame->sample_rate, 0);

  av_opt_set_sample_fmt(m_pSWRContext, "in_sample_fmt",  static_cast<AVSampleFormat>(pSourceFrame->format), 0);
  swr_init(m_pSWRContext);
  if(swr_convert(m_pSWRContext,
                 &outData, pSourceFrame->nb_samples,
                 inData, pSourceFrame->nb_samples) < pSourceFrame->nb_samples)
    GUL_FAIL("Audio resampling failed!");
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

void gul::MediaReader::GetNext(VideoFrame& rFrame)
{
  GUL_ASSERT(HasVideo());

  allocateFrame(rFrame);

  m_isFrameValid = getNextFrame(rFrame);

  // try reading until we have a valid frame
  while(!m_isFrameValid && readNextPacket())
  {
    if(videoDecodingNeeded() && decodePacket(m_pVideoCodecCtx)){
      m_isFrameValid = getNextFrame(rFrame);
    }
  }

  if(!IsFrameValid())
  {
    setData(rFrame, nullptr);
  }
}

void gul::MediaReader::GetNext(AudioFrame& rFrame)
{
  GUL_ASSERT(HasAudio());

  allocateFrame(rFrame);

  m_isFrameValid = getNextFrame(rFrame);

  // try reading next packet
  while(!m_isFrameValid && readNextPacket())
  {
    if(audioDecodingNeeded() && decodePacket(m_pAudioCodecCtx)){
      m_isFrameValid = getNextFrame(rFrame);
    }
  }

  if(!IsFrameValid())
  {
    setData(rFrame, nullptr);
  }
}

void gul::MediaReader::GetNext(MediaFrame& rFrame)
{
  GUL_ASSERT(HasAudio() || HasVideo());

  allocateFrame(rFrame.GetVideoFrame());
  allocateFrame(rFrame.GetAudioFrame());

  m_isFrameValid = getNextFrame(rFrame);

  while(!m_isFrameValid && readNextPacket())
  {
    if(audioDecodingNeeded()){
      decodePacket(m_pAudioCodecCtx);
    }
    if(videoDecodingNeeded()){
      decodePacket(m_pVideoCodecCtx);
    }
    m_isFrameValid = getNextFrame(rFrame);
  }

  if(!IsFrameValid())
  {
    setData(rFrame.GetVideoFrame(), nullptr);
    setData(rFrame.GetAudioFrame(), nullptr);
  }
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
