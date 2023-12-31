#include "krys-pch.h"
#include "Krystal/Renderer/Texture.h"

#include "Krystal/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Krys
{
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
        return std::make_shared<OpenGLTexture2D>(path);
      }
    }

    KRYS_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }
}