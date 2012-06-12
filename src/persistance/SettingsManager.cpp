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

#include "SettingsManager.h"
#include "Misc.h"
#include "Assert.h"
#include "String.h"

gul::SettingsManager::SettingsManager(void)
  : pFile(nullptr)
{
  //TODO: some default path

}

gul::SettingsManager::SettingsManager(const String& rPath)
  : pFile(nullptr)
{
  ASSERT_MSG(!rPath.IsEmpty(), "The path to the file cannot be empty")
  pFile = fopen(rPath.GetData(), "w+");

  ASSERT_MSG(pFile != nullptr, "Could not create/open settings file");
}

gul::SettingsManager::~SettingsManager(void)
{
  fclose(pFile);
}

void gul::SettingsManager::Write(const String& rKey, const String& rValue)
{
  GUL_UNUSED_VAR(rKey);
  GUL_UNUSED_VAR(rValue);
}

void gul::SettingsManager::Write(const String& rKey, double rValue)
{
  GUL_UNUSED_VAR(rKey);
  GUL_UNUSED_VAR(rValue);
}

void gul::SettingsManager::Write(const String& rKey, int rValue)
{
  GUL_UNUSED_VAR(rKey);
  GUL_UNUSED_VAR(rValue);
}

void gul::SettingsManager::Write(const String& rKey, long rValue)
{
  GUL_UNUSED_VAR(rKey);
  GUL_UNUSED_VAR(rValue);
}

int gul::SettingsManager::ReadInt(const String& rKey)
{
  GUL_UNUSED_VAR(rKey);
  return 0;
}

double gul::SettingsManager::ReadDouble(const String& rKey)
{
  GUL_UNUSED_VAR(rKey);
  return 0.0;
}

gul::String gul::SettingsManager::ReadString(const String& rKey)
{
  GUL_UNUSED_VAR(rKey);
  return gul::String("");
}

bool gul::SettingsManager::Contains(const String& rKey)
{
  GUL_UNUSED_VAR(rKey);
  return false;
}


void gul::SettingsManager::Clear(void)
{

}

bool gul::SettingsManager::IsEmpty(void)
{
  return true;
}

