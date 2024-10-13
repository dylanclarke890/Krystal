#include "Core.h"
#include "IO/IO.h"
#include "Graphics/Shaders/ShaderPreprocessor.h"
#include "OpenGL/GLShader.h"

namespace Krys::OpenGL
{
  GLShader::GLShader()
  {
    _id = glCreateProgram();
  }

  GLShader::~GLShader()
  {
    glDeleteProgram(_id);
    for (size_t i = 0; i < _shaders.size(); i++)
      glDeleteShader(_shaders[i]);
  }

  void GLShader::Bind()
  {
    glUseProgram(_id);
  }

  void GLShader::Unbind()
  {
    glUseProgram(0);
  }

  void GLShader::Load(ShaderType type, const stringview &filepath)
  {
    string src = IO::ReadFileText(filepath);

    src = ShaderPreprocessor::ResolveImports(filepath, src);
    src = ShaderPreprocessor::ResolveKeys(src);

    Add(type, src);
  }

  void GLShader::Load(const stringview &vertexFilepath, const stringview &fragmentFilepath)
  {
    Load(ShaderType::Vertex, vertexFilepath);
    Load(ShaderType::Fragment, fragmentFilepath);
  }

  void GLShader::Add(ShaderType type, const stringview &source)
  {
    uint id = glCreateShader(ToGLShaderType(type));
    const char *src = source.data();
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);

