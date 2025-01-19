#pragma once

#include "Base/Types.hpp"
#include "Core/ApplicationContext.hpp"
#include "Graphics/GraphicsContext.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/PrimitiveType.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"

namespace Krys::Gfx::OpenGL
{
  class OpenGLGraphicsContext : public GraphicsContext
  {
  public:
    OpenGLGraphicsContext() noexcept;
    ~OpenGLGraphicsContext() noexcept override;

    void Init() noexcept override;

    void DrawArrays(PrimitiveType type, uint32 count) noexcept override;
    void DrawElements(PrimitiveType type, uint32 count) noexcept override;

    void SetClearColor(const Vec3 &rgb) noexcept override;
    void SetClearColor(const Vec4 &rgba) noexcept override;

    VertexBufferHandle CreateVertexBuffer(uint32 size) noexcept override;
    IndexBufferHandle CreateIndexBuffer(uint32 size) noexcept override;

    ShaderHandle CreateShader(const ShaderDescription &description) noexcept override;
    PipelineHandle CreatePipeline() noexcept override;

    void Clear() noexcept override;
  };
}