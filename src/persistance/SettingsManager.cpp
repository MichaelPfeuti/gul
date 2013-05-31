/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011-2013 Michael Pfeuti.
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

#include "SettingsManager.h"
#include "Misc.h"
#include "Assert.h"
#include "File.h"
#include "String.h"

#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#if defined __GNUC__
# include <unistd.h>
#endif

const gul::String gul::SettingsManager::DELIMITER(":");

gul::SettingsManager::SettingsManager(const gul::File& rPath)
  : path(rPath)
{
  GUL_ASSERT_MSG(rPath.IsPathValid(), "The path to the file cannot be empty");
  load();
}

gul::SettingsManager::~SettingsManager(void)
{
  Flush();
}

void gul::SettingsManager::Write(const String& rKey, const String& rValue)
{
  map.Add(rKey, rValue);
}

void gul::SettingsManager::Write(const String& rKey, double rValue)
{
  map.Add(rKey, gul::String("%").Arg(rValue));
}

void gul::SettingsManager::Write(const String& rKey, int rValue)
{
  map.Add(rKey, gul::String("%").Arg(rValue));
}

void gul::SettingsManager::Write(const String& rKey, long rValue)
{
  map.Add(rKey, gul::String("%").Arg(rValue));
}

long gul::SettingsManager::ReadInt(const String& rKey) const
{
  if(map.Contains(rKey))
    return map.Get(rKey).ToLong();
  else
    return 0;
}

double gul::SettingsManager::ReadFloat(const String& rKey) const
{
  if(map.Contains(rKey))
    return map.Get(rKey).ToDouble();
  else
    return 0;
}

gul::String gul::SettingsManager::ReadString(const String& rKey) const
{
  if(map.Contains(rKey))
    return map.Get(rKey);
  else
    return "";
}

bool gul::SettingsManager::Contains(const String& rKey) const
{
  return map.Contains(rKey);
}

void gul::SettingsManager::Clear(void)
{
  map.Clear();
}

bool gul::SettingsManager::IsEmpty(void) const
{
  return map.IsEmpty();
}

void gul::SettingsManager::Flush(void)
{
  std::ofstream file(path.GetPath().GetData());
  if(!file.is_open())
  {
    //TODO: Log
    GUL_FAIL("Config file couldn't be written!");
    return;
  }
  gul::MapBasic<String, String>::Iterator it = map.GetIterator();
  gul::MapBasic<String, String>::Pair pair;
  while(it.HasNext())
  {
    pair = it.Next();
    file << pair.GetKey().GetData()
         << DELIMITER.GetData()
         << pair.GetValue().GetData()
         << std::endl;

    std::cout << pair.GetValue().GetData() << std::endl;
  }
  file.close();
}

void gul::SettingsManager::load(void)
{
  std::ifstream file(path.GetPath().GetData());
  if(!file.is_open())
  {
    //TODO: add logging here.
    //FAIL("Config file couldn't be read!!");
    return;
  }
  std::string line;

  while(getline(file, line))
  {
    if(line.find("#") == 0 || line.find("//") == 0)
      continue;

    char toSplit[line.length() + 1];
    strcpy(toSplit, line.c_str());
    char* token = strtok(toSplit, DELIMITER.GetData());
    gul::String key, value;
    if(token != nullptr)
    {
      key = token;
      token = strtok(nullptr, DELIMITER.GetData());
      if(token != nullptr)
      {
        value = token;
      }
    }

    if(!key.IsEmpty() && !value.IsEmpty())
      map.Add(key, value);
  }
}
