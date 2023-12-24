#include "krys-pch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Krys
{
  OpenGLContext::OpenGLContext(GLFWwindow* windowHandle): m_WindowHandle(windowHandle) 
  {
    KRYS_CORE_ASSERT(windowHandle, "Window handle is null!");
  }

  void OpenGLContext::Init()
  {
    glfwMakeContextCurrent(m_WindowHandle);
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    KRYS_CORE_ASSERT(status, "Failed to initialise glad!");
  }

  void OpenGLContext::SwapBuffers()
  {
    glfwSwapBuffers(m_WindowHandle);
  }
}