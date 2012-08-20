/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011-2012 Michael Pfeuti.
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

#include "Utils.h"

#include "colorImageSample.c"

gul::Image getGroudTruth(void)
{
  return gul::Image(colorImageSample.width, colorImageSample.height,
                    gul::Image::IT_RGBA, colorImageSample.pixel_data);
}

bool isEqualWithGroundTruth(const gul::Image& image, gul::Image::ImageType typeToCheck)
{
  if(image.GetWidth() != colorImageSample.width ||
     image.GetHeight() != colorImageSample.height)
    return false;

  const int widthStride = colorImageSample.width*colorImageSample.bytes_per_pixel;
  for(int y = 0; y < image.GetHeight(); ++y)
  for(int x = 0; x < image.GetWidth(); ++x)
  {
    gul::RGBA rgbaGT(colorImageSample.pixel_data[y*widthStride + x*colorImageSample.bytes_per_pixel + 0],
                     colorImageSample.pixel_data[y*widthStride + x*colorImageSample.bytes_per_pixel + 1],
                     colorImageSample.pixel_data[y*widthStride + x*colorImageSample.bytes_per_pixel + 2],
                     colorImageSample.pixel_data[y*widthStride + x*colorImageSample.bytes_per_pixel + 3]);
    gul::RGBA rgba = image.GetPixel(x, y);

    switch(typeToCheck)
    {
    case gul::Image::IT_RGBA:
      if(rgba.GetRed() != rgbaGT.GetRed() ||
         rgba.GetBlue() != rgbaGT.GetBlue() ||
         rgba.GetGreen() != rgbaGT.GetGreen() ||
         rgba.GetAlpha() != rgbaGT.GetAlpha())
        return false;
      break;
    case gul::Image::IT_RGB:
      if(rgba.GetRed() != rgbaGT.GetRed() ||
         rgba.GetBlue() != rgbaGT.GetBlue() ||
         rgba.GetGreen() != rgbaGT.GetGreen())
        return false;
      break;
    case gul::Image::IT_GREY:
//      if(rgba.GetRed() != rgbaGT.GetRed() ||
//         rgba.GetBlue() != rgbaGT.GetBlue() ||
//         rgba.GetGreen() != rgbaGT.GetGreen() ||
//         rgba.GetAlpha() != rgbaGT.GetAlpha())
        return false;
      break;
    }

  }

  return true;
}


