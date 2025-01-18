#include "Graphics/OpenGL/OpenGLPipeline.hpp"
#include "Core/Debug/Macros.hpp"

namespace Krys::Graphics::OpenGL
{
  OpenGLPipeline::OpenGLPipeline() noexcept : Pipeline(), _program(glCreateProgram())
  {
    _handle = PipelineHandle(static_cast<PipelineHandle::handle_t>(_program));
  }

  OpenGLPipeline::~OpenGLPipeline() noexcept
  {
    glDeleteProgram(_program);
  }

  void OpenGLPipeline::Bind() noexcept
  {
    KRYS_ASSERT(_linked && _isValid, "Pipeline must be valid and linked before binding");
    glUseProgram(_program);
  }

  void OpenGLPipeline::Unbind() noexcept
  {
    KRYS_ASSERT(_linked && _isValid, "Pipeline must be valid and linked before unbinding");
    glUseProgram(0);
  }

  void OpenGLPipeline::Link() noexcept
  {
    KRYS_ASSERT(!_linked, "Pipeline is already linked");

    for (auto shader : _shaders)
    {
      glAttachShader(_program, shader.Id());
    }

    glLinkProgram(_program);
    _linked = true;

    int success;
    glGetProgramiv(_program, GL_LINK_STATUS, &success);
    if (!success)
    {
      char infoLog[512];
      glGetProgramInfoLog(_program, 512, nullptr, infoLog);
      KRYS_ASSERT(false, "Program linking failed: {0}", infoLog);
    }
    _isValid = true;

    for (auto shader : _shaders)
    {
      glDeleteShader(shader.Id());
    }
  }

  void OpenGLPipeline::AddShader(ShaderHandle handle) noexcept
  {
    _shaders.push_back(handle);
  }
}