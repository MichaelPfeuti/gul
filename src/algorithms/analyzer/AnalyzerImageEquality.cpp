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

#include "AnalyzerImageEquality.h"


gul::AnalyzerImageEquality::AnalyzerImageEquality(void)
  : image1(),
    image2(),
    threshold(0)
{
}

gul::AnalyzerImageEquality::~AnalyzerImageEquality(void)
{
}

void gul::AnalyzerImageEquality::SetParameter(const Image& one, const Image& theOther)
{
  this->image1 = one;
  this->image2 = theOther;
}

void gul::AnalyzerImageEquality::SetParameter(float differenceThreshold)
{
  this->threshold = differenceThreshold;
}

bool gul::AnalyzerImageEquality::GetResult(void) const
{
  return threshold >= difference;
}

#include <cstdio>

void gul::AnalyzerImageEquality::Execute(void)
{
  if(image1.GetWidth() != image2.GetWidth() ||
     image1.GetHeight() != image2.GetHeight())
  {
    difference = threshold + 1.f;
    return;
  }

  float diffPerChannel[image1.GetNumberOfChannels()];
  for(int c = 0; c < image1.GetNumberOfChannels(); ++c)
    diffPerChannel[c] = 0;

  for(int y = 0; y < image1.GetHeight(); ++y)
  {
    for(int x = 0; x < image1.GetWidth(); ++x)
    {
      for(int c = 0; c < image1.GetNumberOfChannels(); ++c)
      {
        diffPerChannel[c] += gul::absoluteDifference<float>(image1.GetColorConst(x,y,c), image2.GetColorConst(x,y,c));
        difference += diffPerChannel[c];
      }
    }
  }

  difference /= image1.GetNumberOfChannels();
  difference /= image1.GetWidth() * image1.GetHeight();
  difference /= 255;

  fprintf(stderr, "error: %f, %f, %f, %f -> %f\n", diffPerChannel[0],diffPerChannel[1],diffPerChannel[2],diffPerChannel[3], difference);
}

bool gul::AnalyzerImageEquality::Execute(const Image& image1, const Image& image2, float differenceThreshold)
{
  AnalyzerImageEquality analyzer;
  analyzer.SetParameter(image1, image2);
  analyzer.SetParameter(differenceThreshold);
  analyzer.Execute();
  return analyzer.GetResult();
}

