#pragma once

#include "Base/Attributes.hpp"
#include "Base/Types.hpp"
#include "Core/Logger.hpp"
#include "Graphics/Handles.hpp"
#include "MTL/Matrices/Ext/Format.hpp"
#include "MTL/Matrices/Mat2x2.hpp"
#include "MTL/Matrices/Mat3x3.hpp"
#include "MTL/Matrices/Mat4x4.hpp"
#include "MTL/Vectors/Ext/Format.hpp"
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
    ~OpenGLUniform() noexcept = default;

    /// @brief Constructs an invalid uniform. You must set the program and name before using it.
    OpenGLUniform() noexcept : _name(), _program(), _nativeHandle(0u), _location(-1), _value()
    {
    }

    /// @brief Constructs a uniform with a program and name.
    /// @param name The name of the uniform.
    /// @param program The program handle.
    /// @param openGLHandle The native OpenGL handle to the program.
    /// @note The program and name must both be valid as the location will be cached immediately.
    OpenGLUniform(const string &name, ProgramHandle program, GLuint openGLHandle) noexcept
        : _name(name), _program(program), _nativeHandle(openGLHandle), _location(-1), _value()
    {
      CacheLocation();
    }

    /// @brief Set the program handle.
    /// @param program The program handle.
    /// @param openGLHandle The native OpenGL handle to the program.
    /// @note The location will automatically be cached if the name has also been set.
    void SetProgram(ProgramHandle program, GLuint openGLHandle) noexcept
    {
      _program = program;
      _nativeHandle = openGLHandle;

      if (!_name.empty())
        CacheLocation();
    }

    /// @brief Set the name of the uniform.
    /// @param name The name of the uniform.
    /// @note The location will automatically be cached if the program has also been set.
    void SetName(const string &name) noexcept
    {
      _name = name;
      if (_program.IsValid())
        CacheLocation();
    }

    /// @brief Set the value of the uniform.
    /// @param value The value to set.
    /// @note - The value will only be uploaded if the location is valid.
    /// @note - Also, the underlying type supports 'operator==' then the value will only be uploaded if it has
    /// changed.
    void SetValue(const uniform_t &value) noexcept
    {
      if (_location == -1)
      {
        Logger::Warn("Tried setting a value for an invalid uniform location. (Program {0})", _program.Id());
        return;
      }

      // Logger::Info("Setting uniform value at location {0} (Program {1}):", _location, _program.Id());
      // Logger::WriteLine("{0}", value);

      // if 'uniform_t' supports 'operator==' then we can compare the values
      if constexpr (requires { _value == value; })
      {
        if (_value == value)
          return;
      }
      _value = value;
      UploadValue();
    }

    /// @brief Get the current value of the uniform.
    NO_DISCARD const uniform_t &GetValue() const noexcept
    {
      return _value;
    }

    /// @brief Get the name of the uniform.
    NO_DISCARD const string &GetName() const noexcept
    {
      return _name;
    }

    /// @brief Get the program handle.
    NO_DISCARD ProgramHandle GetProgram() const noexcept
    {
      return _program;
    }

    /// @brief Get the location of the uniform.
    NO_DISCARD GLint GetLocation() const noexcept
    {
      return _location;
    }

  private:
    void UploadValue() const noexcept
    {
      if constexpr (std::is_same_v<uniform_t, bool>)
        ::glProgramUniform1i(_nativeHandle, _location, _value);
      else if constexpr (std::is_same_v<uniform_t, int32>)
        ::glProgramUniform1i(_nativeHandle, _location, _value);
      else if constexpr (std::is_same_v<uniform_t, List<int32>>)
        ::glProgramUniform1iv(_nativeHandle, _location, _value.size(), _value.data());
      else if constexpr (std::is_same_v<uniform_t, uint32>)
        ::glProgramUniform1ui(_nativeHandle, _location, _value);
      else if constexpr (std::is_same_v<uniform_t, List<uint32>>)
        ::glProgramUniform1uiv(_nativeHandle, _location, _value.size(), _value.data());
      else if constexpr (std::is_same_v<uniform_t, uint64>)
        ::glProgramUniformHandleui64ARB(_nativeHandle, _location, _value);
      else if constexpr (std::is_same_v<uniform_t, float32>)
        ::glProgramUniform1f(_nativeHandle, _location, _value);
      else if constexpr (std::is_same_v<uniform_t, List<float32>>)
        ::glProgramUniform1fv(_nativeHandle, _location, _value.size(), _value.data());
      else if constexpr (std::is_same_v<uniform_t, Vec2>)
        ::glProgramUniform2f(_nativeHandle, _location, _value.x, _value.y);
      else if constexpr (std::is_same_v<uniform_t, List<Vec2>>)
        ::glProgramUniform2fv(_nativeHandle, _location, _value.size(), &_value[0].x);
      else if constexpr (std::is_same_v<uniform_t, Vec3>)
        ::glProgramUniform3f(_nativeHandle, _location, _value.x, _value.y, _value.z);
      else if constexpr (std::is_same_v<uniform_t, List<Vec3>>)
        ::glProgramUniform3fv(_nativeHandle, _location, _value.size(), &_value[0].x);
      else if constexpr (std::is_same_v<uniform_t, Vec4>)
        ::glProgramUniform4f(_nativeHandle, _location, _value.x, _value.y, _value.z, _value.w);
      else if constexpr (std::is_same_v<uniform_t, List<Vec4>>)
        ::glProgramUniform4fv(_nativeHandle, _location, _value.size(), &_value[0].x);
      else if constexpr (std::is_same_v<uniform_t, Mat2>)
        ::glProgramUniformMatrix2fv(_nativeHandle, _location, 1, GL_FALSE, &_value[0].x);
      else if constexpr (std::is_same_v<uniform_t, List<Mat2>>)
        ::glProgramUniformMatrix2fv(_nativeHandle, _location, _value.size(), GL_FALSE, &_value[0][0].x);
      else if constexpr (std::is_same_v<uniform_t, Mat3>)
        ::glProgramUniformMatrix3fv(_nativeHandle, _location, 1, GL_FALSE, &_value[0].x);
      else if constexpr (std::is_same_v<uniform_t, List<Mat3>>)
        ::glProgramUniformMatrix3fv(_nativeHandle, _location, _value.size(), GL_FALSE, &_value[0][0].x);
      else if constexpr (std::is_same_v<uniform_t, Mat4>)
        ::glProgramUniformMatrix4fv(_nativeHandle, _location, 1, GL_FALSE, &_value[0].x);
      else if constexpr (std::is_same_v<uniform_t, List<Mat4>>)
        ::glProgramUniformMatrix4fv(_nativeHandle, _location, _value.size(), GL_FALSE, &_value[0][0].x);
      else
        KRYS_ASSERT(false, "Unsupported uniform type.");
    }

    void CacheLocation() noexcept
    {
      KRYS_ASSERT(_program.IsValid(), "Invalid program handle.");
      KRYS_ASSERT(!_name.empty(), "Name was not provided.");
      _location = ::glGetProgramResourceLocation(_nativeHandle, GL_UNIFORM, _name.c_str());
      if (_location == -1)
        Logger::Warn("Uniform '{0}' does not exist. (Program {1})", _name, _program.Id());
    }

  private:
    string _name;
    ProgramHandle _program;
    GLuint _nativeHandle;
    GLint _location;
    uniform_t _value;
  };
}