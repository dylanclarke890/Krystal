#include "krys-pch.h"
#include "Renderer2D.h"

#include "Krystal/Renderer/RenderCommand.h"
#include "Krystal/Renderer/Shader.h"
#include "Krystal/Renderer/VertexArray.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Krys
{
  struct Renderer2DData
  {
    Ref<VertexArray> QuadVertexArray;
    Ref<Shader> FlatColorShader;
  };

  static Renderer2DData* s_Data;

  void Renderer2D::Init()
  {
    s_Data = new Renderer2DData();

    s_Data->QuadVertexArray = VertexArray::Create();
    s_Data->FlatColorShader = Shader::Create("assets/shaders/FlatColor.krys");
    
    uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
    Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
    
    float vertices[5 * 4] = {
      -0.5f, -0.5f, 0.0f,
       0.5f, -0.5f, 0.0f,
       0.5f,  0.5f, 0.0f,
      -0.5f,  0.5f, 0.0f
    };
    Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
    vertexBuffer->SetLayout({
      { ShaderDataType::Float3, "a_Position" }
    });

    s_Data->QuadVertexArray->AddVertexBuffer(vertexBuffer);
    s_Data->QuadVertexArray->SetIndexBuffer(indexBuffer);
  }

  void Renderer2D::Shutdown()
  {
    delete s_Data;
  }
  
  void Renderer2D::BeginScene(const OrthographicCamera& camera)
  {
    s_Data->FlatColorShader->Bind();
    std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
    std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->UploadUniformMat4("u_Transform", glm::mat4(1.0f));
  }
  
  void Renderer2D::EndScene()
  {

  }

  void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
  {
    DrawQuad({ position.x, position.y, 0.0f }, size, color);
  }
  
  void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
  {
    s_Data->FlatColorShader->Bind();
    std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->UploadUniformFloat4("u_Color", color);

    s_Data->QuadVertexArray->Bind();
    RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
  }
}