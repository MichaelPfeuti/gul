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

#include "MediaConverter.h"
#include "VideoFrameManipulator.h"
#include "MediaReader.h"
#include "MediaWriter.h"
#include "VideoFrame.h"
#include "Misc.h"

gul::MediaConverter::MediaConverter(const gul::File& rInputVideo)
  : pMediaReader(new gul::MediaReader(rInputVideo)),
    pMediaWriter(nullptr),
    pManipulator(nullptr)
{

}

void gul::MediaConverter::Init(const gul::File& rOutputVideo, gul::VideoFrameManipulator& rManipulator)
{
  GUL_DELETE(pManipulator);
  pManipulator = &rManipulator;

  pMediaReader->Open();
  GUL_DELETE(pMediaWriter);
  pMediaWriter = new gul::MediaWriter(rOutputVideo);
  pMediaWriter->setSize(rManipulator.GetResultWidth(pMediaReader->GetWidth()),
                        rManipulator.GetResultHeight(pMediaReader->GetHeight()));
  pMediaWriter->openVideo(*pMediaReader->m_pFormatCtx);
}

void gul::MediaConverter::Execute(void)
{
  gul::VideoFrame input;
  gul::VideoFrame output;

  pMediaReader->allocateFrame(input);

  // copy video
  AVPacket* pPacket = pMediaReader->getNextPacket();
  while(pPacket != nullptr)
  {
    if(pMediaReader->isVideoPacket(*pPacket))
    {
      if(pMediaReader->decodePacket(*pPacket, input))
      {
        pManipulator->Execute(input, output);
        output.SetPresentationTime(input.GetPresentationTime());
        output.SetFrameIndex(input.GetFrameIndex());
        pMediaWriter->AddFrame(output);
      }
    }
    else
    {
      pMediaWriter->writePacket(*pPacket);
    }
    pPacket = pMediaReader->getNextPacket();
  }

  while(pMediaReader->decodeRemaining(input))
  {
    pManipulator->Execute(input, output);
    output.SetPresentationTime(input.GetPresentationTime());
    output.SetFrameIndex(input.GetFrameIndex());
    pMediaWriter->AddFrame(output);
  }

  pMediaReader->Close();
  pMediaWriter->CloseVideo();
}
