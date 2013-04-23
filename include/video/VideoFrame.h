#pragma once
#ifndef _GUL_VIDEO_VIDEO_FRAME_H_
#define _GUL_VIDEO_VIDEO_FRAME_H_
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

#include "Image.h"
#include <cstdint>

namespace gul
{

  class VideoFrame : public gul::Image
  {
    public:
      VideoFrame(void);
      VideoFrame(const gul::Image& img);
      VideoFrame(int w, int h, ImageFormat dataImageFormat);
      VideoFrame(const VideoFrame& rImage);
      virtual ~VideoFrame(void);

      VideoFrame& operator=(const VideoFrame& other);

      void SetPresentationTime(float pts);
      float GetPresentationTime(void) const;

      void SetFrameIndex(uint64_t index);
      uint64_t GetFrameIndex(void) const;

    protected:
      using Image::operator =;

    private:
      float m_presentationTime; //!< PTS in seconds
      uint64_t m_frameIndex;
  };

}


#endif
