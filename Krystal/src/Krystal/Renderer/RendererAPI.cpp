#include "krys-pch.h"

#include "Krystal/Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Krys
{
  RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

  Scope<RendererAPI> RendererAPI::Create()
  {
    switch (s_API)
    {
      case RendererAPI::API::None:
      {
        KRYS_CORE_ASSERT(false, "RendererAPI::None is not supported.");
        return nullptr;
      }
      case RendererAPI::API::OpenGL:
      {
        return CreateScope<OpenGLRendererAPI>();
      }
    }

    KRYS_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }
}