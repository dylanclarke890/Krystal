#pragma once

#include "RenderCommand.h"
#include "Krystal/Camera/OrthographicCamera.h"
#include "Shader.h"

namespace Krys
{
  class Renderer
  {
  public:
    static void Init();

    static void BeginScene(OrthographicCamera& camera);
    static void Submit(
      const Ref<Shader>& shader,
      const Ref<VertexArray>& vertexArray,
      const glm::mat4& transform = glm::mat4(1.0f)
    );
    static void EndScene();
    
    inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); };
  
  private:
    struct SceneData
    {
      glm::mat4 ViewProjectionMatrix;
    };

    static SceneData* m_SceneData;
  };

}