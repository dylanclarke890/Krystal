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

  class Shader
  {
  public:
    virtual ~Shader() noexcept = default;

    /// @brief Gets the stage this shader is for.
    ShaderStage GetStage() const noexcept;

    /// @brief Gets the handle of the shader.
    ShaderHandle GetHandle() const noexcept;

  protected:
    /// @brief Constructs a shader.
    /// @param stage The stage of the shader.
    explicit Shader(ShaderHandle handle, ShaderStage stage) noexcept;

    ShaderHandle _handle;
    ShaderStage _stage;
  };
}