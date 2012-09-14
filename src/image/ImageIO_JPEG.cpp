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

#include "ImageIO_JPEG.h"
#include "Assert.h"
#include "Misc.h"
#include "File.h"
#include <cstdlib>
#include <cstdio>
#include <jpeglib.h>
#include <setjmp.h>

struct ErrorManager
{
  struct jpeg_error_mgr pub;
  jmp_buf setjmp_buffer;
};

METHODDEF(void)
ErrorCallback(j_common_ptr cinfo)
{
  struct ErrorManager* err = (struct ErrorManager*)(cinfo->err);
  (*cinfo->err->output_message)(cinfo);
  longjmp(err->setjmp_buffer, 1);
}

void gul::ImageIO_JPEG::SetQuality(int qual)
{
  this->quality = qual;
}

gul::Image gul::ImageIO_JPEG::Load(const gul::File& rPath)
{
  gul::Image gulImage;

  struct jpeg_decompress_struct cinfo;
  struct ErrorManager jerr;
  FILE* infile;
  JSAMPARRAY buffer;
  int row_stride;

  if((infile = fopen(rPath.GetPath().GetData(), "rb")) == NULL)
  {
    FAIL("cannot open file!");
    return gul::Image();
  }

  cinfo.err = jpeg_std_error(&jerr.pub);
  jerr.pub.error_exit = ErrorCallback;
  if(setjmp(jerr.setjmp_buffer))
  {
    jpeg_destroy_decompress(&cinfo);
    fclose(infile);
    FAIL("Invalid JPEG file!");
    return gul::Image();
  }

  jpeg_create_decompress(&cinfo);
  jpeg_stdio_src(&cinfo, infile);
  (void) jpeg_read_header(&cinfo, TRUE);

  (void) jpeg_start_decompress(&cinfo);
  row_stride = cinfo.output_width * cinfo.output_components;
  buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);

  gulImage = gul::Image(cinfo.output_width, cinfo.output_height, gul::Image::IT_RGBA);

  int y = 0;
  while(cinfo.output_scanline < cinfo.output_height)
  {
    (void) jpeg_read_scanlines(&cinfo, buffer, 1);

    for(unsigned int x = 0; x < cinfo.output_width; ++x)
    {
      gulImage.SetPixel(x, y, gul::RGBA(buffer[0][x * cinfo.output_components + 0] / 255.f,
                                        buffer[0][x * cinfo.output_components + 1] / 255.f,
                                        buffer[0][x * cinfo.output_components + 2] / 255.f,
                                        1.f));

    }
    ++y;
  }
  (void) jpeg_finish_decompress(&cinfo);

  jpeg_destroy_decompress(&cinfo);
  fclose(infile);

  if(jerr.pub.num_warnings != 0)
  {
    FAIL("Corrupt JPEG file!");
  }

  return gulImage;
}

void gul::ImageIO_JPEG::Save(const gul::File& rPath, const gul::Image& rImage)
{
  unsigned char image_buffer[rImage.GetHeight()*rImage.GetWidth() * 3];
  for(int y = 0; y < rImage.GetHeight(); ++y)
  {
    for(int x = 0; x < rImage.GetWidth(); ++x)
    {
      image_buffer[(x + y * rImage.GetWidth()) * 3 + 0] = rImage.GetPixel(x, y).GetRed()  * 255.f;
      image_buffer[(x + y * rImage.GetWidth()) * 3 + 1] = rImage.GetPixel(x, y).GetGreen() * 255.f;
      image_buffer[(x + y * rImage.GetWidth()) * 3 + 2] = rImage.GetPixel(x, y).GetBlue() * 255.f;
    }
  }

  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr jerr;
  FILE* outfile;
  JSAMPROW rowPointer[1];
  int row_stride;

  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_compress(&cinfo);

  if((outfile = fopen(rPath.GetPath().GetData(), "wb")) == NULL)
  {
    fprintf(stderr, "can't open %s\n", rPath.GetPath().GetData());
    return;
  }
  jpeg_stdio_dest(&cinfo, outfile);

  cinfo.image_width = rImage.GetWidth();
  cinfo.image_height = rImage.GetHeight();
  cinfo.input_components = 3;
  cinfo.in_color_space = JCS_RGB;
  jpeg_set_defaults(&cinfo);

  cinfo.comp_info[0].h_samp_factor = 1;
  cinfo.comp_info[0].v_samp_factor = 1;
  cinfo.comp_info[1].h_samp_factor = 1;
  cinfo.comp_info[1].v_samp_factor = 1;
  cinfo.comp_info[2].h_samp_factor = 1;
  cinfo.comp_info[2].v_samp_factor = 1;
  cinfo.progressive_mode = FALSE;

  jpeg_set_quality(&cinfo, this->quality, TRUE);

  jpeg_start_compress(&cinfo, TRUE);

  row_stride = rImage.GetWidth() * 3;
  while(cinfo.next_scanline < cinfo.image_height)
  {
    rowPointer[0] = &image_buffer[cinfo.next_scanline * row_stride];
    (void) jpeg_write_scanlines(&cinfo, rowPointer, 1);
  }
  jpeg_finish_compress(&cinfo);

  fclose(outfile);

  jpeg_destroy_compress(&cinfo);
}

