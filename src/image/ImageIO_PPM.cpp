/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011-2013 Michael Pfeuti
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

#include "ImageIO_PPM.h"
#include <cstdio>
#include <cstring>
#include <ctype.h>
#include <cstdlib>
#include "Assert.h"
#include "File.h"

void gul::ImageIO_PPM::SetMode(PPMMode m)
{
  mode = m;
}

gul::Image gul::ImageIO_PPM::Load(const gul::File& rPath)
{
  GUL_ASSERT_MSG(rPath.Exists(), "File does not exists.");

  FILE* f = fopen(rPath.GetPath().GetData(), "r");

  // read magic number
  char dataMode[255];
  fscanf(f, " %s ", dataMode);

  // ignore any comment lines
  char c = getc(f);
  while(c == '#')
  {
    while(getc(f) != '\n') ;
    c = getc(f);
  }
  ungetc(c, f);

  // read image size
  int width, height;
  fscanf(f, " %d %d ", &width, &height);

  // read max value when not in binary mode
  int maxValue = 0;
  if(strcmp(dataMode, "P1") != 0 &&
     strcmp(dataMode, "P4") != 0)
  {
    fscanf(f, " %d ", &maxValue);
  }

  // ignore any trailing whitespaces
  //while (fgetc(f) != '\n') ;

  gul::Image image;

  if(strcmp(dataMode, "P1") == 0)
  {
    // b/w image
    image = gul::Image(width, height, gul::Image::IF_GRAY);
    for(int y = 0; y < image.GetHeight(); ++y)
    {
      unsigned char* pData = image.GetScanline(y);
      for(int x = 0; x < image.GetWidth(); ++x)
      {
        char bw = fgetc(f);
        while(!isdigit(bw))
        {
          bw = fgetc(f);
        }
        bw = 255 * (1 - atoi(&bw)) ;
        pData[image.GetNumberOfChannels()*x + 0] = bw;
        pData[image.GetNumberOfChannels()*x + 1] = bw;
        pData[image.GetNumberOfChannels()*x + 2] = bw;
        pData[image.GetNumberOfChannels()*x + 3] = 255;
      }
    }
  }
  else if(strcmp(dataMode, "P2") == 0)
  {
    image = gul::Image(width, height, gul::Image::IF_GRAY);
    // greyscale image
    for(int y = 0; y < image.GetHeight(); ++y)
    {
      unsigned char* pData = image.GetScanline(y);
      for(int x = 0; x < image.GetWidth(); ++x)
      {
        unsigned int bw;
        fscanf(f, " %u ", &bw);
        pData[image.GetNumberOfChannels()*x + 0] = bw * 255 / maxValue;
        pData[image.GetNumberOfChannels()*x + 1] = bw * 255 / maxValue;
        pData[image.GetNumberOfChannels()*x + 2] = bw * 255 / maxValue;
        pData[image.GetNumberOfChannels()*x + 3] = 255;
      }
    }
  }
  else if(strcmp(dataMode, "P3") == 0)
  {
    image = gul::Image(width, height, gul::Image::IF_RGBA);
    // rgb image
    for(int y = 0; y < image.GetHeight(); ++y)
    {
      unsigned char* pData = image.GetScanline(y);
      for(int x = 0; x < image.GetWidth(); ++x)
      {
        unsigned int r, g, b;
        fscanf(f, " %u %u %u ", &r, &g, &b);
        pData[image.GetNumberOfChannels()*x + 0] = r * 255 / maxValue;
        pData[image.GetNumberOfChannels()*x + 1] = g * 255 / maxValue;
        pData[image.GetNumberOfChannels()*x + 2] = b * 255 / maxValue;
        pData[image.GetNumberOfChannels()*x + 3] = 255;
      }
    }
  }
  else if(strcmp(dataMode, "P4") == 0)
  {
    // b/w image 8 pixels packed in one byte.
    image = gul::Image(width, height, gul::Image::IF_GRAY);
    unsigned char ucData[width * height];
    int byteWidth = (width + 0.5f) / 8;
    fread(ucData, sizeof(unsigned char), byteWidth * height, f);

    int bitShift = 7;
    for(int y = 0; y < image.GetHeight(); ++y)
    {
      unsigned char* pData = image.GetScanline(y);
      for(int x = 0; x < image.GetWidth(); ++x)
      {
        unsigned char bw = 255 * (1 - (ucData[x / 8 + y * byteWidth] >> bitShift & 1));
        pData[image.GetNumberOfChannels()*x + 0] = bw;
        pData[image.GetNumberOfChannels()*x + 1] = bw;
        pData[image.GetNumberOfChannels()*x + 2] = bw;
        pData[image.GetNumberOfChannels()*x + 3] = 255;
        --bitShift;
        if(bitShift < 0)
          bitShift = 7;
      }
      bitShift = 7;
    }
  }
  else if(strcmp(dataMode, "P5") == 0)
  {
    // greyscale image
    image = gul::Image(width, height, gul::Image::IF_GRAY);
    unsigned char ucData[width * height];
    fread(ucData, sizeof(unsigned char), width * height, f);
    for(int y = 0; y < image.GetHeight(); ++y)
    {
      unsigned char* pData = image.GetScanline(y);
      for(int x = 0; x < image.GetWidth(); ++x)
      {
        pData[image.GetNumberOfChannels()*x + 0] = ucData[x + y * width] * 255 / maxValue;
        pData[image.GetNumberOfChannels()*x + 1] = ucData[x + y * width] * 255 / maxValue;
        pData[image.GetNumberOfChannels()*x + 2] = ucData[x + y * width] * 255 / maxValue;
        pData[image.GetNumberOfChannels()*x + 3] = 255 ;
      }
    }
  }
  else if(strcmp(dataMode, "P6") == 0)
  {
    // rgb image
    image = gul::Image(width, height, gul::Image::IF_RGBA);
    unsigned char ucData[width * height * 3];
    fread(ucData, sizeof(unsigned char), 3 * width * height, f);
    for(int y = 0; y < image.GetHeight(); ++y)
    {
      unsigned char* pData = image.GetScanline(y);
      for(int x = 0; x < image.GetWidth(); ++x)
      {
        pData[image.GetNumberOfChannels()*x + 0] = ucData[(x + y * width) * 3 + 0] * 255 / maxValue;
        pData[image.GetNumberOfChannels()*x + 1] = ucData[(x + y * width) * 3 + 1] * 255 / maxValue;
        pData[image.GetNumberOfChannels()*x + 2] = ucData[(x + y * width) * 3 + 2] * 255 / maxValue;
        pData[image.GetNumberOfChannels()*x + 3] = 255;
      }
    }
  }
  else
  {
    GUL_FAIL("Unknown PPM Mode!");
    return gul::Image();
  }

  fclose(f);

  return image;
}

