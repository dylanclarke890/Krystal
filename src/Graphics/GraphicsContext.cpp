#include "Core/Debug/Macros.hpp"
#include "Graphics/Renderer.hpp"

namespace Krys::Graphics
{
  GraphicsContext::~GraphicsContext() noexcept
  {
    _vertexBuffers.clear();
    _indexBuffers.clear();
    _uniformBuffers.clear();
    _shaders.clear();
  }

  void GraphicsContext::DestroyVertexBuffer(VertexBufferHandle handle) noexcept
  {
    KRYS_ASSERT(handle.Id() != VertexBufferHandle::InvalidHandle && _vertexBuffers.contains(handle),
                "Invalid vertex buffer handle");
    _vertexBuffers.erase(handle);
  }

  void GraphicsContext::DestroyShader(ShaderHandle handle) noexcept
  {
    KRYS_ASSERT(handle.Id() != ShaderHandle::InvalidHandle && _shaders.contains(handle),
                "Invalid shader handle");
    _shaders.erase(handle);
  }

  void GraphicsContext::DestroyPipeline(PipelineHandle handle) noexcept
  {
    KRYS_ASSERT(handle.Id() != PipelineHandle::InvalidHandle && _pipelines.contains(handle),
                "Invalid pipeline handle");
    _pipelines.erase(handle);
  }

  VertexBuffer &GraphicsContext::GetVertexBuffer(VertexBufferHandle handle) noexcept
  {
    KRYS_ASSERT(handle.Id() != VertexBufferHandle::InvalidHandle && _vertexBuffers.contains(handle),
                "Invalid vertex buffer handle");
    return *_vertexBuffers.at(handle);
  }

  IndexBuffer &GraphicsContext::GetIndexBuffer(IndexBufferHandle handle) noexcept
  {
    KRYS_ASSERT(handle.Id() != IndexBufferHandle::InvalidHandle && _indexBuffers.contains(handle),
                "Invalid index buffer handle");
    return *_indexBuffers.at(handle);
  }

  UniformBuffer &GraphicsContext::GetUniformBuffer(UniformHandle handle) noexcept
  {
    KRYS_ASSERT(handle.Id() != UniformHandle::InvalidHandle && _uniformBuffers.contains(handle),
                "Invalid uniform buffer handle");
    return *_uniformBuffers.at(handle);
  }

  Shader &GraphicsContext::GetShader(ShaderHandle handle) noexcept
  {
    KRYS_ASSERT(handle.Id() != ShaderHandle::InvalidHandle && _shaders.contains(handle),
                "Invalid shader handle");
    return *_shaders.at(handle);
  }

  Pipeline &GraphicsContext::GetPipeline(PipelineHandle handle) noexcept
  {
    KRYS_ASSERT(handle.Id() != PipelineHandle::InvalidHandle && _pipelines.contains(handle),
                "Invalid pipeline handle");
    return *_pipelines.at(handle);
  }
}