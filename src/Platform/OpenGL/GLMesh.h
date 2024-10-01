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
    GLMesh(List<Vertex> &vertices, List<uint32> &indices, List<Ref<Texture2D>> &textures)
    {
      Vertices = vertices;
      Indices = indices;
      Textures = textures;

      Setup();
    }

    void Setup() override
    {
      VertexBuffer = CreateRef<GLVertexBuffer>(reinterpret_cast<float *>(Vertices.data()), static_cast<uint32>(Vertices.size() * sizeof(Vertex)));
      VertexBuffer->SetLayout(VertexBufferLayout({{ShaderDataType::Float3, "i_Position"},
                                                  {ShaderDataType::Float3, "i_Normal"},
                                                  {ShaderDataType::Float2, "i_TextureCoords"}}));

      IndexBuffer = CreateRef<GLIndexBuffer>(Indices.data(), static_cast<uint32>(Indices.size()));

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
          string uniformName = "u_DiffuseTextures[" + std::to_string(diffuseSlot++) + "]";
          shader->TrySetUniform(uniformName, textureSlot);
          break;
        }
        case TextureType::Specular:
        {
          string uniformName = "u_SpecularTextures[" + std::to_string(specularSlot++) + "]";
          shader->TrySetUniform(uniformName, textureSlot);
          break;
        }
        case TextureType::Emission:
        {
          string uniformName = "u_EmissionTextures[" + std::to_string(emissionSlot++) + "]";
          shader->TrySetUniform(uniformName, textureSlot);
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

      shader->TrySetUniform("u_TotalDiffuseTextures", diffuseSlot + 1);
      shader->TrySetUniform("u_TotalSpecularTextures", specularSlot + 1);
      shader->TrySetUniform("u_TotalEmissionTextures", emissionSlot + 1);

      VertexArray->Bind();
      glDrawElements(GL_TRIANGLES, static_cast<int>(Indices.size()), GL_UNSIGNED_INT, 0);
      VertexArray->Unbind();
    }
  };
}