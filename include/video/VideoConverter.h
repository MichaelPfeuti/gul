#pragma once
#ifndef _GUL_VIDEO_VIDEO_CONVERTER_H_
#define _GUL_VIDEO_VIDEO_CONVERTER_H_
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

namespace gul
{
  class File;
  class VideoFrameManipulator;
  class VideoLoader;
  class VideoSaver;
}

namespace gul
{

  // works only for mkv -> mkv conversion at the moment
  class VideoConverter
  {
    public:
      VideoConverter(const gul::File& rInputVideo);

      void Init(const File& rOutputVideo, gul::VideoFrameManipulator& rManipulator);
      void Execute(void);

    private:
      gul::VideoLoader* pVideoLoader;
      gul::VideoSaver* pVideoSaver;
      gul::VideoFrameManipulator* pManipulator;
  };
}

#endif
