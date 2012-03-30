/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011 #FIRST AND LAST NAME#.
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

#include "FFMPEG.h"
#include "Assert.h"

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

bool gul::FFMPEG::codecsAreRegistered = false;

gul::FFMPEG::FFMPEG(const gul::String& videoPath)
  : path(videoPath)
{
  if(!codecsAreRegistered)
  {
    av_register_all();
    codecsAreRegistered = true;
  }
}

void gul::FFMPEG::OpenVideo(void)
{
  // Open video file
  if(avformat_open_input(&pFormatCtx, path.GetData(), nullptr, nullptr) != 0)
    FAIL("Couldn't open file");

  // Retrieve stream information
  if(avformat_find_stream_info(pFormatCtx, nullptr) < 0)
    FAIL("Couldn't find stream information");

  av_dump_format(pFormatCtx, 0, path.GetData(), 0);

  // Find the first video stream
  int videoStream = -1;
  for(unsigned int i = 0; i < pFormatCtx->nb_streams; i++)
    if(pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
    {
      videoStream = i;
      break;
    }
  if(videoStream == -1)
    FAIL("Didn't find a video stream");

  // Get a pointer to the codec context for the video stream
  pCodecCtx = pFormatCtx->streams[videoStream]->codec;


  // Find the decoder for the video stream
  pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
  if(pCodec == NULL)
  {
    FAIL("Unsupported codec!\n");
  }

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
  pSWSContext = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,
                               pCodecCtx->width, pCodecCtx->height, PIX_FMT_RGB24,
                               SWS_BILINEAR, nullptr, nullptr, nullptr);

  // scale the decoded video into the rgba video buffer



  // Read packets and generate frames
  int frameFinished;
  AVPacket packet;
  int i = 0;
  while(av_read_frame(pFormatCtx, &packet) >= 0)
  {
    // Is this a packet from the video stream?
    if(packet.stream_index == videoStream)
    {
      // Decode video frame
      avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet);

      // Did we get a video frame?
      if(frameFinished)
      {
        // Convert the image from its native format to RGB
        //Scale the raw data/convert it to our video buffer...
        sws_scale(pSWSContext, pFrame->data, pFrame->linesize, 0, pCodecCtx->height,
                  pFrameRGBA->data, pFrameRGBA->linesize);

        // Save the frame to disk
        if(++i <= 5)
          SaveFrame(pCodecCtx->width, pCodecCtx->height, i);
      }
    }

    // Free the packet that was allocated by av_read_frame
    av_free_packet(&packet);
  }
}

gul::FFMPEG::~FFMPEG(void)
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

void gul::FFMPEG::SaveFrame(int width, int height, int iFrame)
{
  FILE* pFile;
  char szFilename[32];
  int  y;

  // Open file
  sprintf(szFilename, "frame%d.ppm", iFrame);
  pFile = fopen(szFilename, "wb");
  if(pFile == NULL)
    return;

  // Write header
  fprintf(pFile, "P6\n%d %d\n255\n", width, height);

  // Write pixel data
  for(y = 0; y < height; y++)
    fwrite(pFrameRGBA->data[0] + y * pFrameRGBA->linesize[0], 1, width * 3, pFile);

  // Close file
  fclose(pFile);
}