void gul::ImageIO_PPM::Save(const gul::File& rPath, const gul::Image& rImage)
{
  FILE* f = fopen(rPath.GetPath().GetData(), "w");


  switch(mode)
  {
    case PPM_BINARY:
      {
        fprintf(f, "P6\n");
        fprintf(f, "# CREATOR: gul (Graphic Utility Library)\n");

        fprintf(f, "%u %u\n", rImage.GetWidth(), rImage.GetHeight());
        fprintf(f, "%u\n", 255);

        unsigned char ucData[rImage.GetWidth()*rImage.GetHeight() * 3];

        for(int y = 0; y < rImage.GetHeight(); ++y)
        {
          const unsigned char* pData = rImage.GetScanline(y);
          for(int x = 0; x < rImage.GetWidth(); ++x)
          {
            ucData[(x + y * rImage.GetWidth()) * 3 + 0] = pData[rImage.GetNumberOfChannels() * x + 0];
            ucData[(x + y * rImage.GetWidth()) * 3 + 1] = pData[rImage.GetNumberOfChannels() * x + 1];
            ucData[(x + y * rImage.GetWidth()) * 3 + 2] = pData[rImage.GetNumberOfChannels() * x + 2];
          }
        }
        fwrite(ucData, sizeof(unsigned char), rImage.GetWidth()*rImage.GetHeight() * 3, f);

        break;
      }
    case PPM_ASCII:
      {
        fprintf(f, "P3\n");
        fprintf(f, "# CREATOR: gul (Graphic Utility Library)\n");
        fprintf(f, "%u %u\n", rImage.GetWidth(), rImage.GetHeight());
        fprintf(f, "%u\n", 255);

        for(int y = 0; y < rImage.GetHeight(); ++y)
        {
          const unsigned char* pData = rImage.GetScanline(y);
          for(int x = 0; x < rImage.GetWidth(); ++x)
          {
            fprintf(f, "%u\n%u\n%u\n", pData[rImage.GetNumberOfChannels()*x + 0],
                    pData[rImage.GetNumberOfChannels()*x + 1],
                    pData[rImage.GetNumberOfChannels()*x + 2]);
          }
          fprintf(f, "\n");
        }

        break;
      }
    default:
      GUL_FAIL("Unknown Enum!");
  }

  fclose(f);
}
