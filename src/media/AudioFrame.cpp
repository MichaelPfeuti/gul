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

#include "AudioFrame.h"
#include "Misc.h"
#include "Log.h"

gul::AudioFrame::AudioFrame(void)
  : m_channels(0),
    m_sampleRate(0),
    m_presentationTime(0),
    m_frameIndex(0),
    m_sampleCount(0),
    m_data(nullptr),
    m_dataSize(0),
    m_isDataSynched(false)
{
}

gul::AudioFrame::AudioFrame(int channels, int sampleRate)
  : m_channels(channels),
    m_sampleRate(sampleRate),
    m_presentationTime(0),
    m_frameIndex(0),
    m_sampleCount(0),
    m_data(nullptr),
    m_dataSize(0),
    m_isDataSynched(false)
{

}

gul::AudioFrame::~AudioFrame(void)
{
  GUL_DELETE_ARRAY(m_data);

#ifdef LIBOPENAL_FOUND
  if(alIsBuffer(m_alBuffer))
  {
    alDeleteBuffers(1, &m_alBuffer);
    ALenum alError;
    if((alError = alGetError()) != AL_NO_ERROR)
    {
      GUL_LOG_WARNING("OpenAL could delete buffer (code %d)!", alError);
    }
  }
#endif
}

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

int gul::AudioFrame::GetChannels(void) const
{
  return m_channels;
}

int gul::AudioFrame::GetSampleRate(void) const
{
  return m_sampleRate;
}

void gul::AudioFrame::ResizeData(int sampleCount)
{
  int dataSize = sizeof(int16_t) * m_channels * sampleCount;
  if(dataSize != m_dataSize)
  {
    GUL_DELETE_ARRAY(m_data);
    m_data = new int16_t[m_channels * sampleCount];
  }
  m_sampleCount = sampleCount;
  m_dataSize = dataSize;
  m_isDataSynched = false;
}

int gul::AudioFrame::GetDataSize(void) const
{
  return m_dataSize;
}

int gul::AudioFrame::GetSampleCount(void) const
{
  return m_sampleCount;
}

int16_t* gul::AudioFrame::GetData(void)
{
  m_isDataSynched = false;
  return m_data;
}

const int16_t* gul::AudioFrame::GetData(void) const
{
  return m_data;
}


#ifdef LIBOPENAL_FOUND

const ALuint& gul::AudioFrame::GetALBuffer(void)
{
  ALenum alError;

  if(!alIsBuffer(m_alBuffer))
  {
    alGenBuffers(1, &m_alBuffer);
    if((alError = alGetError()) != AL_NO_ERROR)
    {
      GUL_LOG_WARNING("OpenAL could generate buffer (code %d)!", alError);
    }
  }

  if(!m_isDataSynched)
  {
    alBufferData(m_alBuffer,
                 AL_FORMAT_STEREO16,
                 m_data,
                 m_dataSize,
                 m_sampleRate);
    m_isDataSynched = true;

    if((alError = alGetError()) != AL_NO_ERROR)
    {
      GUL_LOG_WARNING("OpenAL could set buffer data (code %d)!", alError);
    }
  }

  return m_alBuffer;
}

#endif
