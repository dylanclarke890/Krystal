#pragma once

#include <string>

namespace Krys {
  class Shader 
  {
  private:
    uint32_t m_RendererId;
  public:
    Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
    ~Shader();

    void Bind() const;
    void Unbind() const;
  };
}