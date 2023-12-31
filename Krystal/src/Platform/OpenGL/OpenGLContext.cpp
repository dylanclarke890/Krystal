#include "krys-pch.h"
#include "Platform/OpenGL/OpenGLContext.h"

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

    KRYS_CORE_INFO("Start Up - OpenGL Initialised:");
    KRYS_CORE_INFO("- Version: {0}", (const char*)glGetString(GL_VERSION));
    KRYS_CORE_INFO("- Vendor: {0}", (const char*)glGetString(GL_VENDOR));
    KRYS_CORE_INFO("- Renderer: {0}", (const char*)glGetString(GL_RENDERER));

#ifdef KRYS_ENABLE_ASSERTS
    int versionMajor, versionMinor;
    glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
    glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

    KRYS_CORE_ASSERT(versionMajor >= 4 && versionMinor >= 5, "Krystal requires at least OpenGL version 4.5!");
#endif
  }

  void OpenGLContext::SwapBuffers()
  {
    glfwSwapBuffers(m_WindowHandle);
  }
}