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

#include "File.h"
#include "CTestAssert.h"

namespace TestFile
{
  int GetSuffix(void)
  {
    gul::File fileWithoutSuffix("test");
    TEST_EQUAL(fileWithoutSuffix.GetSuffix(), "");

    gul::File fileWithSuffix("test.file");
    TEST_EQUAL(fileWithSuffix.GetSuffix(), "file");

    gul::File fileWithTwoSuffix("test.file.suffix");
    TEST_EQUAL(fileWithTwoSuffix.GetSuffix(), "suffix");

    return EXIT_SUCCESS;
  }

  int GetBasename(void)
  {
    gul::File fileNoSuffix("test");
    TEST_EQUAL(fileNoSuffix.GetBasename(), "test");

    gul::File fileSuffix("test.file");
    TEST_EQUAL(fileSuffix.GetBasename(), "test");

    gul::File fileNoSuffixDirLinux("/linuxDir/test");
    TEST_EQUAL(fileNoSuffixDirLinux.GetBasename(), "test");

    gul::File fileSuffixDirLinux("/linuxDir/test.file");
    TEST_EQUAL(fileSuffixDirLinux.GetBasename(), "test");

    gul::File fileNoSuffixDirWin("C:\\WinDir\\test");
    TEST_EQUAL(fileNoSuffixDirWin.GetBasename(), "test");

    gul::File fileSuffixDirWin("C:\\WinDir\\test.file");
    TEST_EQUAL(fileSuffixDirWin.GetBasename(), "test");

    gul::File fileNoSuffixDirRootWin("C:\\test.file");
    TEST_EQUAL(fileNoSuffixDirRootWin.GetBasename(), "test");

    gul::File fileSuffixDirRootWin("C:\\test.file");
    TEST_EQUAL(fileSuffixDirRootWin.GetBasename(), "test");

    return EXIT_SUCCESS;
  }

}
