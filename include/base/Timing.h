#pragma once
#ifndef _GUL_BASE_TIMING_H_
#define _GUL_BASE_TIMING_H_
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

namespace gul
{
  class String;
}

namespace gul
{
  GUL_EXPORT void TimingStart(void);
  GUL_EXPORT void TimingStop(const gul::String& rText);
}

#define GUL_TIMING_START()    gul::TimingStart()
#define GUL_TIMING_STOP(text) gul::TimingStop(text)


#endif
