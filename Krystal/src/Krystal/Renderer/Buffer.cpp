#include "krys-pch.h"
#include "Krystal/Renderer/Buffer.h"
#include "Krystal/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Krys
{
  Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
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
        return CreateScope<OpenGLVertexBuffer>(size);
      }
    }

    KRYS_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }

  Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
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
        return CreateScope<OpenGLVertexBuffer>(vertices, size);
      }
    }

    KRYS_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }

  Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
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
        return CreateScope<OpenGLIndexBuffer>(indices, count);
      }
    }

    KRYS_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }
}