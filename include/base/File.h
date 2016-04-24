#pragma once
#ifndef _GUL_BASE_FILE_H_
#define _GUL_BASE_FILE_H_
/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011-2015 Michael Pfeuti
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

#include "String.h"
#include "XMLMacros.h"

namespace gul
{
  class GUL_EXPORT File : INHERIT_SERIALIZABLE(File)
  {
    DECLARE_RTTI(File)

    public:
      File(void);
      File(const String& rPath);
      virtual ~File(void);

      /**
       * @brief GetBasename
       * @return the name of the file without suffix.
       */
      String GetBasename(void) const;

      /**
       * @brief GetSuffix
       * @return the file ending of the file.
       */
      String GetSuffix(void) const;

      /**
       * @brief GetPath
       * @return the entire path the was passed in the constructor.
       */
      String GetPath(void) const;

      /**
       * @brief IsPathValid
       * @return true if path is not empty, false otherwise
       */
      bool IsPathValid(void) const;

      /**
       * @brief Test the file exists. It does not check permissions.
       * @return true if the file exists, false otherwise
       */
      bool Exists(void) const;

    private:
      String m_path;

    DECLARE_SERIALIZABLE()

      friend bool operator==(const File& rLeft, const File& rRight);
  };

  GUL_EXPORT bool operator!=(const File& rLeft, const File& rRight);
  GUL_EXPORT bool operator==(const File& rLeft, const File& rRight);
}

SPECIALIZE_TRAITS(gul::File)

#endif