    GLint status;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
      GLint infoLogLength;
      glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);

      GLchar *infoLog = new GLchar[infoLogLength + 1];
      glGetShaderInfoLog(id, infoLogLength, NULL, infoLog);

      const char *shaderType = NULL;
      switch (type)
      {
      case ShaderType::Vertex:
        shaderType = "vertex";
        break;
      case ShaderType::Geometry:
        shaderType = "geometry";
        break;
      case ShaderType::Fragment:
        shaderType = "fragment";
        break;
      default:
      {
        KRYS_ASSERT(false, "Unknown ShaderType!", 0);
        break;
      }
      }

      KRYS_ASSERT(false, "Compile failure in %s shader:\n%s", shaderType, infoLog);
      delete[] infoLog;
    }

    _shaders.push_back(id);
  }

  void GLShader::Link()
  {
    for (size_t i = 0; i < _shaders.size(); i++)
      glAttachShader(_id, _shaders[i]);

    glLinkProgram(_id);

    GLint status;
    glGetProgramiv(_id, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
      GLint infoLogLength;
      glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &infoLogLength);

      GLchar *infoLog = new GLchar[infoLogLength + 1];
      glGetProgramInfoLog(_id, infoLogLength, NULL, infoLog);

      KRYS_ASSERT(false, "Linker failure: %s", infoLog);
      delete[] infoLog;
    }

    for (size_t i = 0; i < _shaders.size(); i++)
      glDetachShader(_id, _shaders[i]);
  }

  void GLShader::SetUniform(const string &name, int value)
  {
    GLint location = glGetProgramResourceLocation(_id, GL_UNIFORM, name.c_str());
    KRYS_ASSERT(location != -1, "%s wasn't a valid uniform", name.c_str());
    glProgramUniform1i(_id, location, value);
  }

  void GLShader::TrySetUniform(const string &name, int value)
  {
    GLint location = glGetProgramResourceLocation(_id, GL_UNIFORM, name.c_str());
    if (location != -1)
    {
      glProgramUniform1i(_id, location, value);
    }
  }

  void GLShader::SetUniform(const string &name, float value)
  {
    GLint location = glGetProgramResourceLocation(_id, GL_UNIFORM, name.c_str());
    KRYS_ASSERT(location != -1, "%s wasn't a valid uniform", name.c_str());
    glProgramUniform1f(_id, location, value);
  }

  void GLShader::TrySetUniform(const string &name, float value)
  {
    GLint location = glGetProgramResourceLocation(_id, GL_UNIFORM, name.c_str());
    if (location != -1)
    {
      glProgramUniform1f(_id, location, value);
    }
  }

  void GLShader::SetUniform(const string &name, int *values, uint32_t count)
  {
    GLint location = glGetProgramResourceLocation(_id, GL_UNIFORM, name.c_str());
    KRYS_ASSERT(location != -1, "%s wasn't a valid uniform", name.c_str());
    glProgramUniform1iv(_id, location, count, values);
  }

  void GLShader::TrySetUniform(const string &name, int *values, uint32_t count)
  {
    GLint location = glGetProgramResourceLocation(_id, GL_UNIFORM, name.c_str());
    if (location != -1)
    {
      glProgramUniform1iv(_id, location, count, values);
    }
  }

  void GLShader::SetUniform(const string &name, float *values, uint32_t count)
  {
    GLint location = glGetProgramResourceLocation(_id, GL_UNIFORM, name.c_str());
    KRYS_ASSERT(location != -1, "%s wasn't a valid uniform", name.c_str());
    glProgramUniform1fv(_id, location, count, values);
  }

  void GLShader::TrySetUniform(const string &name, float *values, uint32_t count)
  {
    GLint location = glGetProgramResourceLocation(_id, GL_UNIFORM, name.c_str());
    if (location != -1)
    {
      glProgramUniform1fv(_id, location, count, values);
    }
  }

  void GLShader::SetUniform(const string &name, const Vec2 &value)
  {
    GLint location = glGetProgramResourceLocation(_id, GL_UNIFORM, name.c_str());
    KRYS_ASSERT(location != -1, "%s wasn't a valid uniform", name.c_str());
    glProgramUniform2f(_id, location, value.x, value.y);
  }

  void GLShader::TrySetUniform(const string &name, const Vec2 &value)
  {
    GLint location = glGetProgramResourceLocation(_id, GL_UNIFORM, name.c_str());
    if (location != -1)
    {
      glProgramUniform2f(_id, location, value.x, value.y);
    }
  }

  void GLShader::SetUniform(const string &name, const Vec3 &value)
  {
    GLint location = glGetProgramResourceLocation(_id, GL_UNIFORM, name.c_str());
    KRYS_ASSERT(location != -1, "%s wasn't a valid uniform", name.c_str());
    glProgramUniform3f(_id, location, value.x, value.y, value.z);
  }

  void GLShader::TrySetUniform(const string &name, const Vec3 &value)
  {
    GLint location = glGetProgramResourceLocation(_id, GL_UNIFORM, name.c_str());
    if (location != -1)
    {
      glProgramUniform3f(_id, location, value.x, value.y, value.z);
    }
  }

  void GLShader::SetUniform(const string &name, const Vec4 &value)
  {
    GLint location = glGetProgramResourceLocation(_id, GL_UNIFORM, name.c_str());
    KRYS_ASSERT(location != -1, "%s wasn't a valid uniform", name.c_str());
    glProgramUniform4f(_id, location, value.x, value.y, value.z, value.w);
  }

  void GLShader::TrySetUniform(const string &name, const Vec4 &value)
  {
    GLint location = glGetProgramResourceLocation(_id, GL_UNIFORM, name.c_str());
    if (location != -1)
    {
      glProgramUniform4f(_id, location, value.x, value.y, value.z, value.w);
    }
  }

  void GLShader::SetUniform(const string &name, const Mat3 &matrix)
  {
    GLint location = glGetProgramResourceLocation(_id, GL_UNIFORM, name.c_str());
    KRYS_ASSERT(location != -1, "%s wasn't a valid uniform", name.c_str());
    glProgramUniformMatrix3fv(_id, location, 1, GL_FALSE, glm::value_ptr(matrix));
  }

  void GLShader::TrySetUniform(const string &name, const Mat3 &matrix)
  {
    GLint location = glGetProgramResourceLocation(_id, GL_UNIFORM, name.c_str());
    if (location != -1)
    {
      glProgramUniformMatrix3fv(_id, location, 1, GL_FALSE, glm::value_ptr(matrix));
    }
  }

  void GLShader::SetUniform(const string &name, const Mat4 &matrix)
  {
    GLint location = glGetProgramResourceLocation(_id, GL_UNIFORM, name.c_str());
    KRYS_ASSERT(location != -1, "%s wasn't a valid uniform", name.c_str());
    glProgramUniformMatrix4fv(_id, location, 1, GL_FALSE, glm::value_ptr(matrix));
  }

  void GLShader::TrySetUniform(const string &name, const Mat4 &matrix)
  {
    GLint location = glGetProgramResourceLocation(_id, GL_UNIFORM, name.c_str());
    if (location != -1)
    {
      glProgramUniformMatrix4fv(_id, location, 1, GL_FALSE, glm::value_ptr(matrix));
    }
  }

  GLenum GLShader::ToGLShaderType(ShaderType type)
  {
    switch (type)
    {
    case ShaderType::Vertex:
      return GL_VERTEX_SHADER;
      break;
    case ShaderType::Fragment:
      return GL_FRAGMENT_SHADER;
      break;
    case ShaderType::Geometry:
      return GL_GEOMETRY_SHADER;
    default:
      KRYS_ASSERT(false, "Invalid ShaderType!", 0);
      return 0;
    }
  }
}