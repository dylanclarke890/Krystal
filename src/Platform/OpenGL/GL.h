#pragma once

#pragma warning(push)
#pragma warning(disable : 4005)
#include <glad/gl.h>
#include <glad/wgl.h>
#pragma warning(pop)

struct ARBExtensions
{
  PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = nullptr;
  PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;
};
