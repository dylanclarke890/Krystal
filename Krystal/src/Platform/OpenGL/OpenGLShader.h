#pragma once

#include "Krystal/Renderer/Shader.h"

#include <glm/glm.hpp>
typedef unsigned int GLenum; // TODO: REMOVE!

namespace Krys
{

  class OpenGLShader : public Shader
  {
  private:
    uint32_t m_RendererId;
    std::string m_Name;
  public:
    OpenGLShader(const std::string& filePath);
    OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
    virtual ~OpenGLShader() override;

    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual void SetInt(const std::string& name, int value) override;
    virtual void SetIntArray(const std::string& name, int* values, uint32_t count) override;
    virtual void SetFloat(const std::string& name, float value) override;
    virtual void SetFloat3(const std::string& name, const glm::vec3& vector) override;
    virtual void SetFloat4(const std::string& name, const glm::vec4& vector) override;
    virtual void SetMat4(const std::string& name, const glm::mat4& matrix) override;

    virtual const std::string& GetName() const override { return m_Name; }

    void UploadUniformInt(const std::string& name, int value);
    void UploadUniformIntArray(const std::string& name, int* values, uint32_t count);

    void UploadUniformFloat(const std::string& name, float value);
    void UploadUniformFloat2(const std::string& name, const glm::vec2& vector);
    void UploadUniformFloat3(const std::string& name, const glm::vec3& vector);
    void UploadUniformFloat4(const std::string& name, const glm::vec4& vector);

    void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
    void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
  private:
    std::string ReadFile(const std::string& filePath);
    std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
    void Compile(std::unordered_map<GLenum, std::string>& shaderSources);
  };
}