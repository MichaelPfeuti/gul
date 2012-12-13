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

#include "FilterImageToBW.h"
#include "Misc.h"
#include "Assert.h"
#include "Math.h"

gul::FilterImageToBW::FilterImageToBW(void)
  : inputImage(),
    outputImage(),
    threshold(0.5f)
{
}

gul::FilterImageToBW::~FilterImageToBW(void)
{
}

void gul::FilterImageToBW::SetParameter(float bwThreshold)
{
  ASSERT_MSG(0.f <= bwThreshold, "threshold must be between 0 and 1");
  ASSERT_MSG(1.f >= bwThreshold, "threshold must be between 0 and 1");
  threshold = bwThreshold;
}

void gul::FilterImageToBW::SetParameter(const gul::Image& grayImage)
{
  ASSERT_MSG(grayImage.GetImageType() == gul::Image::IT_GRAY, "Input must be a grayscale image");
  inputImage = grayImage;
}

void gul::FilterImageToBW::Execute(void)
{
  outputImage = gul::Image(inputImage.GetWidth(), inputImage.GetHeight(), inputImage.GetImageType());

  for(int y = 0; y < inputImage.GetHeight(); ++y)
  {
    for(int x = 0; x < inputImage.GetWidth(); ++x)
    {
      gul::RGBA in = inputImage.GetPixel(x, y);
      if(in.GetRed() < threshold)
      {
        outputImage.SetPixel(x, y, gul::RGBA(0.f, 0.f, 0.f, in.GetAlpha()));
      }
      else
      {
        outputImage.SetPixel(x, y, gul::RGBA(1.f, 1.f, 1.f, in.GetAlpha()));
      }
    }
  }
}

gul::Image gul::FilterImageToBW::GetResult(void) const
{
  return outputImage;
}

gul::Image gul::FilterImageToBW::Execute(const gul::Image& grayImage)
{
  FilterImageToBW converter;
  converter.SetParameter(grayImage);
  converter.Execute();
  return converter.GetResult();
}

