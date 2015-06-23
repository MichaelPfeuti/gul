#pragma once
#ifndef _GUL_CONTEXT_AL_SOURCE_H_
#define _GUL_CONTEXT_AL_SOURCE_H_
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

#include "gul_export.h"

#include <AL/al.h>
#include <AL/alc.h>
#include <Set.h>

namespace gul
{

  /**
   * @brief The ALSource class provides a wrapper to OpenAL source operations.
   *
   * This class is just a simple wrapper around the alSource* funcitons.
   * The only additional functionality it offers is error checking.
   *
   * The only exception is Play().
   * Internally the buffers you add with AddBuffer() are queued.
   * To remove played buffers use RemoveBuffers() and to check if
   * a buffer was played and was removed use IsBufferPlayed().
   * This way you can reuse buffers (@see AddBuffer).
   */
  class GUL_EXPORT ALSource
  {
    public:
      ALSource(void);
      ~ALSource(void);

      bool Initialize(void);
      bool Play(void);
      bool Pause(void);
      bool Stop(void);
      bool Rewind(void);

      bool AddBuffer(ALuint buffer);
      bool RemoveBuffers(void);
      bool IsBufferPlayed(ALuint buffer);

    private:
      ALuint m_source;
      Set<ALuint> m_playedBuffers;
  };

}

#endif
