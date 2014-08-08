#pragma once
#ifndef _GUL_CONTEXT_GL_CONTEXT_H_
#define _GUL_CONTEXT_GL_CONTEXT_H_
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
#include <GLFW/glfw3.h>

namespace gul
{
  class String;
}

namespace gul
{
  class GUL_EXPORT GLContext
  {
    public:
      GLContext(void);
      ~GLContext(void);

      bool InitializeOffscreen(void);
      bool Initialize(int width, int height, const gul::String& title);
      bool InitializeFullscreen(const gul::String& title);
      void MakeCurrent(void);
      void SwapBuffers(void);
      void SwapBuffersAndWaitForInput(void);

    private:
      bool initGLFW(void);
      bool initGLEW(void);
      void setDefaultWindowHints(void);
      void createVertexArray(void);

    private:
      GLFWwindow* m_pWindow;
      GLuint m_vertexArray;
  };

}

#endif
