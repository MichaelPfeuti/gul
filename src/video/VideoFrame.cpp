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

#include "VideoFrame.h"

gul::VideoFrame::VideoFrame(void)
{
}

gul::VideoFrame::VideoFrame(const gul::Image& img)
  : gul::Image(img),
    presentationTime(0)
{
}

gul::VideoFrame::VideoFrame(int w, int h, ImageType dataImageType)
  : gul::Image(w, h, dataImageType)
{

}

gul::VideoFrame::~VideoFrame(void)
{
}

gul::VideoFrame& gul::VideoFrame::operator=(const gul::VideoFrame& other)
{
  gul::Image::operator =(other);
  presentationTime = other.presentationTime;
  return *this;
}

void gul::VideoFrame::SetPresentationTime(uint64_t pts)
{
  presentationTime = pts;
}


uint64_t gul::VideoFrame::GetPresentationTime(void) const
{
  return presentationTime;
}

