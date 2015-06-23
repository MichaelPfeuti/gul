#pragma once
#ifndef _GUL_PERSISTANCE_SETTINGS_MANAGER_H_
#define _GUL_PERSISTANCE_SETTINGS_MANAGER_H_
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

#include "NonCopyable.h"
#include <cstdio>
#include "String.h"
#include "File.h"
#include "MapBasic.h"


namespace gul
{

  class GUL_EXPORT SettingsManager : public NonCopyable
  {
    public:
      explicit SettingsManager(const File& rPath);
      virtual ~SettingsManager(void);

      void Write(const String& rKey, const String& rValue);
      void Write(const String& rKey, double rValue);
      void Write(const String& rKey, int rValue);
      void Write(const String& rKey, long rValue);

      long ReadInt(const String& rKey) const;
      double ReadFloat(const String& rKey) const;
      String ReadString(const String& rKey) const;

      bool Contains(const String& rKey) const;
      bool IsEmpty(void) const;

      void Clear(void);
      void Flush(void);

    private:
      gul::String getDefaultPathPosix(void) const;
      void load(void);

    private:
      gul::File path;
      MapBasic<String, String> map;
      static const gul::String DELIMITER;
  };

}

#endif
