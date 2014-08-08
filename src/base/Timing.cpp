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

#include "Timing.h"
#include <ctime>
#include <cstdio>
#include "StackBasic.h"
#include "String.h"

namespace gul
{
  struct TimineOutput
  {
    String text;
    int depth;
  };

  StackBasic<clock_t> gTimingHandleStack;
  StackBasic<TimineOutput> gTimingOutputStack;
}

void gul::TimingStart(void)
{
  gTimingHandleStack.Push(clock());
}

void gul::TimingStop(const gul::String& rText)
{
  float elapsed = 1000.0f * (float)(clock() - gTimingHandleStack.Pop()) / CLOCKS_PER_SEC;
  TimineOutput output;
  output.text = gul::String("%: % ms").Arg(rText).Arg(elapsed);
  output.depth = gTimingHandleStack.Size();
  gTimingOutputStack.Push(output);

  while(gTimingHandleStack.IsEmpty() && !gTimingOutputStack.IsEmpty())
  {
    output = gTimingOutputStack.Pop();

    gul::String outString = gul::String("%") + output.text;
    for(int i = 0; i < output.depth; ++i)
      outString = outString.Arg(gul::String(" %"));

    outString = outString.Arg(gul::String("|-"));
    printf("%s\n", outString.GetData());
  }
}
