#include "krys-pch.h"
#include "Krystal/Renderer/VertexArray.h"

#include "Krystal/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Krys
{
  Ref<VertexArray> VertexArray::Create()
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
        return CreateScope<OpenGLVertexArray>();
      }
    }

    KRYS_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }
}