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
      _location =
        ::glGetProgramResourceLocation(static_cast<GLuint>(_program.Id()), GL_UNIFORM, name.c_str());
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
        ::glProgramUniform1i(_program.Id(), _location, _value);
      else if constexpr (std::is_same_v<uniform_t, int32>)
        ::glProgramUniform1i(_program.Id(), _location, _value);
      else if constexpr (std::is_same_v<uniform_t, List<int32>>)
        ::glProgramUniform1iv(_program.Id(), _location, _value.size(), _value.data());
      else if constexpr (std::is_same_v<uniform_t, float32>)
        ::glProgramUniform1f(_program.Id(), _location, _value);
      else if constexpr (std::is_same_v<uniform_t, List<float32>>)
        ::glProgramUniform1fv(_program.Id(), _location, _value.size(), _value.data());
      else if constexpr (std::is_same_v<uniform_t, Vec2>)
        ::glProgramUniform2f(_program.Id(), _location, _value.x, _value.y);
      else if constexpr (std::is_same_v<uniform_t, List<Vec2>>)
        ::glProgramUniform2fv(_program.Id(), _location, _value.size(), &_value[0].x);
      else if constexpr (std::is_same_v<uniform_t, Vec3>)
        ::glProgramUniform3f(_program.Id(), _location, _value.x, _value.y, _value.z);
      else if constexpr (std::is_same_v<uniform_t, List<Vec3>>)
        ::glProgramUniform3fv(_program.Id(), _location, _value.size(), &_value[0].x);
      else if constexpr (std::is_same_v<uniform_t, Vec4>)
        ::glProgramUniform4f(_program.Id(), _location, _value.x, _value.y, _value.z, _value.w);
      else if constexpr (std::is_same_v<uniform_t, List<Vec4>>)
        ::glProgramUniform4fv(_program.Id(), _location, _value.size(), &_value[0].x);
      else if constexpr (std::is_same_v<uniform_t, Mat2>)
        ::glProgramUniformMatrix2fv(_program.Id(), _location, 1, GL_FALSE, &_value[0][0]);
      else if constexpr (std::is_same_v<uniform_t, List<Mat2>>)
        ::glProgramUniformMatrix2fv(_program.Id(), _location, _value.size(), GL_FALSE, &_value[0][0][0]);
      else if constexpr (std::is_same_v<uniform_t, Mat3>)
        ::glProgramUniformMatrix3fv(_program.Id(), _location, 1, GL_FALSE, &_value[0][0]);
      else if constexpr (std::is_same_v<uniform_t, List<Mat3>>)
        ::glProgramUniformMatrix3fv(_program.Id(), _location, _value.size(), GL_FALSE, &_value[0][0][0]);
      else if constexpr (std::is_same_v<uniform_t, Mat4>)
        ::glProgramUniformMatrix4fv(_program.Id(), _location, 1, GL_FALSE, &_value[0][0]);
      else if constexpr (std::is_same_v<uniform_t, List<Mat4>>)
        ::glProgramUniformMatrix4fv(_program.Id(), _location, _value.size(), GL_FALSE, &_value[0][0][0]);
      else
        KRYS_ASSERT(false, "Unsupported uniform type.");
    }

  private:
    PipelineHandle _program;

    GLint _location;
    uniform_t _value;
  };
}