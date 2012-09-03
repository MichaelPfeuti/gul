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

#include "ConverterImageToGrayscale.h"
#include "Misc.h"
#include "Assert.h"
#include "Math.h"

gul::ConverterImageToGrayscale::ConverterImageToGrayscale(void)
  : inputImage(),
    outputImage(),
    conversionType(GCT_LUMINOSITY)
{
}

gul::ConverterImageToGrayscale::~ConverterImageToGrayscale(void)
{
}

gul::RGBA gul::ConverterImageToGrayscale::computeGreyValue(const RGBA& rgba) const
{
  float gray = 0.f;

  switch(conversionType)
  {
    case GCT_AVERAGE:
      gray = rgba.GetRed() + rgba.GetGreen() + rgba.GetBlue();
      gray /= 3.f;
      break;

    case GCT_LIGHTNESS:
      gray  = gul::min(gul::min(rgba.GetRed(), rgba.GetGreen()), rgba.GetBlue());
      gray += gul::max(gul::max(rgba.GetRed(), rgba.GetGreen()), rgba.GetBlue());
      gray /= 2.f;
      break;

    case GCT_LUMINOSITY:
      gray  = 0.21f * rgba.GetRed();
      gray += 0.72f * rgba.GetGreen();
      gray += 0.07f * rgba.GetBlue();
      break;

    default:
      FAIL("Unknown Grey Conversion Type!");
  }

  return gul::RGBA(gray, gray, gray, rgba.GetAlpha());
}

void gul::ConverterImageToGrayscale::SetParameter(GreyscaleConversionType type)
{
  conversionType = type;
}

void gul::ConverterImageToGrayscale::SetParameter(const gul::Image& colorImage)
{
  inputImage = colorImage;
}

void gul::ConverterImageToGrayscale::Execute(void)
{
  outputImage = gul::Image(inputImage.GetWidth(), inputImage.GetHeight(), inputImage.GetImageType());
  outputImage.AllocateMemory();

  for(int y = 0; y < inputImage.GetHeight(); ++y)
  {
    for(int x = 0; x < inputImage.GetWidth(); ++x)
    {
      gul::RGBA in = inputImage.GetPixel(x, y);
      outputImage.SetPixel(x, y, computeGreyValue(in));
    }
  }
}

gul::Image gul::ConverterImageToGrayscale::GetResult(void) const
{
  return outputImage;
}

gul::Image gul::ConverterImageToGrayscale::Execute(const gul::Image& colorImage)
{
  ConverterImageToGrayscale converter;
  converter.SetParameter(colorImage);
  converter.Execute();
  return converter.GetResult();
}

