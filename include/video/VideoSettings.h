#pragma once
#ifndef _GUL_VIDEO_VIDEO_SETTINGS_H_
#define _GUL_VIDEO_VIDEO_SETTINGS_H_
/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011-2012#FIRST AND LAST NAME#.
**
** Contact: #FIRST AND LAST NAME# (#EMAIL#)
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
** #FIRST AND LAST NAME# at #EMAIL#.
**
***************************************************************************/

namespace gul
{

class VideoSettings
{
public:
  VideoSettings(int videoWidth, int videoHeight,
                int videoBitRate = 400000,
                int videoFrameRateNum = 1,
                int videoFrameRateDen = 30,
                int videoGroupOfPictureSize = 12)
    : width(videoWidth),
      height(videoHeight),
      bitRate(videoBitRate),
      frameRateNum(videoFrameRateNum),
      frameRateDen(videoFrameRateDen),
      groupOfPictureSize(videoGroupOfPictureSize)
  {}

  int GetWidth(void) const              { return width; }
  int GetHeight(void) const             { return height; }
  int GetBitRate(void) const            { return bitRate; }
  int GetFrameRateNum(void) const        { return frameRateNum; }
  int GetFrameRateDen(void) const        { return frameRateDen; }
  int GetGroupOfPictureSize(void) const { return groupOfPictureSize; }

private:
  int width;
  int height;
  int bitRate;
  int frameRateNum;
  int frameRateDen;
  int groupOfPictureSize;
};

}

#endif
