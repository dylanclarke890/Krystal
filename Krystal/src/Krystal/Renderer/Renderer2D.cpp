#include "krys-pch.h"
#include "Renderer2D.h"

#include "Krystal/Renderer/RenderCommand.h"
#include "Krystal/Renderer/Shader.h"
#include "Krystal/Renderer/VertexArray.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Krys
{
  struct Renderer2DData
  {
    Ref<VertexArray> QuadVertexArray;
    Ref<Shader> Shader;
    Ref<Texture2D> WhiteTexture;
  };

  static Renderer2DData* s_Data;

  void Renderer2D::Init()
  {
    KRYS_PROFILE_FUNCTION();

    s_Data = new Renderer2DData();

    s_Data->QuadVertexArray = VertexArray::Create();

    s_Data->Shader = Shader::Create("assets/shaders/Texture.krys");
    s_Data->Shader->Bind();
    s_Data->Shader->SetInt("u_Texture", 0);
    
    uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
    Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
    
    float vertices[5 * 4] = {
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
       0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
       0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
      -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
    };
    Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
    vertexBuffer->SetLayout({
      { ShaderDataType::Float3, "a_Position" },
      { ShaderDataType::Float2, "a_TextureCoord" }
    });

    s_Data->QuadVertexArray->AddVertexBuffer(vertexBuffer);
    s_Data->QuadVertexArray->SetIndexBuffer(indexBuffer);

    s_Data->WhiteTexture = Texture2D::Create(1, 1);
    uint32_t whiteTextureData = 0xFFFFFFFF;
    s_Data->WhiteTexture->SetData(&whiteTextureData, sizeof(whiteTextureData));
  }

  void Renderer2D::Shutdown()
  {
    KRYS_PROFILE_FUNCTION();

    delete s_Data;
  }
  
  void Renderer2D::BeginScene(const OrthographicCamera& camera)
  {
    KRYS_PROFILE_FUNCTION();

    s_Data->Shader->Bind();
    s_Data->Shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
  }
  
  void Renderer2D::EndScene()
  {
    KRYS_PROFILE_FUNCTION();
  }

  void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
  {
    DrawQuad({ position.x, position.y, 0.0f }, size, color);
  }
  
  void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
  {
    KRYS_PROFILE_FUNCTION();

    s_Data->Shader->SetFloat4("u_Color", color);
    s_Data->Shader->SetFloat("u_TilingFactor", 1.0f);
    s_Data->WhiteTexture->Bind();

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
    s_Data->Shader->SetMat4("u_Transform", transform);

    s_Data->QuadVertexArray->Bind();
    RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
  }

  void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
  {
    DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
  }
  
  void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
  {
    KRYS_PROFILE_FUNCTION();

    s_Data->Shader->SetFloat4("u_Color", tintColor);
    s_Data->Shader->SetFloat("u_TilingFactor", tilingFactor);
    texture->Bind();

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
    s_Data->Shader->SetMat4("u_Transform", transform);

    s_Data->QuadVertexArray->Bind();
    RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
  }

  void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
  {
    DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
  }
  
  void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
  {
    KRYS_PROFILE_FUNCTION();

    s_Data->Shader->SetFloat4("u_Color", color);
    s_Data->Shader->SetFloat("u_TilingFactor", 1.0f);
    s_Data->WhiteTexture->Bind();

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
      * glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
      * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

    s_Data->Shader->SetMat4("u_Transform", transform);

    s_Data->QuadVertexArray->Bind();
    RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
  }
  
  void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
  {
    DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tilingFactor, tintColor);

  }
  
  void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
  {
    KRYS_PROFILE_FUNCTION();

    s_Data->Shader->SetFloat4("u_Color", tintColor);
    s_Data->Shader->SetFloat("u_TilingFactor", tilingFactor);
    texture->Bind();

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) 
      * glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
      * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

    s_Data->Shader->SetMat4("u_Transform", transform);

    s_Data->QuadVertexArray->Bind();
    RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
  }
}