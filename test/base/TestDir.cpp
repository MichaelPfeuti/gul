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

#include "Dir.h"
#include "CTestAssert.h"

namespace TestDir
{
  int Create(void)
  {
    gul::Dir dir(gul::CTestData::GetTempDirPath("testDir"));
    dir.Create();
    TEST_TRUE(dir.Exists());

    return EXIT_SUCCESS;
  }

  int Delete(void)
  {
    gul::Dir dir(gul::CTestData::GetTempDirPath("testDir"));
    dir.Create();
    TEST_TRUE(dir.Exists());
    dir.Delete();
    TEST_FALSE(dir.Exists());

    return EXIT_SUCCESS;
  }

  int DeleteContent(void)
  {
    gul::Dir dir(gul::CTestData::GetTempDirPath("testDir"));
    gul::Dir subdir1(gul::CTestData::GetTempDirPath("testDir/subdir1"));
    gul::Dir subdir2(gul::CTestData::GetTempDirPath("testDir/subdir2"));
    gul::Dir subsubdir(gul::CTestData::GetTempDirPath("testDir/subdir1/subsubdir"));

    dir.Create();
    TEST_TRUE(dir.Exists());
    subdir1.Create();
    TEST_TRUE(subdir1.Exists());
    subdir2.Create();
    TEST_TRUE(subdir2.Exists());
    subsubdir.Create();
    TEST_TRUE(subsubdir.Exists());

    dir.DeleteContent();
    TEST_FALSE(subdir1.Exists());
    TEST_FALSE(subdir2.Exists());
    TEST_FALSE(subsubdir.Exists());
    TEST_TRUE(dir.Exists());

    return EXIT_SUCCESS;
  }

}
