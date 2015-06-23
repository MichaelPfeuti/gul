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

#include "FilterImageToGrayscale.h"
#include "CTestAssert.h"
#include "UtilsImage.h"

namespace TestImageToGrayscale
{
  int Average(void)
  {
    gul::Image color = gul::GetLenaAlpha();
    gul::FilterImageToGrayscale converter;
    converter.SetParameter(color);
    converter.SetParameter(gul::FilterImageToGrayscale::GCT_AVERAGE);

    converter.Execute();
    TEST_EQUAL_IMAGE(converter.GetResult(), gul::GetLenaGrayAverage(), 0.f);

    return EXIT_SUCCESS;
  }

  int Luminosity(void)
  {
    gul::Image color = gul::GetLenaAlpha();
    gul::FilterImageToGrayscale converter;
    converter.SetParameter(color);
    converter.SetParameter(gul::FilterImageToGrayscale::GCT_LUMINOSITY);

    converter.Execute();
    TEST_EQUAL_IMAGE(converter.GetResult(), gul::GetLenaGrayLuminosity(), 0.0007f);

    return EXIT_SUCCESS;
  }

  int Lightness(void)
  {
    gul::Image color = gul::GetLenaAlpha();
    gul::FilterImageToGrayscale converter;
    converter.SetParameter(color);
    converter.SetParameter(gul::FilterImageToGrayscale::GCT_LIGHTNESS);

    converter.Execute();
    TEST_EQUAL_IMAGE(converter.GetResult(), gul::GetLenaGrayLightness(), 0.f);

    return EXIT_SUCCESS;
  }
}
