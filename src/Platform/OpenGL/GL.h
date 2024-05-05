#pragma once

#pragma warning(push)
#pragma warning(disable : 4005)
#include <gl.h>
#include <wgl.h>
#pragma warning(pop)

struct ARBExtensions
{
  PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = nullptr;
  PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;
};

namespace Krys
{
  typedef GLuint GLRendererId;
}