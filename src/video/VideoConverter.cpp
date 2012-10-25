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

#include "VideoConverter.h"
#include "VideoFrameManipulator.h"
#include "VideoLoader.h"
#include "VideoSaver.h"
#include "VideoFrame.h"
#include "Misc.h"

gul::VideoConverter::VideoConverter(const gul::File& rInputVideo)
  : pVideoLoader(new gul::VideoLoader(rInputVideo)),
    pVideoSaver(nullptr),
    pManipulator(nullptr)
{

}

void gul::VideoConverter::Init(const gul::File& rOutputVideo, gul::VideoFrameManipulator& rManipulator)
{
  GUL_DELETE(pManipulator);
  pManipulator = &rManipulator;

  pVideoLoader->OpenVideo();
  GUL_DELETE(pVideoSaver);
  pVideoSaver = new gul::VideoSaver(rOutputVideo);
  pVideoSaver->setSize(rManipulator.GetResultWidth(pVideoLoader->GetWidth()),
                       rManipulator.GetResultHeight(pVideoLoader->GetHeight()));
  pVideoSaver->openVideo(*pVideoLoader->pFormatCtx);
}

void gul::VideoConverter::Execute(void)
{
  gul::VideoFrame input;
  gul::VideoFrame output;

  pVideoLoader->allocateVideoFrame(input);

  // copy video
  AVPacket* pPacket = pVideoLoader->getNextPacket();
  while(pPacket != nullptr)
  {
    if(pVideoLoader->isVideoPacket(*pPacket))
    {
      if(pVideoLoader->decodeVideoPacket(*pPacket, input))
      {
        pManipulator->Execute(input, output);
        output.SetPresentationTime(input.GetPresentationTime());
        pVideoSaver->AddFrame(output);
      }
    }
    else
    {
      pVideoSaver->writePacket(*pPacket);
    }
    pPacket = pVideoLoader->getNextPacket();
  }

  while(pVideoLoader->decodeRemaining(input))
  {
    pManipulator->Execute(input, output);
    output.SetPresentationTime(input.GetPresentationTime());
    pVideoSaver->AddFrame(output);
  }

  pVideoLoader->CloseVideo();
  pVideoSaver->CloseVideo();
}
