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

#include "MediaFrame.h"

gul::MediaFrame::MediaFrame(void)
  : m_hasAudio(false),
    m_hasVideo(false)
{
}

const gul::VideoFrame& gul::MediaFrame::GetVideoFrame(void) const
{
  return m_videoFrame;
}

gul::VideoFrame& gul::MediaFrame::GetVideoFrame(void)
{
  return m_videoFrame;
}

bool gul::MediaFrame::HasVideoFrame(void) const
{
  return m_hasVideo;
}

void gul::MediaFrame::SetHasVideoFrame(bool status)
{
  m_hasVideo = status;
}

const gul::AudioFrame& gul::MediaFrame::GetAudioFrame(void) const
{
  return m_audioFrame;
}

gul::AudioFrame& gul::MediaFrame::GetAudioFrame(void)
{
  return m_audioFrame;
}

bool gul::MediaFrame::HasAudioFrame(void) const
{
  return m_hasAudio;
}

void gul::MediaFrame::SetHasAudioFrame(bool status)
{
  m_hasAudio = status;
}
