#pragma once
#ifndef _GUL_CONTEXT_GL_PROGRAM_H_
#define _GUL_CONTEXT_GL_PROGRAM_H_
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

#include "gul_export.h"

#include <GL/glew.h>

namespace gul {
  class String;
}

namespace gul
{

  class GUL_EXPORT GLProgram
  {
    public:
      GLProgram(void);
      ~GLProgram(void);

      bool Initialize(void);
      bool Link(void);
      bool CompileShader(GLenum shaderType, const gul::String& sourceCode);
      bool Use(void);

      GLuint GetGLId(void);

    private:
      bool compileShader(const GLuint& shader, const gul::String& sourceCode);

    private:
      GLuint m_program;
      GLuint m_shaderVertex;
      GLuint m_shaderFragment;
      GLuint m_shaderGeometry;
  };

}

#endif
