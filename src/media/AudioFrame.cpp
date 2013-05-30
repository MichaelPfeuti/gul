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

#include "AudioFrame.h"

gul::AudioFrame::AudioFrame(void)
{
}

//gul::AudioFrame::AudioFrame(const gul::Image& img)
//  : gul::Image(img),
//    m_presentationTime(0),
//    m_frameIndex(0)
//{
//}

//gul::AudioFrame::AudioFrame(int w, int h, ImageFormat dataImageFormat)
//  : gul::Image(w, h, dataImageFormat)
//{

//}

gul::AudioFrame::~AudioFrame(void)
{
}

//gul::AudioFrame& gul::AudioFrame::operator=(const gul::AudioFrame& other)
//{
//  gul::Image::operator =(other);
//  m_presentationTime = other.m_presentationTime;
//  m_frameIndex = other.m_frameIndex;
//  return *this;
//}

void gul::AudioFrame::SetPresentationTime(float pts)
{
  m_presentationTime = pts;
}


float gul::AudioFrame::GetPresentationTime(void) const
{
  return m_presentationTime;
}

void gul::AudioFrame::SetFrameIndex(uint64_t index)
{
  m_frameIndex = index;
}

uint64_t gul::AudioFrame::GetFrameIndex(void) const
{
  return m_frameIndex;
}

