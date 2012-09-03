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
#include "AnalyzerImageEquality.h"
#include "CTestAssert.h"
#include "Utils.h"

namespace TestImageToGrayscale
{
  int Average(void)
  {
    gul::Image color = GetLenaAlphaGT();
    gul::ConverterImageToGrayscale converter;
    converter.SetParameter(color);
    converter.SetParameter(gul::ConverterImageToGrayscale::GCT_AVERAGE);

    converter.Execute();
    TEST_TRUE(gul::AnalyzerImageEquality::Execute(GetLenaGrayAverage(), converter.GetResult(), 0.0007f));

    return EXIT_SUCCESS;
  }

  int Luminosity(void)
  {
    gul::Image color = GetLenaAlphaGT();
    gul::ConverterImageToGrayscale converter;
    converter.SetParameter(color);
    converter.SetParameter(gul::ConverterImageToGrayscale::GCT_LUMINOSITY);

    converter.Execute();
    TEST_TRUE(gul::AnalyzerImageEquality::Execute(GetLenaGrayLuminosity(), converter.GetResult(), 0.001f));

    return EXIT_SUCCESS;
  }

  int Lightness(void)
  {
    gul::Image color = GetLenaAlphaGT();
    gul::ConverterImageToGrayscale converter;
    converter.SetParameter(color);
    converter.SetParameter(gul::ConverterImageToGrayscale::GCT_LIGHTNESS);

    converter.Execute();
    TEST_TRUE(gul::AnalyzerImageEquality::Execute(GetLenaGrayLightness(), converter.GetResult(), 0.0008f));

    return EXIT_SUCCESS;
  }
}
