#pragma once
#ifndef _GUL_VIDEO_VIDEO_FRAME_MANIPULATOR_H_
#define _GUL_VIDEO_VIDEO_FRAME_MANIPULATOR_H_
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

namespace gul
{
  class Image;
}

namespace gul
{
  class VideoFrameManipulator
  {
    public:
      virtual ~VideoFrameManipulator(void) {}
      virtual void Execute(const gul::Image& input, gul::Image& output) = 0;
      virtual int GetResultWidth(int inputWidth) const = 0;
      virtual int GetResultHeight(int inputHeight) const = 0;
  };
}

#endif
