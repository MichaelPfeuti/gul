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

#include "UtilsImage.h"

#include "image/lena.c"
#include "image/lena_alpha.c"
#include "image/lena_gray.c"
#include "image/lena_bin.c"
#include "algorithms/lena_gray_average.c"
#include "algorithms/lena_gray_luminosity.c"
#include "algorithms/lena_gray_lightness.c"
#include "algorithms/lena_bw.c"

gul::Image gul::GetLena(void)
{
  return gul::Image(lena.width, lena.height,
                    gul::Image::IF_RGBA, lena.pixel_data);
}

gul::Image gul::GetLenaAlpha(void)
{
  return gul::Image(lena_alpha.width, lena_alpha.height,
                    gul::Image::IF_RGBA, lena_alpha.pixel_data);
}

gul::Image gul::GetLenaGrayscale(void)
{
  return gul::Image(lena_gray.width, lena_gray.height,
                    gul::Image::IF_GRAY, lena_gray.pixel_data);
}

gul::Image gul::GetLenaBin(void)
{
  return gul::Image(lena_bin.width, lena_bin.height,
                    gul::Image::IF_GRAY, lena_bin.pixel_data);
}

gul::Image gul::GetLenaGrayAverage(void)
{
  return gul::Image(lena_gray_average.width, lena_gray_average.height,
                    gul::Image::IF_GRAY, lena_gray_average.pixel_data);
}

gul::Image gul::GetLenaGrayLuminosity(void)
{
  return gul::Image(lena_gray_luminosity.width, lena_gray_luminosity.height,
                    gul::Image::IF_GRAY, lena_gray_luminosity.pixel_data);
}

gul::Image gul::GetLenaGrayLightness(void)
{
  return gul::Image(lena_gray_lightness.width, lena_gray_lightness.height,
                    gul::Image::IF_GRAY, lena_gray_lightness.pixel_data);
}

gul::Image gul::GetLenaBW(void)
{
  return gul::Image(lena_bw.width, lena_bw.height,
                    gul::Image::IF_GRAY, lena_bw.pixel_data);
}
