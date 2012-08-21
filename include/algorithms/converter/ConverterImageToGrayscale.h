#pragma once
#ifndef _GUL_ALGORITHMS_CONVERTER_IMAGE_TO_GRAYSCALE_H_
#define _GUL_ALGORITHMS_CONVERTER_IMAGE_TO_GRAYSCALE_H_
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

#include "Converter.h"
#include "Image.h"

namespace gul
{
class ConverterImageToGrayscale : public Converter
{

public:
  enum GreyscaleConversionType
  {
    GCT_LIGHTNESS,
    GCT_AVERAGE,
    GCT_LUMINOSITY
  };

public:
  ConverterImageToGrayscale(void);

  virtual ~ConverterImageToGrayscale(void);

  void SetParameter(GreyscaleConversionType type);

  void SetParameter(const gul::Image& colorImage);

  virtual void Execute(void);

  gul::Image GetResult(void) const;

  static gul::Image Execute(const gul::Image& colorImage);


private:
  gul::RGBA computeGreyValue(const RGBA& rgba) const;

private:
  gul::Image inputImage;
  gul::Image outputImage;
  GreyscaleConversionType conversionType;
};

}

#endif
