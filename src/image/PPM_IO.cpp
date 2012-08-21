/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011-2012 Michael Pfeuti
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

#include "PPM_IO.h"
#include <cstdio>
#include <cstring>
#include <ctype.h>
#include <cstdlib>
#include "Assert.h"
#include "File.h"

void gul::PPM_IO::SetMode(PPMMode m)
{
  mode = m;
}

gul::Image gul::PPM_IO::Load(const gul::File& rPath)
{
  ASSERT_MSG(rPath.Exists(), "File does not exists.");

  FILE* f = fopen(rPath.GetPath().GetData(), "r");

  // read magic number
  char dataMode[255];
  fscanf(f, " %s ", dataMode);

  // ignore any comment lines
  char c = getc(f);
  while (c == '#')
  {
    while (getc(f) != '\n') ;
    c = getc(f);
  }
  ungetc(c, f);

  // read image size
  int width, height;
  fscanf(f, " %d %d ", &width, &height);

  // read max value when not in binary mode
  int maxValueInt = 0;
  float maxValue = 0;
  if(strcmp(dataMode, "P1") != 0 &&
     strcmp(dataMode, "P4") != 0)
  {
    fscanf(f, " %d ", &maxValueInt);
    maxValue = static_cast<float>(maxValueInt);
  }

  // ignore any trailing whitespaces
  //while (fgetc(f) != '\n') ;

  gul::Image image(width, height);
  image.AllocateMemory();

  if(strcmp(dataMode, "P1") == 0)
  {
    // b/w image
    for(int y = 0; y < image.GetHeight(); ++y)
    {
      for(int x = 0; x < image.GetWidth(); ++x)
      {
        char bw = fgetc(f);
        while(!isdigit(bw))
        {
          bw = fgetc(f);
        }
        float greyVal = bw = 1-atof(&bw);
        gul::RGBA rgba(greyVal,greyVal,greyVal, 1.f);
        image.SetPixel(x,y,rgba);
      }
    }
  }
  else if(strcmp(dataMode, "P2") == 0)
  {
    // greyscale image
    for(int y = 0; y < image.GetHeight(); ++y)
    {
      for(int x = 0; x < image.GetWidth(); ++x)
      {
        unsigned int bw;
        fscanf(f, " %u ", &bw);
        gul::RGBA rgba(bw/maxValue,
                       bw/maxValue,
                       bw/maxValue,
                       1.f);
        image.SetPixel(x,y,rgba);
      }
    }
  }
  else if(strcmp(dataMode, "P3") == 0)
  {
    // rgb image
    for(int y = 0; y < image.GetHeight(); ++y)
    {
      for(int x = 0; x < image.GetWidth(); ++x)
      {
        unsigned int r, g, b;
        fscanf(f, " %u %u %u ", &r, &g, &b);
        gul::RGBA rgba(r/maxValue,
                       g/maxValue,
                       b/maxValue,
                       1.f);
        image.SetPixel(x,y,rgba);
      }
    }
  }
  else if(strcmp(dataMode, "P4") == 0)
  {
    // b/w image 8 pixels packed in one byte.
    unsigned char ucData[width*height];
    int byteWidth = (width+0.5f)/8;
    fread(ucData, sizeof(unsigned char), byteWidth*height, f);

    int bitShift = 7;
    for(int y = 0; y < image.GetHeight(); ++y)
    {
      for(int x = 0; x < image.GetWidth(); ++x)
      {
        float bw = 1.f-(ucData[x/8+y*byteWidth]>>bitShift & 1);
        gul::RGBA rgba(bw, bw, bw, 1.f);
        image.SetPixel(x,y,rgba);
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
    unsigned char ucData[width*height];
    fread(ucData, sizeof(unsigned char),width*height,f);
    for(int y = 0; y < image.GetHeight(); ++y)
    {
      for(int x = 0; x < image.GetWidth(); ++x)
      {
        float grey = ucData[x+y*width]/maxValue;
        gul::RGBA rgba(grey, grey, grey, 1.f);
        image.SetPixel(x,y,rgba);
      }
    }
  }
  else if(strcmp(dataMode, "P6") == 0)
  {
    // rgb image
    unsigned char ucData[width*height*3];
    fread(ucData, sizeof(unsigned char), 3*width*height,f);
    for(int y = 0; y < image.GetHeight(); ++y)
    {
      for(int x = 0; x < image.GetWidth(); ++x)
      {
        gul::RGBA rgba(ucData[(x+y*width)*3 + 0]/maxValue,
                       ucData[(x+y*width)*3 + 1]/maxValue,
                       ucData[(x+y*width)*3 + 2]/maxValue,
                       1.f);
        image.SetPixel(x,y,rgba);
      }
    }
  }
  else
  {
    FAIL("Unknown PPM Mode!");
  }

  fclose(f);

  return image;
}

void gul::PPM_IO::Save(const gul::File& rPath, const gul::Image& rImage)
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

    unsigned char ucData[rImage.GetWidth()*rImage.GetHeight()*3];

    for(int y = 0; y < rImage.GetHeight(); ++y)
    {
      for(int x = 0; x < rImage.GetWidth(); ++x)
      {
        gul::RGBA rgba = rImage.GetPixel(x, y);
        ucData[(x+y*rImage.GetWidth())*3 + 0] = static_cast<unsigned char>(rgba.GetRed()*255);
        ucData[(x+y*rImage.GetWidth())*3 + 1] = static_cast<unsigned char>(rgba.GetGreen()*255);
        ucData[(x+y*rImage.GetWidth())*3 + 2] = static_cast<unsigned char>(rgba.GetBlue()*255);
      }
    }
    fwrite(ucData, sizeof(unsigned char), rImage.GetWidth()*rImage.GetHeight()*3, f);

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
      for(int x = 0; x < rImage.GetWidth(); ++x)
      {
        gul::RGBA rgba = rImage.GetPixel(x, y);
        fprintf(f, "%u\n%u\n%u\n", static_cast<unsigned char>(rgba.GetRed()*255),
                                   static_cast<unsigned char>(rgba.GetGreen()*255),
                                   static_cast<unsigned char>(rgba.GetBlue()*255));
      }
      fprintf(f, "\n");
    }

    break;
  }
  default:
    FAIL("Unknown Enum!");
  }

  fclose(f);
}
