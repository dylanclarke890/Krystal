#pragma once

#include "Base/Pointers.hpp"
#include "Graphics/Buffer.hpp"
#include "Graphics/Handles.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"

namespace Krys::Graphics
{
  class GraphicsContext
  {
  public:
    virtual ~GraphicsContext() noexcept;

    virtual void SetClearColor(const Vec4 &rgba) noexcept = 0;
    virtual void SetClearColor(const Vec3 &rgb) noexcept = 0;
    virtual void Clear() noexcept = 0;

    virtual VertexBufferHandle CreateVertexBuffer(uint32 size) noexcept = 0;
    // virtual IndexBufferHandle CreateIndexBuffer(uint32 size) noexcept = 0;
    // virtual UniformBufferHandle CreateUniformBuffer(uint32 size) noexcept = 0;

    void DestroyVertexBuffer(VertexBufferHandle handle) noexcept;
    // void DestroyIndexBuffer(IndexBufferHandle handle) noexcept;
    // void DestroyUniformBuffer(UniformHandle handle) noexcept;

    VertexBuffer &GetVertexBuffer(VertexBufferHandle handle) noexcept;
    IndexBuffer &GetIndexBuffer(IndexBufferHandle handle) noexcept;
    UniformBuffer &GetUniformBuffer(UniformHandle handle) noexcept;

  protected:
    Vec4 _clearColor {0.0f, 0.0f, 0.0f, 1.0f};
    Map<VertexBufferHandle, Unique<VertexBuffer>, VertexBufferHandle::Hash> _vertexBuffers {};
    Map<IndexBufferHandle, Unique<IndexBuffer>, IndexBufferHandle::Hash> _indexBuffers {};
    Map<UniformHandle, Unique<UniformBuffer>, UniformHandle::Hash> _uniformBuffers {};
  };
}