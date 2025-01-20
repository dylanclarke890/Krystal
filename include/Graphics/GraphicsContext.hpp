#pragma once

#include "Base/Pointers.hpp"
#include "Graphics/Buffer.hpp"
#include "Graphics/Colour.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/Pipeline.hpp"
#include "Graphics/PrimitiveType.hpp"
#include "Graphics/Shader.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"

namespace Krys::Gfx
{
  class GraphicsContext
  {
  public:
    virtual ~GraphicsContext() noexcept;

    virtual void Init() noexcept = 0;

    virtual void DrawArrays(PrimitiveType type, uint32 count) noexcept = 0;
    virtual void DrawElements(PrimitiveType type, uint32 count) noexcept = 0;

    virtual void SetClearColour(const Colour &colour) noexcept = 0;
    virtual void Clear() noexcept = 0;

    virtual VertexBufferHandle CreateVertexBuffer(uint32 size) noexcept = 0;
    virtual IndexBufferHandle CreateIndexBuffer(uint32 size) noexcept = 0;
    // virtual UniformBufferHandle CreateUniformBuffer(uint32 size) noexcept = 0;
    virtual ShaderHandle CreateShader(const ShaderDescription &description) noexcept = 0;
    virtual PipelineHandle CreatePipeline() noexcept = 0;

    void DestroyVertexBuffer(VertexBufferHandle handle) noexcept;
    void DestroyIndexBuffer(IndexBufferHandle handle) noexcept;
    // void DestroyUniformBuffer(UniformHandle handle) noexcept;
    void DestroyShader(ShaderHandle handle) noexcept;
    void DestroyPipeline(PipelineHandle handle) noexcept;

    VertexBuffer &GetVertexBuffer(VertexBufferHandle handle) noexcept;
    IndexBuffer &GetIndexBuffer(IndexBufferHandle handle) noexcept;
    UniformBuffer &GetUniformBuffer(UniformHandle handle) noexcept;
    Shader &GetShader(ShaderHandle handle) noexcept;
    Pipeline &GetPipeline(PipelineHandle handle) noexcept;

  protected:
    Colour _clearColour {0.0f, 0.0f, 0.0f, 1.0f};
    Map<ShaderHandle, Unique<Shader>, ShaderHandle::Hash> _shaders {};
    Map<PipelineHandle, Unique<Pipeline>, PipelineHandle::Hash> _pipelines {};
    Map<VertexBufferHandle, Unique<VertexBuffer>, VertexBufferHandle::Hash> _vertexBuffers {};
    Map<IndexBufferHandle, Unique<IndexBuffer>, IndexBufferHandle::Hash> _indexBuffers {};
    Map<UniformHandle, Unique<UniformBuffer>, UniformHandle::Hash> _uniformBuffers {};
  };
}