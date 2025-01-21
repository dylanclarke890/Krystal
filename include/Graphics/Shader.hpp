#pragma once

#include "Base/Types.hpp"
#include "Graphics/Handles.hpp"

namespace Krys::Gfx
{
  enum class ShaderStage
  {
    Vertex,
    Fragment
  };

  struct ShaderDescriptor
  {
    ShaderStage Stage;
    string Source;
  };

  class Shader
  {
  public:
    Shader() = delete;
    virtual ~Shader() noexcept = default;

    ShaderStage GetStage() const noexcept;
    ShaderHandle GetHandle() const noexcept;

  protected:
    explicit Shader(const ShaderDescriptor &description) noexcept;

    ShaderStage _stage;
    ShaderHandle _handle;
  };
}