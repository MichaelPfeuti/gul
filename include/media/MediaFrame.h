#pragma once
#ifndef _GUL_MEDIA_MEDIA_FRAME_H_
#define _GUL_MEDIA_MEDIA_FRAME_H_
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
#include "VideoFrame.h"
#include <cstdint>

namespace gul
{

  class GUL_EXPORT MediaFrame
  {
    public:
      MediaFrame(void);

      const VideoFrame& GetVideoFrame(void) const;
      VideoFrame& GetVideoFrame(void);
      bool HasVideoFrame(void) const;
      void SetHasVideoFrame(bool status);

      const AudioFrame& GetAudioFrame(void) const;
      AudioFrame& GetAudioFrame(void);
      bool HasAudioFrame(void) const;
      void SetHasAudioFrame(bool status);

    private:
      AudioFrame m_audioFrame;
      VideoFrame m_videoFrame;

      bool m_hasAudio;
      bool m_hasVideo;
  };

}


#endif
