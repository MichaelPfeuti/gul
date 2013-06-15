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

#include "GLContext.h"
#include "Log.h"
#include "Assert.h"
#include <cstdlib>

static void errorCallback(int error, const char* description)
{
  GUL_LOG_ERROR("GLFW Error %d: %s!", error, description);
}

static void framebufferResizeCallback(GLFWwindow*, int width, int height)
{
    glViewport(0, 0, width, height);
}

gul::GLContext::GLContext(void)
  : m_pWindow(nullptr)
{
}

gul::GLContext::~GLContext(void)
{
  if(m_pWindow != nullptr)
  {
    glDeleteVertexArrays(1, &m_vertexArray);
    glfwDestroyWindow(m_pWindow);
  }
}

bool gul::GLContext::InitializeOffscreen(void)
{
  glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
  return Initialize(1,1,"");
}

bool gul::GLContext::Initialize(int width, int height, const gul::String& title)
{
  if(!initGLFW())
  {
    return false;
  }

  setDefaultWindowHints();

  m_pWindow = glfwCreateWindow(width, height, title.GetData(), nullptr, nullptr);
  if(m_pWindow == nullptr)
  {
    GUL_LOG_ERROR("GLFW could not create window!");
    return false;
  }

  glfwSetFramebufferSizeCallback(m_pWindow, framebufferResizeCallback);
  MakeCurrent();
  if(!initGLEW())
  {
    return false;
  }
  createVertexArray();
  return true;
}

bool gul::GLContext::InitializeFullscreen(const gul::String& title)
{
  if(!initGLFW())
  {
    return false;
  }

  setDefaultWindowHints();

  GLFWmonitor* monitor = glfwGetPrimaryMonitor();
  const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);
  m_pWindow = glfwCreateWindow(videoMode->width, videoMode->height, title.GetData(), monitor, nullptr);
  if(m_pWindow == nullptr)
  {
    GUL_LOG_ERROR("GLFW could not create window!");
    return false;
  }

  MakeCurrent();
  if(!initGLEW())
  {
    return false;
  }
  createVertexArray();
  return true;
}

void gul::GLContext::MakeCurrent(void)
{
  glfwMakeContextCurrent(m_pWindow);
}

void gul::GLContext::SwapBuffers(void)
{
  glfwSwapBuffers(m_pWindow);
  glfwPollEvents();
}

void gul::GLContext::SwapBuffersAndWaitForInput(void)
{
  glfwSwapBuffers(m_pWindow);
  glfwWaitEvents();
}

bool gul::GLContext::initGLFW(void)
{
  static bool s_isGLFWInit = false;

  if(!s_isGLFWInit)
  {
    if(glfwInit() == GL_TRUE)
    {
      glfwSetErrorCallback(errorCallback);
      atexit(&glfwTerminate);
      s_isGLFWInit = true;
    }
    else
    {
      GUL_LOG_ERROR("GLFW could not be initialized!");
      return false;
    }
  }

  return true;
}

bool gul::GLContext::initGLEW(void)
{
  static bool s_isGLEWInit = false;

  if(!s_isGLEWInit)
  {
    // Needed for core profile
    glewExperimental = true;
    GLenum glewError = glewInit();
    if(glewError != GLEW_OK)
    {
      GUL_LOG_ERROR("GLEW\n could not be initialized (%s)!", glewGetErrorString(glewError));
      return false;
    }
  }

  return true;
}

void gul::GLContext::createVertexArray(void)
{
  glGenVertexArrays(1, &m_vertexArray);
  glBindVertexArray(m_vertexArray);
}

void gul::GLContext::setDefaultWindowHints(void)
{
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
