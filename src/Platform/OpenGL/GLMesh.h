#pragma once

#include <vector>

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
    GLMesh(std::vector<Vertex> &vertices, std::vector<uint32> &indices, std::vector<Ref<Texture2D>> &textures)
    {
      Vertices = vertices;
      Indices = indices;
      Textures = textures;

      Setup();
    }

    void Setup() override
    {
      auto bufferSize = Vertices.size() * sizeof(Vertex);
      VertexBuffer = CreateRef<GLVertexBuffer>(reinterpret_cast<float *>(Vertices.data()), static_cast<uint32>(bufferSize));
      VertexBuffer->SetLayout(
          BufferLayout(static_cast<uint32>(bufferSize),
                       {{ShaderDataType::Float3, "i_Position"},
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
          std::string uniformName = "u_DiffuseTextures[" + std::to_string(diffuseSlot++) + "]";
          shader->SetUniform(uniformName.c_str(), textureSlot);
          break;
        }
        case TextureType::Specular:
        {
          std::string uniformName = "u_SpecularTextures[" + std::to_string(specularSlot++) + "]";
          shader->SetUniform(uniformName.c_str(), textureSlot);
          break;
        }
        case TextureType::Emission:
        {
          std::string uniformName = "u_EmissionTextures[" + std::to_string(emissionSlot++) + "]";
          shader->SetUniform(uniformName.c_str(), textureSlot);
          break;
        }
        default:
        {
          KRYS_ASSERT(false, "TextureType not recognised");
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
      glDrawElements(GL_TRIANGLES, static_cast<int>(Indices.size()), GL_UNSIGNED_INT, 0);
      VertexArray->Unbind();
    }
  };
}