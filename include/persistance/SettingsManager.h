#pragma once
#ifndef _GUL_PERSISTANCE_SETTINGS_MANAGER_H_
#define _GUL_PERSISTANCE_SETTINGS_MANAGER_H_
/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011-2012 Michael Pfeuti.
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

#include "NonCopyable.h"
#include <cstdio>

namespace gul
{
  class String;
}

namespace gul
{

  class SettingsManager : public NonCopyable
  {

    public:
      SettingsManager(void);
      explicit SettingsManager(const String& rPath);
      virtual ~SettingsManager(void);

      void Write(const String& rKey, const String& rValue);
      void Write(const String& rKey, double rValue);
      void Write(const String& rKey, int rValue);
      void Write(const String& rKey, long rValue);

      int ReadInt(const String& rKey);
      double ReadDouble(const String& rKey);
      String ReadString(const String& rKey);

      bool Contains(const String& rKey);
      void Clear(void);
      bool IsEmpty(void);

    private:
      FILE* pFile;
  };

}

#endif
