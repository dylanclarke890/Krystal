#pragma once

#include "Krystal/Renderer/OrthographicCamera.h"
#include "Krystal/Renderer/Texture.h"

namespace Krys
{
  class Renderer2D
  {
  public:
    static void Init();
    static void Shutdown();
    
    static void BeginScene(const OrthographicCamera& camera);
    static void EndScene();

    static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
    static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
    static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture);
    static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture);

    // Enforce Singleton usage.
  public:
    Renderer2D(const Renderer2D&) = delete;
    Renderer2D& operator=(const Renderer2D&) = delete;
  };
}