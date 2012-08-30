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

#include "ImageIO_PNG.h"
#include <cstdio>
#include <png.h>
#include "File.h"
#include "Assert.h"

gul::Image gul::ImageIO_PNG::Load(const gul::File& rPath)
{
  const int HEADER_SIZE = 8;
  unsigned char header[HEADER_SIZE];
  FILE* fp = fopen(rPath.GetPath().GetData(), "rb");
  if(!fp)
  {
    FAIL("File could not be opened!");
    return gul::Image();
  }

  fread(header, 1, HEADER_SIZE, fp);

  if(png_sig_cmp(header, 0, HEADER_SIZE) != 0)
  {
    FAIL("File is not a PNG file");
    return gul::Image();
  }

  png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
  if(png_ptr == NULL)
  {
    fclose(fp);
    FAIL("Incompatible runtime libpng version!");
    return gul::Image();
  }

  png_infop info_ptr = png_create_info_struct(png_ptr);
  if(info_ptr == NULL)
  {
    fclose(fp);
    png_destroy_read_struct(&png_ptr, NULL, NULL);
    FAIL("PNG read info could not be created!");
    return gul::Image();
  }

  if(setjmp(png_jmpbuf(png_ptr)))
  {
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    fclose(fp);
    FAIL("PNG data could not be read!");
    return gul::Image();
  }

  png_init_io(png_ptr, fp);
  png_set_sig_bytes(png_ptr, HEADER_SIZE);
  png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

  png_uint_32 width, height;
  int bit_depth, color_type, interlace_type;
  png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
               &interlace_type, NULL, NULL);

  png_bytep* row_pointers = png_get_rows(png_ptr, info_ptr);
  gul::Image image(width, height);
  image.AllocateMemory();
  switch(color_type)
  {
    case PNG_COLOR_TYPE_GRAY:
      for(png_uint_32 y = 0; y < height; ++y)
      {
        for(png_uint_32 x = 0; x < width; ++x)
        {
          float grey = row_pointers[y][x] / 255.f;
          image.SetPixel(x, y, gul::RGBA(grey, grey, grey, 1.f));
        }
      }
      break;

    case PNG_COLOR_TYPE_PALETTE:
      FAIL("PNG_COLOR_TYPE_PALETTE cannot be read!");
      break;

    case PNG_COLOR_TYPE_RGB:
      for(png_uint_32 y = 0; y < height; ++y)
      {
        for(png_uint_32 x = 0; x < width; ++x)
        {
          image.SetPixel(x, y, gul::RGBA(row_pointers[y][x * 3 + 0] / 255.f,
                                         row_pointers[y][x * 3 + 1] / 255.f,
                                         row_pointers[y][x * 3 + 2] / 255.f,
                                         1.f));
        }
      }
      break;

    case PNG_COLOR_TYPE_RGB_ALPHA:
      for(png_uint_32 y = 0; y < height; ++y)
      {
        for(png_uint_32 x = 0; x < width; ++x)
        {
          image.SetPixel(x, y, gul::RGBA(row_pointers[y][x * 4 + 0] / 255.f,
                                         row_pointers[y][x * 4 + 1] / 255.f,
                                         row_pointers[y][x * 4 + 2] / 255.f,
                                         row_pointers[y][x * 4 + 3] / 255.f));
        }
      }
      break;

    case PNG_COLOR_TYPE_GRAY_ALPHA:
      for(png_uint_32 y = 0; y < height; ++y)
      {
        for(png_uint_32 x = 0; x < width; ++x)
        {
          float grey  = row_pointers[y][x * 2 + 0] / 255.f;
          float alpha = row_pointers[y][x * 2 + 1] / 255.f;
          image.SetPixel(x, y, gul::RGBA(grey, grey, grey, alpha));
        }
      }
      break;

    default:
      FAIL("Unknown PNG_COLOR_TYPE!");
      png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
      fclose(fp);
      return gul::Image();
  }

  png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

  fclose(fp);


  return image;
}

void gul::ImageIO_PNG::Save(const File& rPath, const Image& rImage)
{
  FILE* fp;
  png_structp png_ptr;
  png_infop info_ptr;
  const int BIT_PER_CHANNEL = 8;

  /* Open the file */
  fp = fopen(rPath.GetPath().GetData(), "wb");
  if(fp == NULL)
  {
    FAIL("File could not be opened!");
    return;
  }

  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

  if(png_ptr == nullptr)
  {
    fclose(fp);
    FAIL("Incompatible runtime libpng version!");
    return;
  }

  info_ptr = png_create_info_struct(png_ptr);
  if(info_ptr == nullptr)
  {
    fclose(fp);
    png_destroy_write_struct(&png_ptr,  NULL);
    FAIL("PNG write info could not be created!");
    return;
  }

  if(setjmp(png_jmpbuf(png_ptr)))
  {
    fclose(fp);
    png_destroy_write_struct(&png_ptr, &info_ptr);
    FAIL("PNG data could not be written!");
    return;
  }

  png_init_io(png_ptr, fp);

  png_set_IHDR(png_ptr, info_ptr,
               rImage.GetWidth(), rImage.GetHeight(),
               BIT_PER_CHANNEL, PNG_COLOR_TYPE_RGBA,
               PNG_INTERLACE_NONE,
               PNG_COMPRESSION_TYPE_DEFAULT,
               PNG_FILTER_TYPE_DEFAULT);

  png_bytep* row_pointers = static_cast<png_bytep*>(png_malloc(png_ptr, rImage.GetHeight() * sizeof(png_bytep)));
  for(int y = 0; y < rImage.GetHeight(); ++y)
  {
    row_pointers[y] = static_cast<png_bytep>(png_malloc(png_ptr, sizeof(png_byte) * rImage.GetWidth() * rImage.GetNumberOfChannels()));
    for(int x = 0; x < rImage.GetWidth(); ++x)
    {
      gul::RGBA rgba = rImage.GetPixel(x, y);
      row_pointers[y][x * rImage.GetNumberOfChannels() + 0] = rgba.GetRed() * 255;
      row_pointers[y][x * rImage.GetNumberOfChannels() + 1] = rgba.GetGreen() * 255;
      row_pointers[y][x * rImage.GetNumberOfChannels() + 2] = rgba.GetBlue() * 255;
      row_pointers[y][x * rImage.GetNumberOfChannels() + 3] = rgba.GetAlpha() * 255;
    }
  }
  png_set_rows(png_ptr, info_ptr, row_pointers);

  png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

  for(int y = 0; y < rImage.GetHeight(); ++y)
  {
    png_free(png_ptr, row_pointers[y]);
  }
  png_free(png_ptr, row_pointers);

  png_destroy_write_struct(&png_ptr, &info_ptr);

  fclose(fp);
}
