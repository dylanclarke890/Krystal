#include "krys-pch.h"
#include "Krystal/Renderer/GraphicsContext.h"

#include "Krystal/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Krys
{
  Scope<GraphicsContext> GraphicsContext::Create(void* window)
  {
    switch (Renderer::GetAPI())
    {
      case RendererAPI::API::None:
      {
        KRYS_CORE_ASSERT(false, "RendererAPI::None is not supported.");
        return nullptr;
      }
      case RendererAPI::API::OpenGL:
      {
        return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
      }
    }

    KRYS_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }
}
