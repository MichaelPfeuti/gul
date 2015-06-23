#pragma once
#ifndef _GUL_CONTEXT_AL_CONTEXT_H_
#define _GUL_CONTEXT_AL_CONTEXT_H_
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

namespace gul
{
  /**
   * @brief The ALSource class provides a wrapper to OpenAL context operations.
   *
   * This class creates an OpenAL context and opens the default device.
   * This class can be used to reduce the boiler plat code of OpenAL. In addition
   * error checking is also done.
   *
   * \b Note: You must be careful with deleting a context. Make sure you delete th
   *          context as the last object. Otherwise, delete sources and other OpenAL
   *          object will fail. So you might want to create most gul::AL* classes
   *          on the heap so that you can controll the deletion order.
   */
  class GUL_EXPORT ALContext
  {
    public:
      ALContext(void);
      ~ALContext(void);

      bool Initialize(void);
      void MakeCurrent(void);

    private:
      ALCdevice* m_pDevice;
      ALCcontext* m_pContext;
  };

}

#endif
