#pragma once
#ifndef _GUL_TEST_UTILS_CDASH_H_
#define _GUL_TEST_UTILS_CDAHS_H_
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
#include <String.h>
#include <File.h>

namespace gul
{

  void GUL_EXPORT UploadCDashImage(const gul::String& label,
                                   const gul::File& path);

  void GUL_EXPORT UploadCDashMeasurement(const gul::String& label,
                                         int value);

  void GUL_EXPORT UploadCDashMeasurement(const gul::String& label,
                                         double value);

  void GUL_EXPORT UploadCDashMeasurement(const gul::String& label,
                                         bool value);
}

#endif
