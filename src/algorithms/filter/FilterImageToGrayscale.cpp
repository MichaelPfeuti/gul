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

#include "FilterImageToGrayscale.h"
#include "Misc.h"
#include "Assert.h"
#include "Math.h"

gul::FilterImageToGrayscale::FilterImageToGrayscale(void)
  : inputImage(),
    outputImage(),
    conversionType(GCT_LUMINOSITY)
{
}

gul::FilterImageToGrayscale::~FilterImageToGrayscale(void)
{
}

void gul::FilterImageToGrayscale::SetParameter(GreyscaleFilterType type)
{
  conversionType = type;
}

void gul::FilterImageToGrayscale::SetParameter(const gul::Image& colorImage)
{
  GUL_ASSERT(colorImage.GetImageFormat() == gul::Image::IF_RGBA);

  inputImage = colorImage;
}

void gul::FilterImageToGrayscale::Execute(void)
{
  outputImage = gul::Image(inputImage.GetWidth(),
                           inputImage.GetHeight(),
                           gul::Image::IF_GRAY);

  for(int y = 0; y < inputImage.GetHeight(); ++y)
  {
    for(int x = 0; x < inputImage.GetWidth(); ++x)
    {
      float gray = 0;
      switch(conversionType)
      {
        case GCT_AVERAGE:
          gray = inputImage.GetColorConst(x, y, 0) + inputImage.GetColorConst(x, y, 1) + inputImage.GetColorConst(x, y, 2);
          gray /= 3.f;
          gray += 0.5f;
          break;

        case GCT_LIGHTNESS:
          gray  = gul::min(gul::min(inputImage.GetColorConst(x, y, 0), inputImage.GetColorConst(x, y, 1)), inputImage.GetColorConst(x, y, 2));
          gray += gul::max(gul::max(inputImage.GetColorConst(x, y, 0), inputImage.GetColorConst(x, y, 1)), inputImage.GetColorConst(x, y, 2));
          gray /= 2.f;
          break;

        case GCT_LUMINOSITY:
          gray  = 0.21f * inputImage.GetColorConst(x, y, 0);
          gray += 0.72f * inputImage.GetColorConst(x, y, 1);
          gray += 0.07f * inputImage.GetColorConst(x, y, 2);
          gray += 0.5f;
          break;

        default:
          GUL_FAIL("Unknown Grey Conversion Type!");
      }
      outputImage.GetColor(x, y, 0) = gray;
      outputImage.GetColor(x, y, 1) = gray;
      outputImage.GetColor(x, y, 2) = gray;
      outputImage.GetColor(x, y, 3) = inputImage.GetColorConst(x, y, 3);
    }
  }
}

gul::Image gul::FilterImageToGrayscale::GetResult(void) const
{
  return outputImage;
}

gul::Image gul::FilterImageToGrayscale::Execute(const gul::Image& colorImage)
{
  FilterImageToGrayscale converter;
  converter.SetParameter(colorImage);
  converter.Execute();
  return converter.GetResult();
}

