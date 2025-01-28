#include "Core/Debug/Macros.hpp"
#include "Core/Window.hpp"
#include "Graphics/Renderer.hpp"

namespace Krys::Gfx
{
  GraphicsContext::~GraphicsContext() noexcept
  {
    _vertexBuffers.clear();
    _indexBuffers.clear();
    _uniformBuffers.clear();
    _shaders.clear();
  }

  ProgramHandle GraphicsContext::CreateProgram(ShaderHandle vertexHandle, ShaderHandle fragmentHandle) noexcept
  {
    auto handle = _programHandles.Next();
    auto program = CreateProgramImpl(handle, vertexHandle, fragmentHandle);
    _programs[handle] = std::move(program);
    return handle;
  }

  Program *GraphicsContext::GetProgram(ProgramHandle handle) noexcept
  {
    KRYS_ASSERT(handle.IsValid(), "Invalid program handle");
    auto it = _programs.find(handle);

    if (it == _programs.end())
      return nullptr;

    return it->second.get();
  }

  bool GraphicsContext::DestroyProgram(ProgramHandle handle) noexcept
  {
    KRYS_ASSERT(handle.IsValid(), "Invalid Program handle");
    auto it = _programs.find(handle);

    if (it == _programs.end())
      return false;

    _programs.erase(it);
    _programHandles.Recycle(handle);

    return true;
  }

  ShaderHandle GraphicsContext::CreateShader(ShaderStage stage, const string &source) noexcept
  {
    auto handle = _shaderHandles.Next();
    auto shader = CreateShaderImpl(handle, stage, source);
    _shaders[handle] = std::move(shader);
    return handle;
  }

  Shader *GraphicsContext::GetShader(ShaderHandle handle) noexcept
  {
    KRYS_ASSERT(handle.IsValid(), "Invalid shader handle");
    auto it = _shaders.find(handle);

    if (it == _shaders.end())
      return nullptr;

    return it->second.get();
  }

  bool GraphicsContext::DestroyShader(ShaderHandle handle) noexcept
  {
    KRYS_ASSERT(handle.IsValid(), "Invalid shader handle");
    auto it = _shaders.find(handle);

    if (it == _shaders.end())
      return false;

    _shaders.erase(it);
    _shaderHandles.Recycle(handle);

    return true;
  }

  VertexBufferHandle GraphicsContext::CreateVertexBuffer(uint32 size) noexcept
  {
    auto handle = _vertexBufferHandles.Next();
    auto buffer = CreateVertexBufferImpl(handle, size);
    _vertexBuffers[handle] = std::move(buffer);
    return handle;
  }

  VertexBuffer *GraphicsContext::GetVertexBuffer(VertexBufferHandle handle) noexcept
  {
    KRYS_ASSERT(handle.IsValid(), "Invalid vertex buffer handle");
    auto it = _vertexBuffers.find(handle);

    if (it == _vertexBuffers.end())
      return nullptr;

    return it->second.get();
  }

  bool GraphicsContext::DestroyVertexBuffer(VertexBufferHandle handle) noexcept
  {
    KRYS_ASSERT(handle.IsValid(), "Invalid vertex buffer handle");
    auto it = _vertexBuffers.find(handle);

    if (it == _vertexBuffers.end())
      return false;

    _vertexBuffers.erase(it);
    _vertexBufferHandles.Recycle(handle);

    return true;
  }

  IndexBufferHandle GraphicsContext::CreateIndexBuffer(uint32 size) noexcept
  {
    auto handle = _indexBufferHandles.Next();
    auto buffer = CreateIndexBufferImpl(handle, size);
    _indexBuffers[handle] = std::move(buffer);
    return handle;
  }

  IndexBuffer *GraphicsContext::GetIndexBuffer(IndexBufferHandle handle) noexcept
  {
    KRYS_ASSERT(handle.IsValid(), "Invalid index buffer handle");
    auto it = _indexBuffers.find(handle);

    if (it == _indexBuffers.end())
      return nullptr;

    return it->second.get();
  }

  bool GraphicsContext::DestroyIndexBuffer(IndexBufferHandle handle) noexcept
  {
    KRYS_ASSERT(handle.IsValid(), "Invalid index buffer handle");
    auto it = _indexBuffers.find(handle);

    if (it == _indexBuffers.end())
      return false;

    _indexBuffers.erase(it);
    _indexBufferHandles.Recycle(handle);

    return true;
  }

  UniformBuffer *GraphicsContext::GetUniformBuffer(UniformHandle handle) noexcept
  {
    KRYS_ASSERT(handle.IsValid(), "Invalid uniform buffer handle");
    auto it = _uniformBuffers.find(handle);

    if (it == _uniformBuffers.end())
      return nullptr;

    return it->second.get();
  }

  void GraphicsContext::SetViewport(uint32 width, uint32 height) noexcept
  {
    SetViewport({0u, 0u, width, height});
  }

  void GraphicsContext::SetViewport(uint32 x, uint32 y, uint32 width, uint32 height) noexcept
  {
    SetViewport({x, y, width, height});
  }

  void GraphicsContext::SetViewport(const Window &window) noexcept
  {
    SetViewport({0u, 0u, window.GetWidth(), window.GetHeight()});
  }
}