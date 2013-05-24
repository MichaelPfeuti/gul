#pragma once
#ifndef _GUL_BASE_DIR_H_
#define _GUL_BASE_DIR_H_
/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011-2013 Michael Pfeuti
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

namespace gul
{
  class GUL_EXPORT Dir
  {
    public:
      Dir(void);
      Dir(const String& rPath);
      virtual ~Dir(void);

      /**
       * @brief Delete this folder recursively
       */
      void Delete(void);

      /**
       * @brief Delete all content of the folder recursively without delete the folder itself.
       */
      void DeleteContent(void);

      /**
       * @brief Create the folder at the given path
       */
      void Create(void);

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
  };
}

#endif
