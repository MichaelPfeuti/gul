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

#include "ALSource.h"
#include "Log.h"
#include "Assert.h"
#include "ContextErrorHandling.h"

gul::ALSource::ALSource(void)
  : m_source(0)
{
}

gul::ALSource::~ALSource(void)
{
  alSourceStop(m_source);
  alDeleteSources(1, &m_source);

  ALenum alError;
  if((alError = alGetError()) != AL_NO_ERROR || alIsSource(m_source))
  {
    GUL_LOG_WARNING("OpenAL could not delete source (code %d)!", alError);
  }
}

/**
 * @brief Initialized the source. Must be called before any other calls of this class.
 * @return  success status
 */
bool gul::ALSource::Initialize(void)
{
  alGenSources(1, &m_source);
  GUL_AL_CHECK_ERROR("Could not create source!");
  return true;
}

/**
 * @brief gul::ALSource::Play plays the current buffers
 * @return  success status
 *
 * In comparisson to the OpenAL play function, we do not restart
 * at the beginning. If the source is already playing, nothing
 * happens by calling Play() again.
 * When the source has played all its buffers and Play() is called
 * it will resart at the beginning, meaning the currently persent buffers.
 */
bool gul::ALSource::Play(void)
{
  ALint state;
  alGetSourcei(m_source, AL_SOURCE_STATE, &state);
  if(state != AL_PLAYING)
  {
    alSourcePlay(m_source);
  }

  GUL_AL_CHECK_ERROR("Could not play source!");
  return true;
}

/**
 * @brief Pause when the source is playing, otherwise nothing happens.
 * @return  success status
 */
bool gul::ALSource::Pause(void)
{
  alSourcePause(m_source);

  GUL_AL_CHECK_ERROR("Could not pause source!");
  return true;
}

/**
 * @brief Stop when the source is playing, other nothing happens.
 * @return  success status
 */
bool gul::ALSource::Stop(void)
{
  alSourceStop(m_source);

  GUL_AL_CHECK_ERROR("Could not stop source!");
  return true;
}

/**
 * @brief Rewind source and stops playing.
 * @return  success status
 *
 * After a successive Play() call the source start playing from the
 * oldest not yet removed buffer.
 */
bool gul::ALSource::Rewind(void)
{
  alSourceRewind(m_source);

  GUL_AL_CHECK_ERROR("Could not rewind source!");
  return true;
}

/**
 * @brief Add buffer to queue to be played.
 * @param buffer to be added to queue.
 * @return success status
 *
 * The buffer is not immediately played. The buffer is queued and
 * will be played when all previously added buffers are played.
 *
 * \b Note: You must not add a buffer twice unless it was played and
 *          removed. You must call RemoveBuffers() and check with
 *          IsBufferPlayed() if your buffer was remove. If so you
 *          can add it again.
 */
bool gul::ALSource::AddBuffer(ALuint buffer)
{
  if(m_playedBuffers.Contains(buffer))
    m_playedBuffers.Remove(buffer);

  alSourceQueueBuffers(m_source, 1, &buffer);

  GUL_AL_CHECK_ERROR("Could not rewind source!");
  return true;
}

/**
 * @brief Remove all played buffers from the source buffer queue
 * @return success status
 *
 * You can check if a buffer was removed with IsBufferPlayed().
 */
bool gul::ALSource::RemoveBuffers(void)
{
  ALint bufferCount;
  alGetSourcei(m_source, AL_BUFFERS_PROCESSED, &bufferCount);
  if(bufferCount > 0)
  {
    ALuint buffers[bufferCount];
    alSourceUnqueueBuffers(m_source, bufferCount, buffers);

    GUL_LOG_INFO("OpenAL removed %d played buffers from sources!", bufferCount);

    for(int i = 0; i < bufferCount; ++i)
      m_playedBuffers.Add(buffers[i]);
  }

  GUL_AL_CHECK_ERROR("Could not remove played buffers from sources!");
  return true;
}

/**
 * @brief Check if buffer was already played and removed
 * @param buffer to be checked
 * @return is buffer played?
 *
 * Note: you must call RemoveBuffers previous to this method.
 */
bool gul::ALSource::IsBufferPlayed(ALuint buffer)
{
  return m_playedBuffers.Contains(buffer);
}
