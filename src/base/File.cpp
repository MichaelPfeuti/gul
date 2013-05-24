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

#include "File.h"
#include "Misc.h"
#include "String.h"
#include <unistd.h>


gul::File::File(void)
  : m_path()
{
}

gul::File::File(const String& rPath)
  : m_path(rPath)
{

}

gul::File::~File(void)
{
}

gul::String gul::File::GetBasename(void) const
{
  int start = m_path.FindBackward(gul::String("/"));
  // try windows splitter
  if(start < 0)
    start = m_path.FindBackward(gul::String("\\"));

  int end = m_path.FindBackward(gul::String("."));

  if(start < 0 && end < 0)
    return m_path;

  if(end < 0)
    end = m_path.Size();

  return m_path.Substring(start+1, end);
}

gul::String gul::File::GetSuffix(void) const
{
  int idx = m_path.FindBackward(gul::String("."));
  if(idx < 0)
    return gul::String();

  return m_path.Substring(idx + 1, m_path.Size());
}

gul::String gul::File::GetPath(void) const
{
  return m_path;
}

bool gul::File::IsPathValid(void) const
{
  return !m_path.IsEmpty();
}

bool gul::File::Exists(void) const
{
  return IsPathValid() &&
         access(m_path.GetData(), F_OK) == 0;
}
