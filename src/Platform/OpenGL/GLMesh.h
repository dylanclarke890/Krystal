#pragma once

#include "Krystal.h"
#include "Graphics/Mesh.h"

#include "GLVertexArray.h"
#include "GLBuffer.h"

namespace Krys
{
  class GLMesh : public Mesh
  {
    Ref<GLVertexArray> VertexArray;
    Ref<GLVertexBuffer> VertexBuffer;
    Ref<GLIndexBuffer> IndexBuffer;

  public:
    void Setup() override
    {
      auto bufferSize = Vertices.size() * sizeof(Vertex);
      VertexBuffer = CreateRef<GLVertexBuffer>(Vertices.data(), bufferSize);
      VertexBuffer->SetLayout(
          BufferLayout(bufferSize,
                       {{ShaderDataType::Float3, "i_Position"},
                        {ShaderDataType::Float3, "i_Normal"},
                        {ShaderDataType::Float2, "i_TextureCoord"}}));

      IndexBuffer = CreateRef<GLIndexBuffer>(Indices.data(), Indices.size());

      VertexArray = CreateRef<GLVertexArray>();
      VertexArray->AddVertexBuffer(VertexBuffer);
      VertexArray->SetIndexBuffer(IndexBuffer);
    }

    void Draw(Ref<Shader> shader) const override
    {
      int textureSlot = 0;
      int diffuseSlot = 0;
      int specularSlot = 0;
      int emissionSlot = 0;

      for (auto texture : Textures)
      {
        switch (texture->GetType())
        {
        case TextureType::Diffuse:
        {
          shader->SetUniform(("u_DiffuseTextures[" + std::to_string(diffuseSlot++) + "]").c_str(), textureSlot);
          break;
        }
        case TextureType::Specular:
        {
          shader->SetUniform(("u_SpecularTextures[" + std::to_string(specularSlot++) + "]").c_str(), textureSlot);
          break;
        }
        case TextureType::Emission:
        {
          shader->SetUniform(("u_EmissionTextures[" + std::to_string(emissionSlot++) + "]").c_str(), textureSlot);
          break;
        }
        default:
        {
          KRYS_ASSERT(false, "TextureType not recognised", 0);
          break;
        }
        }

        texture->Bind(textureSlot);
        textureSlot++;
      }

      shader->SetUniform("u_TotalDiffuseTextures", diffuseSlot + 1);
      shader->SetUniform("u_TotalSpecularTextures", specularSlot + 1);
      shader->SetUniform("u_TotalEmissionTextures", emissionSlot + 1);

      VertexArray->Bind();
      glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
      VertexArray->Unbind();
    }
  };
}