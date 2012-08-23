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

#include "TIFF_IO.h"
#define JPEG_SUPPORT
#include <tiffio.h>
#include "File.h"
#include "Assert.h"

gul::Image gul::TIFF_IO::Load(const gul::File& rPath)
{
  TIFF* tif = TIFFOpen(rPath.GetPath().GetData(), "r");
  if(tif == nullptr)
  {
    FAIL("Could not open TIFF file!");
    return gul::Image();
  }

  uint32 width, height;
  TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &width);
  TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &height);

  gul::Image image(width, height);
  image.AllocateMemory();

  uint32 npixels = width * height;
  uint32* raster = static_cast<uint32*>(_TIFFmalloc(npixels * sizeof(uint32)));
  if(TIFFReadRGBAImageOriented(tif, width, height, raster, ORIENTATION_TOPLEFT, 0))
  {
    FILE* f = fopen("Load.txt","w");
    float alpha;
    for(uint32 y = 0; y < height; ++y)
    {
      for(uint32 x = 0; x < width; ++x)
      {
        //TODO: this is premuptiplied by the ReadRGBA function. use ReadEncodedStrip
        //      to prevent the small rounding error due to the premultiplication!
        alpha = TIFFGetA(raster[x + y * width]) / 255.f;
        image.SetPixel(x, y, gul::RGBA(TIFFGetR(raster[x + y * width]) / (255.f * alpha),
                                       TIFFGetG(raster[x + y * width]) / (255.f * alpha),
                                       TIFFGetB(raster[x + y * width]) / (255.f * alpha),
                                       alpha));
        fprintf(f, "%1.0f ", image.GetPixel(x, y).GetBlue()*255);
      }
      fprintf(f, "\n");
    }
    fclose(f);
  }
  else
  {
    image = gul::Image();
    FAIL("TIFF file could no be read!");
  }

  _TIFFfree(raster);
  TIFFClose(tif);

  return image;
}


void gul::TIFF_IO::Save(const gul::File& rPath, const gul::Image& rImage)
{
  TIFF* out = TIFFOpen(rPath.GetPath().GetData(), "w");
  if(out == nullptr)
  {
    FAIL("Could not open TIFF file for writing!");
    return;
  }

  //TIFFSetField(out, TIFFTAG_DOCUMENTNAME, rPath.GetPath().GetData());
  TIFFSetField(out, TIFFTAG_IMAGEWIDTH, rImage.GetWidth());
  TIFFSetField(out, TIFFTAG_IMAGELENGTH, rImage.GetHeight());
  TIFFSetField(out, TIFFTAG_SAMPLESPERPIXEL, 4);
  TIFFSetField(out, TIFFTAG_BITSPERSAMPLE, 8);
  TIFFSetField(out, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
  TIFFSetField(out, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
  TIFFSetField(out, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);
  //TIFFSetField(out, TIFFTAG_COMPRESSION, compression);
  uint16 extra_samples[] = {EXTRASAMPLE_UNASSALPHA};
  TIFFSetField(out, TIFFTAG_EXTRASAMPLES, 1, extra_samples);
  TIFFSetField(out, TIFFTAG_ROWSPERSTRIP, TIFFDefaultStripSize(out, 4*rImage.GetWidth()));

  unsigned char* buf = static_cast<unsigned char*>(_TIFFmalloc(4 * rImage.GetWidth()));

  //Now writing image to the file one strip at a time
  for(int row = 0; row < rImage.GetHeight(); ++row)
  {
    for(int x = 0; x < rImage.GetWidth(); ++x)
    {
      gul::RGBA rgba = rImage.GetPixel(x, row);
      buf[x * 4 + 0] = rgba.GetRed() * 255;
      buf[x * 4 + 1] = rgba.GetGreen() * 255;
      buf[x * 4 + 2] = rgba.GetBlue() * 255;
      buf[x * 4 + 3] = rgba.GetAlpha() * 255;
    }

    if(TIFFWriteScanline(out, buf, row, 0) < 0)
    {
      FAIL("TIFF file could no be written!");
    }
  }
  TIFFFlushData(out);

  _TIFFfree(buf);
  TIFFClose(out);
}
