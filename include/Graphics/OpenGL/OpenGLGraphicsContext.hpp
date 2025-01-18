#pragma once

#include "Base/Types.hpp"
#include "Core/ApplicationContext.hpp"
#include "Graphics/GraphicsContext.hpp"
#include "Graphics/Handles.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"

namespace Krys::Graphics::OpenGL
{
  class OpenGLGraphicsContext : public GraphicsContext
  {
  public:
    OpenGLGraphicsContext() noexcept = default;
    ~OpenGLGraphicsContext() noexcept override;

    void SetClearColor(const Vec3 &rgb) noexcept override;
    void SetClearColor(const Vec4 &rgba) noexcept override;

    VertexBufferHandle CreateVertexBuffer(uint32 size) noexcept override;

    void Clear() noexcept override;
  };
}