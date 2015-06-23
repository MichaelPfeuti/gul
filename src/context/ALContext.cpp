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

#include "ALContext.h"
#include "Log.h"
#include "Assert.h"
#include "ContextErrorHandling.h"

gul::ALContext::ALContext(void)
  : m_pDevice(nullptr),
    m_pContext(nullptr)
{
}

gul::ALContext::~ALContext(void)
{
  alcMakeContextCurrent(nullptr);
  if(m_pContext != nullptr)
    alcDestroyContext(m_pContext);
  if(m_pDevice != nullptr)
    alcCloseDevice(m_pDevice);
}

bool gul::ALContext::Initialize(void)
{
  GUL_ASSERT(m_pDevice == nullptr);
  GUL_ASSERT(m_pContext == nullptr);

  m_pDevice = alcOpenDevice(nullptr);
  if(m_pDevice == nullptr)
  {
    GUL_LOG_WARNING("OpenAL could not open default audio device!");
    return false;
  }
  m_pContext = alcCreateContext(m_pDevice, nullptr);
  if(m_pContext == nullptr)
  {
    GUL_LOG_WARNING("OpenAL could not create context (code %d)!");
    return false;
  }
  alcMakeContextCurrent(m_pContext);

  GUL_AL_CHECK_ERROR("Could not make context current!");

  return true;
}

void gul::ALContext::MakeCurrent(void)
{
  GUL_ASSERT(m_pContext != nullptr);
  alcMakeContextCurrent(m_pContext);
}
