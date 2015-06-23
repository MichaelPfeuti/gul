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

#include "VFM2DToSBSDelay.h"

gul::VFM2DToSBSDelay::VFM2DToSBSDelay(void)
  : m_delay(1)
{

}

gul::VFM2DToSBSDelay::~VFM2DToSBSDelay(void)
{
}

void gul::VFM2DToSBSDelay::SetParameter(int delay)
{
  m_delay = delay;
}

void gul::VFM2DToSBSDelay::Execute(const gul::Image& input, gul::Image& output)
{
  if(m_lastFrame.IsNull())
  {
    m_lastFrame = input;
  }

  if(m_delay == 0)
  {
    output = m_converter.Execute(m_lastFrame, input);
    m_lastFrame = input;
  }
  else
  {
    output = gul::Image(GetResultWidth(input.GetWidth()),
                        GetResultHeight(input.GetHeight()),
                        input.GetImageFormat());
    --m_delay;
  }

}

int gul::VFM2DToSBSDelay::GetResultWidth(int inputWidth) const
{
  return 2 * inputWidth;
}

int gul::VFM2DToSBSDelay::GetResultHeight(int inputHeight) const
{
  return inputHeight;
}
