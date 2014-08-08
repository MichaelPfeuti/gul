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

#include "Traits.h"

#ifdef LIBGLEW_FOUND
#  include <GL/glew.h>
#endif
#ifdef LIBOPENCL_FOUND
#  include <CL/cl.h>
#endif

SPECIALIZE_TRAITS(double)
SPECIALIZE_TRAITS(short)
SPECIALIZE_TRAITS(unsigned short)
SPECIALIZE_TRAITS(int)
SPECIALIZE_TRAITS(unsigned int)
SPECIALIZE_TRAITS(long)
SPECIALIZE_TRAITS(unsigned long)
SPECIALIZE_TRAITS(long long)
SPECIALIZE_TRAITS(unsigned long long)
SPECIALIZE_TRAITS(char)
SPECIALIZE_TRAITS(bool)
SPECIALIZE_TRAITS(void)
SPECIALIZE_TRAITS(gul::String)


namespace gul
{
  template<>
  class Traits<unsigned char>
  {
    public:
      static String GetName()
      {
        return gul::String("unsigned char");
      }
#ifdef LIBOPENGL_FOUND
      static GLenum GetGLType()
      {
        return GL_UNSIGNED_BYTE;
      }
#endif
#ifdef LIBOPENCL_FOUND
      static cl_channel_type GetCLType()
      {
        return CL_UNORM_INT8;
      }
#endif
  };
}

namespace gul
{
  template<>
  class Traits<float>
  {
    public:
      static String GetName()
      {
        return gul::String("float");
      }
#ifdef LIBOPENGL_FOUND
      static GLenum GetGLType()
      {
        return GL_FLOAT;
      }
#endif
#ifdef LIBOPENCL_FOUND
      static cl_channel_type GetCLType()
      {
        return CL_FLOAT;
      }
#endif
  };
}
