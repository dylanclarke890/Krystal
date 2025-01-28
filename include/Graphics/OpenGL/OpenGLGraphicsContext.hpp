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

    void SetViewport(const Vec4ui &viewport) noexcept override;

    void DrawArrays(PrimitiveType type, uint32 count) noexcept override;
    void DrawElements(PrimitiveType type, uint32 count) noexcept override;

    void Clear(ClearBuffer flags) noexcept override;
    void SetClearColour(const Colour &colour) noexcept override;

  protected:
    Unique<Program> CreateProgramImpl(ProgramHandle handle, ShaderHandle vertexShader, ShaderHandle fragmentShader) noexcept override;

    Unique<Shader> CreateShaderImpl(ShaderHandle handle, ShaderStage stage,
                                    const string &source) noexcept override;

    Unique<VertexBuffer> CreateVertexBufferImpl(VertexBufferHandle handle, uint32 size) noexcept override;

    Unique<IndexBuffer> CreateIndexBufferImpl(IndexBufferHandle handle, uint32 size) noexcept override;
  };
}