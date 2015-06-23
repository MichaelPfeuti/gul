/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011-2015 Michael Pfeuti.
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
    threshold(127)
{
}

gul::FilterImageToBW::~FilterImageToBW(void)
{
}

void gul::FilterImageToBW::SetParameter(unsigned char bwThreshold)
{
  threshold = bwThreshold;
}

void gul::FilterImageToBW::SetParameter(const gul::Image& grayImage)
{
  GUL_ASSERT_MSG(grayImage.GetImageFormat() == gul::Image::IF_GRAY, "Input must be a grayscale image");
  inputImage = grayImage;
}

void gul::FilterImageToBW::Execute(void)
{
  outputImage = gul::Image(inputImage.GetWidth(),
                           inputImage.GetHeight(),
                           gul::Image::IF_GRAY);

  for(int y = 0; y < inputImage.GetHeight(); ++y)
  {
    for(int x = 0; x < inputImage.GetWidth(); ++x)
    {
      if(inputImage.GetColorConst(x, y, 0) < threshold)
      {
        outputImage.GetColor(x, y, 0) = 0;
        outputImage.GetColor(x, y, 1) = 0;
        outputImage.GetColor(x, y, 2) = 0;
      }
      else
      {
        outputImage.GetColor(x, y, 0) = 255;
        outputImage.GetColor(x, y, 1) = 255;
        outputImage.GetColor(x, y, 2) = 255;
      }
      outputImage.GetColor(x, y, 3) = inputImage.GetColorConst(x, y, 3);
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

