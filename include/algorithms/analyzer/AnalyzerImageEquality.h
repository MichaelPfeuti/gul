#pragma once
#ifndef _GUL_ALGORITHMS_ANALYZER_IMAGE_EQUALITY_H_
#define _GUL_ALGORITHMS_ANALYZER_IMAGE_EQUALITY_H_
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

#include "Analyzer.h"
#include "Image.h"

namespace gul
{
class AnalyzerImageEquality : public Analyzer
{

public:
  AnalyzerImageEquality(void);
  virtual ~AnalyzerImageEquality(void);

  void SetParameter(const Image& one, const Image& theOther);

  void SetParameter(float differenceThreshold);

  bool GetResult(void) const;

  virtual void Execute(void);

  static bool Execute(const Image& image1, const Image& image2, float differenceThreshold = 0.f);

private:
  Image image1;
  Image image2;

  float threshold;
  float difference;
};
}

#endif
