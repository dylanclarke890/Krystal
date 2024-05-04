#include <fstream>
#include <sstream>

#include "GLShader.h"
#include "Krystal.h"

namespace Krys
{
  GLShader::GLShader() : Id(glCreateProgram()) {}

  GLShader::~GLShader()
  {
    glDeleteProgram(Id);
    for (size_t i = 0; i < Shaders.size(); i++)
      glDeleteShader(Shaders[i]);
  }

  void GLShader::Bind()
  {
    glUseProgram(Id);
  }

  void GLShader::Unbind()
  {
    glUseProgram(0);
  }

  void GLShader::Load(ShaderType type, const char *filepath)
  {
    std::ifstream fileStream(filepath, std::ios::in);
    bool isOpen = fileStream.is_open();

    KRYS_ASSERT(isOpen, "Unable to open %s. Are you in the right directory?", filepath);
    if (!isOpen)
      return;

    std::stringstream sstr;
    sstr << fileStream.rdbuf();
    fileStream.close();

    auto sourceStr = sstr.str();
    const char *source = sourceStr.c_str();
    Add(type, source);
  }

  void GLShader::Load(const char *vertexFilepath, const char *fragmentFilepath)
  {
    Load(ShaderType::Vertex, vertexFilepath);
    Load(ShaderType::Fragment, fragmentFilepath);
  }

  void GLShader::Add(ShaderType type, const char *source)
  {
    GLRendererId id = glCreateShader(ToGLShaderType(type));
    glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);

    // TODO: check if the debug output callback can handle outputting this instead
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
      }

      KRYS_ASSERT(false, "Compile failure in %s shader:\n%s", shaderType, infoLog);
      delete[] infoLog;
    }

    Shaders.push_back(id);
  }

  void GLShader::Link()
  {
    for (size_t i = 0; i < Shaders.size(); i++)
      glAttachShader(Id, Shaders[i]);

    glLinkProgram(Id);

    // TODO: check if the debug output callback can handle outputting this instead
    GLint status;
    glGetProgramiv(Id, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
      GLint infoLogLength;
      glGetProgramiv(Id, GL_INFO_LOG_LENGTH, &infoLogLength);

      GLchar *infoLog = new GLchar[infoLogLength + 1];
      glGetProgramInfoLog(Id, infoLogLength, NULL, infoLog);

      KRYS_ASSERT(false, "Linker failure: %s", infoLog);
      delete[] infoLog;
    }

    for (size_t i = 0; i < Shaders.size(); i++)
      glDetachShader(Id, Shaders[i]);
  }

  void GLShader::SetUniform(const char *name, int value)
  {
    GLint location = glGetProgramResourceLocation(Id, GL_UNIFORM, name);
    KRYS_ASSERT(location != -1, "%s wasn't a valid uniform", name);
    glProgramUniform1i(Id, location, value);
  }

  void GLShader::SetUniform(const char *name, float value)
  {
    GLint location = glGetProgramResourceLocation(Id, GL_UNIFORM, name);
    KRYS_ASSERT(location != -1, "%s wasn't a valid uniform", name);
    glProgramUniform1f(Id, location, value);
  }

  void GLShader::SetUniform(const char *name, int *values, uint32_t count)
  {
    GLint location = glGetProgramResourceLocation(Id, GL_UNIFORM, name);
    KRYS_ASSERT(location != -1, "%s wasn't a valid uniform", name);
    glProgramUniform1iv(Id, location, count, values);
  }

  void GLShader::SetUniform(const char *name, float *values, uint32_t count)
  {
    GLint location = glGetProgramResourceLocation(Id, GL_UNIFORM, name);
    KRYS_ASSERT(location != -1, "%s wasn't a valid uniform", name);
    glProgramUniform1fv(Id, location, count, values);
  }

  void GLShader::SetUniform(const char *name, const Vec2 &value)
  {
    GLint location = glGetProgramResourceLocation(Id, GL_UNIFORM, name);
    KRYS_ASSERT(location != -1, "%s wasn't a valid uniform", name);
    glProgramUniform2f(Id, location, value.x, value.y);
  }

  void GLShader::SetUniform(const char *name, const Vec3 &value)
  {
    GLint location = glGetProgramResourceLocation(Id, GL_UNIFORM, name);
    KRYS_ASSERT(location != -1, "%s wasn't a valid uniform", name);
    glProgramUniform3f(Id, location, value.x, value.y, value.z);
  }

  void GLShader::SetUniform(const char *name, const Vec4 &value)
  {
    GLint location = glGetProgramResourceLocation(Id, GL_UNIFORM, name);
    KRYS_ASSERT(location != -1, "%s wasn't a valid uniform", name);
    glProgramUniform4f(Id, location, value.x, value.y, value.z, value.w);
  }

  void GLShader::SetUniform(const char *name, const Mat3 &matrix)
  {
    GLint location = glGetProgramResourceLocation(Id, GL_UNIFORM, name);
    KRYS_ASSERT(location != -1, "%s wasn't a valid uniform", name);
    glProgramUniformMatrix3fv(Id, location, 1, GL_FALSE, &(matrix[0].x));
  }

  void GLShader::SetUniform(const char *name, const Mat4 &matrix)
  {
    GLint location = glGetProgramResourceLocation(Id, GL_UNIFORM, name);
    KRYS_ASSERT(location != -1, "%s wasn't a valid uniform", name);
    glProgramUniformMatrix4fv(Id, location, 1, GL_FALSE, &(matrix[0].x));
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
      KRYS_ASSERT(false, "Invalid ShaderType!");
      return 0;
    }
  }
}