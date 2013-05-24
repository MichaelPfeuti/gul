/***************************************************************************
**
** This Dir is part of gul (Graphic Utility Library).
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
** If you have questions regarding the use of this Dir, please contact
** Michael Pfeuti at mpfeuti@ganymede.ch.
**
***************************************************************************/

#include "Dir.h"
#include "Misc.h"
#include "String.h"
#include <unistd.h>
#include <dirent.h>
#include "Assert.h"
#include <cstdio>
#include <sys/stat.h>


gul::Dir::Dir(void)
  : m_path()
{
}

gul::Dir::Dir(const String& rPath)
  : m_path(rPath)
{

}

gul::Dir::~Dir(void)
{
}

void gul::Dir::Delete(void)
{
  DeleteContent();
  rmdir(m_path.GetData());
}

void gul::Dir::DeleteContent(void)
{
  DIR* dir = opendir(m_path.GetData());
  if(dir == nullptr)
    return;

  dirent* entry = readdir(dir);
  struct stat entryStat;
  while(entry != nullptr)
  {
    gul::String filename(entry->d_name);
    if(filename != gul::String(".") &&
       filename != gul::String(".."))
    {
      gul::String path = m_path + "/" + filename;
      stat(path.GetData(), &entryStat);
      if(S_ISREG(entryStat.st_mode))
      {
        remove(path.GetData());
      }
      else if(S_ISDIR(entryStat.st_mode))
      {
        Dir subdir(path.GetData());
        subdir.Delete();
      }
    }

    entry = readdir(dir);
  }
  closedir(dir);
}

void gul::Dir::Create(void)
{
  mkdir(m_path.GetData(), ALLPERMS);
}


gul::String gul::Dir::GetPath(void) const
{
  return m_path;
}

bool gul::Dir::IsPathValid(void) const
{
  return !m_path.IsEmpty();
}

bool gul::Dir::Exists(void) const
{
  return IsPathValid() &&
         access(m_path.GetData(), F_OK) == 0;
}
