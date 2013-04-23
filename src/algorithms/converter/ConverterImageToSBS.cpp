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

#include "ConverterImageToSBS.h"
#include "Misc.h"
#include "Assert.h"
#include "Math.h"

gul::ConverterImageToSBS::ConverterImageToSBS(void)
  : m_leftImage(),
    m_rightImage(),
    m_sbsImage()
{
}

gul::ConverterImageToSBS::~ConverterImageToSBS(void)
{
}

void gul::ConverterImageToSBS::SetParameter(const gul::Image& leftImage,
    const gul::Image& rightImage)
{
  ASSERT_MSG(leftImage.GetHeight() == rightImage.GetHeight(), "Left and right image must have the same height!");
  m_leftImage = leftImage;
  m_rightImage = rightImage;
}

void gul::ConverterImageToSBS::Execute(void)
{
  m_sbsImage = gul::Image(m_leftImage.GetWidth() + m_rightImage.GetWidth(),
                          m_leftImage.GetHeight(),
                          m_leftImage.GetImageFormat());

  for(int y = 0; y < m_sbsImage.GetHeight(); ++y)
  {
    memcpy(m_sbsImage.GetScanline(y), m_leftImage.GetScanlineConst(y), m_leftImage.GetPitch());
    memcpy(m_sbsImage.GetScanline(y) + m_leftImage.GetPitch(), m_rightImage.GetScanlineConst(y), m_rightImage.GetPitch());
  }
}

gul::Image gul::ConverterImageToSBS::GetResult(void) const
{
  return m_sbsImage;
}

gul::Image gul::ConverterImageToSBS::Execute(const gul::Image& leftImage,
    const gul::Image& rightImage)
{
  ConverterImageToSBS converter;
  converter.SetParameter(leftImage, rightImage);
  converter.Execute();
  return converter.GetResult();
}

