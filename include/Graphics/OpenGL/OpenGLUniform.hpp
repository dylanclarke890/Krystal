#pragma once

#include "Base/Attributes.hpp"
#include "Base/Types.hpp"
#include "Core/Logger.hpp"
#include "Graphics/Handles.hpp"
#include "MTL/Matrices/Mat2x2.hpp"
#include "MTL/Matrices/Mat3x3.hpp"
#include "MTL/Matrices/Mat4x4.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"

#include <glad/gl.h>

namespace Krys::Gfx::OpenGL
{
  template <typename UniformT>
  class OpenGLUniform
  {
    using uniform_t = UniformT;

  public:
    OpenGLUniform() noexcept
        : _location(-1), _value()
    {
    }

    OpenGLUniform(PipelineHandle program, const string &name) noexcept
        : _program(program), _location(-1), _value()
    {
      _location = glGetUniformLocation(static_cast<GLuint>(_program.Id()), name.c_str());
      if (_location == -1)
        Logger::Warn("Uniform '{0}' does not exist. (Program {1})", name, _program.Id());
    }

    ~OpenGLUniform() noexcept = default;

    void SetValue(const uniform_t &value) noexcept
    {
      if (_location == -1)
      {
        Logger::Warn("Tried setting a value for an invalid uniform location. (Program {0})", _program.Id());
        return;
      }

      // if 'uniform_t' supports 'operator==' then we can compare the values
      if constexpr (requires { _value == value; })
      {
        if (_value == value)
          return;
      }
      _value = value;
      UploadValue();
    }

    NO_DISCARD const uniform_t &GetValue() const noexcept
    {
      return _value;
    }

  private:
    void UploadValue() const noexcept
    {
      if constexpr (std::is_same_v<uniform_t, bool>)
        glUniform1i(_location, _value);
      else if constexpr (std::is_same_v<uniform_t, int32>)
        glUniform1i(_location, _value);
      else if constexpr (std::is_same_v<uniform_t, List<int32>>)
        glUniform1iv(_location, _value.size(), _value.data());
      else if constexpr (std::is_same_v<uniform_t, float32>)
        glUniform1f(_location, _value);
      else if constexpr (std::is_same_v<uniform_t, List<float32>>)
        glUniform1fv(_location, _value.size(), _value.data());
      else if constexpr (std::is_same_v<uniform_t, Vec2>)
        glUniform2f(_location, _value.x, _value.y);
      else if constexpr (std::is_same_v<uniform_t, List<Vec2>>)
        glUniform2fv(_location, _value.size(), &_value[0].x);
      else if constexpr (std::is_same_v<uniform_t, Vec3>)
        glUniform3f(_location, _value.x, _value.y, _value.z);
      else if constexpr (std::is_same_v<uniform_t, List<Vec3>>)
        glUniform3fv(_location, _value.size(), &_value[0].x);
      else if constexpr (std::is_same_v<uniform_t, Vec4>)
        glUniform4f(_location, _value.x, _value.y, _value.z, _value.w);
      else if constexpr (std::is_same_v<uniform_t, List<Vec4>>)
        glUniform4fv(_location, _value.size(), &_value[0].x);
      else if constexpr (std::is_same_v<uniform_t, Mat2>)
        glUniformMatrix2fv(_location, 1, GL_FALSE, &_value[0][0]);
      else if constexpr (std::is_same_v<uniform_t, List<Mat2>>)
        glUniformMatrix2fv(_location, _value.size(), GL_FALSE, &_value[0][0][0]);
      else if constexpr (std::is_same_v<uniform_t, Mat3>)
        glUniformMatrix3fv(_location, 1, GL_FALSE, &_value[0][0]);
      else if constexpr (std::is_same_v<uniform_t, List<Mat3>>)
        glUniformMatrix3fv(_location, _value.size(), GL_FALSE, &_value[0][0][0]);
      else if constexpr (std::is_same_v<uniform_t, Mat4>)
        glUniformMatrix4fv(_location, 1, GL_FALSE, &_value[0][0]);
      else if constexpr (std::is_same_v<uniform_t, List<Mat4>>)
        glUniformMatrix4fv(_location, _value.size(), GL_FALSE, &_value[0][0][0]);
      else
        KRYS_ASSERT(false, "Unsupported uniform type.");
    }

  private:
    PipelineHandle _program;

    GLint _location;
    uniform_t _value;
  };
}