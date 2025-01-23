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

  // TODO: consider getting rid of this struct
  struct ShaderDescriptor
  {
    ShaderStage Stage;
    string Source;
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
    /// @param description The description of the shader.
    explicit Shader(const ShaderDescriptor &description) noexcept;

    ShaderStage _stage;
    ShaderHandle _handle;
  };
}