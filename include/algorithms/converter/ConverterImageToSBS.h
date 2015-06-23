#pragma once
#ifndef _GUL_ALGORITHMS_CONVERTER_IMAGE_TO_SBS_H_
#define _GUL_ALGORITHMS_CONVERTER_IMAGE_TO_SBS_H_
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

#include "Converter.h"
#include "Image.h"

namespace gul
{
  class GUL_EXPORT ConverterImageToSBS : public Converter
  {

    public:
      ConverterImageToSBS(void);

      virtual ~ConverterImageToSBS(void);

      void SetParameter(const gul::Image& leftImage, const gul::Image& rightImage);

      virtual void Execute(void);

      gul::Image GetResult(void) const;

      static gul::Image Execute(const gul::Image& leftImage, const Image& rightImage);

    private:
      gul::Image m_leftImage;
      gul::Image m_rightImage;
      gul::Image m_sbsImage;
  };

}

#endif
