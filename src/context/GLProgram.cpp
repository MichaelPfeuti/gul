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

#include "GLProgram.h"
#include "Log.h"
#include "Assert.h"

gul::GLProgram::GLProgram(void)
  : m_program(0),
    m_shaderVertex(0),
    m_shaderFragment(0),
    m_shaderGeometry(0)
{
}

gul::GLProgram::~GLProgram(void)
{
  glUseProgram(0);
  glDeleteProgram(m_program);
  glDeleteShader(m_shaderVertex);
  glDeleteShader(m_shaderFragment);
  glDeleteShader(m_shaderGeometry);
}

bool gul::GLProgram::Initialize(void)
{
  m_program = glCreateProgram();
  return true;
}

bool gul::GLProgram::Link(void)
{
  if(glIsShader(m_shaderVertex))
    glAttachShader(m_program, m_shaderVertex);
  if(glIsShader(m_shaderFragment))
    glAttachShader(m_program, m_shaderFragment);
  if(glIsShader(m_shaderGeometry))
    glAttachShader(m_program, m_shaderGeometry);
  glLinkProgram(m_program);

  GLint linkStatus;
  GLint infoLogLength;

  glGetProgramiv(m_program, GL_LINK_STATUS, &linkStatus);
  glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLogLength);

  if(linkStatus != GL_TRUE && infoLogLength > 0)
  {
    GLchar errorMsg[infoLogLength+1];
    glGetProgramInfoLog(m_program, infoLogLength, nullptr, errorMsg);
    GUL_LOG_ERROR("OpenGL program could no be linked:");
    GUL_LOG_ERROR("------------------------------------\n%s", errorMsg);
    return false;
  }

  return true;
}

bool gul::GLProgram::Use(void)
{
  glUseProgram(m_program);
  return true;
}

GLuint gul::GLProgram::GetGLId(void)
{
  return m_program;
}

bool gul::GLProgram::CompileShader(GLenum shaderType, const gul::String& sourceCode)
{
  switch(shaderType) {
    case GL_VERTEX_SHADER:
      m_shaderVertex = glCreateShader(GL_VERTEX_SHADER);
      return compileShader(m_shaderVertex, sourceCode);
    case GL_FRAGMENT_SHADER:
      m_shaderFragment = glCreateShader(GL_FRAGMENT_SHADER);
      return compileShader(m_shaderFragment, sourceCode);
    case GL_GEOMETRY_SHADER:
      m_shaderGeometry = glCreateShader(GL_GEOMETRY_SHADER);
      return compileShader(m_shaderGeometry, sourceCode);
    default:
      GUL_FAIL("Unknown Shader Type");
      return false;
  }
}

bool gul::GLProgram::compileShader(const GLuint& shader, const gul::String& sourceCode)
{
  const GLchar* glCode = sourceCode.GetData();
  glShaderSource(shader, 1, &glCode , nullptr);
  glCompileShader(shader);

  GLint compileStatus;
  GLint infoLogLength;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
  if(compileStatus != GL_TRUE && infoLogLength > 0)
  {
    GLchar errorMsg[infoLogLength+1];
    glGetShaderInfoLog(shader, infoLogLength, nullptr, errorMsg);
    GUL_LOG_ERROR("OpenGL shader could no be compiled:");
    GUL_LOG_ERROR("------------------------------------\n%s", errorMsg);
    return false;
  }

  return true;
}
