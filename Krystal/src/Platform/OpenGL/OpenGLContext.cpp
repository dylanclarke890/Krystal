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

    KRYS_CORE_INFO("OpenGL Initialised:");
    KRYS_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
    KRYS_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
    KRYS_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
  }

  void OpenGLContext::SwapBuffers()
  {
    glfwSwapBuffers(m_WindowHandle);
  }
}