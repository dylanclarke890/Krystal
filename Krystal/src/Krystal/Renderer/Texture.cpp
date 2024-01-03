#include "krys-pch.h"
#include "Krystal/Renderer/Texture.h"

#include "Krystal/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Krys
{
  Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
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
        return CreateRef<OpenGLTexture2D>(width, height);
      }
    }

    KRYS_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }

  Ref<Texture2D> Texture2D::Create(const std::string& path)
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
        return CreateRef<OpenGLTexture2D>(path);
      }
    }

    KRYS_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }
}