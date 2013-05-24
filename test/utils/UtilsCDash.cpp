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

#include "UtilsCDash.h"

#include <iostream>
#include <Assert.h>

void gul::UploadCDashImage(const gul::String& label,
                     const gul::File& path)
{
  ASSERT_MSG(path.GetSuffix().LowerCase().GetData() == gul::String("jpeg") ||
             path.GetSuffix().LowerCase().GetData() == gul::String("png"),
             "Only PNG or JPEG can be uploaded to CDash!");

  std::cerr << "<DartMeasurementFile name=\"";
  std::cerr << label.GetData();
  std::cerr << "\" type=\"image/";
  std::cerr << path.GetSuffix().LowerCase().GetData();
  std::cerr << "\">";
  std::cerr << path.GetPath().GetData();
  std::cerr << "</DartMeasurementFile>";
  std::cerr << std::endl;
}

void gul::UploadCDashMeasurement(const gul::String &label, int value)
{
  std::cerr << "<DartMeasurement name=\"";
  std::cerr << label.GetData();
  std::cerr << "\" type=\"numeric/integer\">";
  std::cerr << value;
  std::cerr << "</DartMeasrement>";
  std::cerr << std::endl;
}

void gul::UploadCDashMeasurement(const gul::String &label, double value)
{
  std::cerr << "<DartMeasurement name=\"";
  std::cerr << label.GetData();
  std::cerr << "\" type=\"numeric/double\">";
  std::cerr << value;
  std::cerr << "</DartMeasrement>";
}

void gul::UploadCDashMeasurement(const gul::String &label, bool value)
{
  std::cerr << "<DartMeasurement name=\"";
  std::cerr << label.GetData();
  std::cerr << "\" type=\"numeric/boolean\">";
  std::cerr << value;
  std::cerr << "</DartMeasrement>";
}
