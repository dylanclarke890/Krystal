#include "krys-pch.h"
#include "Renderer2D.h"

#include "Krystal/Renderer/RenderCommand.h"
#include "Krystal/Renderer/Shader.h"
#include "Krystal/Renderer/VertexArray.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Krys
{
  struct QuadVertex
  {
    glm::vec3 Position = glm::vec3(1.0f);
    glm::vec4 Color = glm::vec4(0.0f);
    glm::vec2 TextureCoord = glm::vec2(0.0f);
    float TextureIndex = 0.0f;
    float TilingFactor = 1.0f;
  };

  struct Renderer2DData
  {
    static const uint32_t MaxQuads = 10000;
    static const uint32_t MaxVertices = MaxQuads * 4;
    static const uint32_t MaxIndices = MaxQuads * 6;
    static const uint32_t MaxTextureSlots = 32; // TODO: Get from RenderCapabilities
    static const size_t QuadVertexCount = 4;

    Ref<VertexArray> QuadVertexArray;
    Ref<VertexBuffer> QuadVertexBuffer;
    Ref<Shader> Shader;
    Ref<Texture2D> WhiteTexture;
  
    QuadVertex* QuadVertexBufferBase = nullptr;
    QuadVertex* QuadVertexBufferPtr = nullptr;
    uint32_t QuadIndexCount = 0;
    uint32_t TextureSlotIndex = 1; // 0 = default white texture

    std::array<Ref<Texture2D>, 32> TextureSlots{};
    glm::vec4 QuadVertexPositions[4]{};

    Renderer2D::Statistics Stats;
  };

  static Renderer2DData s_Data;

  void Renderer2D::Init()
  {
    KRYS_PROFILE_FUNCTION();

    s_Data.QuadVertexArray = VertexArray::Create();

    s_Data.QuadVertexBuffer = VertexBuffer::Create(Renderer2DData::MaxVertices * sizeof(QuadVertex));
    s_Data.QuadVertexBuffer->SetLayout({
      { ShaderDataType::Float3, "a_Position" },
      { ShaderDataType::Float4, "a_Color" },
      { ShaderDataType::Float2, "a_TextureCoord" },
      { ShaderDataType::Float, "a_TextureIndex" },
      { ShaderDataType::Float, "a_TilingFactor" }
    });
    
    s_Data.QuadVertexBufferBase = new QuadVertex[Renderer2DData::MaxIndices];

    uint32_t* quadIndices = new uint32_t[Renderer2DData::MaxIndices];

    uint32_t offset = 0;
    for (uint32_t i = 0; i < Renderer2DData::MaxIndices; i += 6)
    {
      quadIndices[i + 0] = offset + 0;
      quadIndices[i + 1] = offset + 1;
      quadIndices[i + 2] = offset + 2;

      quadIndices[i + 3] = offset + 2;
      quadIndices[i + 4] = offset + 3;
      quadIndices[i + 5] = offset + 0;

      offset += 4;
    }

    Ref<IndexBuffer> quadIndexBuffer = IndexBuffer::Create(quadIndices, Renderer2DData::MaxIndices);
    delete[] quadIndices;

    s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);
    s_Data.QuadVertexArray->SetIndexBuffer(quadIndexBuffer);

    s_Data.WhiteTexture = Texture2D::Create(1, 1);
    uint32_t whiteTextureData = 0xFFFFFFFF;
    s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(whiteTextureData));
  
    int samplers[Renderer2DData::MaxTextureSlots]{};
    for (uint32_t i = 0; i < Renderer2DData::MaxTextureSlots; i++)
      samplers[i] = i;

    s_Data.Shader = Shader::Create("assets/shaders/Texture.krys");
    s_Data.Shader->Bind();
    s_Data.Shader->SetIntArray("u_Textures", samplers, Renderer2DData::MaxTextureSlots);

    s_Data.TextureSlots[0] = s_Data.WhiteTexture;

    s_Data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
    s_Data.QuadVertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
    s_Data.QuadVertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
    s_Data.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
  }

  void Renderer2D::Shutdown()
  {
    KRYS_PROFILE_FUNCTION();

    delete[] s_Data.QuadVertexBufferBase;
  }
  
  void Renderer2D::BeginScene(const OrthographicCamera& camera)
  {
    KRYS_PROFILE_FUNCTION();

    s_Data.Shader->Bind();
    s_Data.Shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
    
    s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
    s_Data.QuadIndexCount = 0;
    s_Data.TextureSlotIndex = 1;
  }
  
  void Renderer2D::EndScene()
  {
    KRYS_PROFILE_FUNCTION();

    uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase);
    s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);

    Flush();
  }

  void Renderer2D::FlushAndReset()
  {
    EndScene();

    s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
    s_Data.QuadIndexCount = 0;
    s_Data.TextureSlotIndex = 1;
  }

  void Renderer2D::Flush()
  {
    KRYS_PROFILE_FUNCTION();

    if (s_Data.QuadIndexCount == 0)
      return; // Nothing to draw

    for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
      s_Data.TextureSlots[i]->Bind(i);

    RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
    
    s_Data.Stats.DrawCalls++;
  }

  void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
  {
    DrawQuad({ position.x, position.y, 0.0f }, size, color);
  }
  
  void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
  {
    KRYS_PROFILE_FUNCTION();

    constexpr float textureIndex = 0.0f;
    constexpr float tilingFactor = 1.0f;
    constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
    constexpr glm::vec3 rotationAxis(0.0f, 0.0f, 1.0f);

    if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
      FlushAndReset();

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
      * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

    for (size_t i = 0; i < s_Data.QuadVertexCount; i++)
    {
      s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
      s_Data.QuadVertexBufferPtr->Color = color;
      s_Data.QuadVertexBufferPtr->TextureCoord = textureCoords[i];
      s_Data.QuadVertexBufferPtr->TextureIndex = textureIndex;
      s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
      s_Data.QuadVertexBufferPtr++;
    }

    s_Data.QuadIndexCount += 6;
    s_Data.Stats.QuadCount++;
  }

  void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
  {
    DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
  }
  
  void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
  {
    KRYS_PROFILE_FUNCTION();
    
    constexpr float x = 7.0f, y = 6.0f;
    constexpr float sheetWidth = 2560.f, sheetHeight = 1664.0f;
    constexpr float spriteWidth = 128.0f, spriteHeight = 128.0f;

    constexpr glm::vec2 textureCoords[] = { 
      { (x * spriteWidth) / sheetWidth, (y * spriteHeight) / sheetHeight },
      { ((x + 1) * spriteWidth) / sheetWidth, (y * spriteHeight) / sheetHeight },
      { ((x + 1) * spriteWidth) / sheetWidth, ((y + 1) * spriteHeight) / sheetHeight },
      { (x * spriteWidth) / sheetWidth, ((y + 1) * spriteHeight) / sheetHeight }
    };

    if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
      FlushAndReset();

    float textureIndex = 0.0f;
    for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
    {
      if (*texture.get() == *s_Data.TextureSlots[i].get())
      {
        textureIndex = (float)i;
        break;
      }
    }

    if (textureIndex == 0.0f)
    {
      if (s_Data.TextureSlotIndex >= Renderer2DData::MaxTextureSlots)
        FlushAndReset();

      textureIndex = (float)s_Data.TextureSlotIndex;
      KRYS_CORE_ASSERT(textureIndex >= 0.0f && textureIndex <= Renderer2DData::MaxTextureSlots - 1, "Texture index out of bounds!");
      
      s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
      s_Data.TextureSlotIndex++;

      s_Data.Stats.Textures++;
    }

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
      * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

    for (size_t i = 0; i < s_Data.QuadVertexCount; i++)
    {
      s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
      s_Data.QuadVertexBufferPtr->Color = tintColor;
      s_Data.QuadVertexBufferPtr->TextureCoord = textureCoords[i];
      s_Data.QuadVertexBufferPtr->TextureIndex = textureIndex;
      s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
      s_Data.QuadVertexBufferPtr++;
    }

    s_Data.QuadIndexCount += 6;

    s_Data.Stats.QuadCount++;
  }

  void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
  {
    DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
  }
  
  void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
  {
    KRYS_PROFILE_FUNCTION();

    constexpr float textureIndex = 0.0f;
    constexpr float tilingFactor = 1.0f;
    constexpr glm::vec3 rotationAxis(0.0f, 0.0f, 1.0f);
    constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

    if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
      FlushAndReset();

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
      * glm::rotate(glm::mat4(1.0f), rotation, rotationAxis)
      * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

    for (size_t i = 0; i < s_Data.QuadVertexCount; i++)
    {
      s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
      s_Data.QuadVertexBufferPtr->Color = color;
      s_Data.QuadVertexBufferPtr->TextureCoord = textureCoords[i];
      s_Data.QuadVertexBufferPtr->TextureIndex = textureIndex;
      s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
      s_Data.QuadVertexBufferPtr++;
    }

    s_Data.QuadIndexCount += 6;

    s_Data.Stats.QuadCount++;
  }
  
  void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
  {
    DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tilingFactor, tintColor);
  }
  
  void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
  {
    KRYS_PROFILE_FUNCTION();

    constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
    constexpr glm::vec3 rotationAxis(0.0f, 0.0f, 1.0f);

    if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
      FlushAndReset();

    float textureIndex = 0.0f;
    for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
    {
      if (*texture.get() == *s_Data.TextureSlots[i].get())
      {
        textureIndex = (float)i;
        break;
      }
    }

      if (textureIndex == 0.0f)
      {
        if (s_Data.TextureSlotIndex >= Renderer2DData::MaxTextureSlots)
          FlushAndReset();

        textureIndex = (float)s_Data.TextureSlotIndex;
        KRYS_CORE_ASSERT(textureIndex >= 0.0f && textureIndex <= Renderer2DData::MaxTextureSlots - 1, "Texture index out of bounds!");

        s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
        s_Data.TextureSlotIndex++;

        s_Data.Stats.Textures++;
      }

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
      * glm::rotate(glm::mat4(1.0f), rotation, rotationAxis)
      * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

    for (size_t i = 0; i < s_Data.QuadVertexCount; i++)
    {
      s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
      s_Data.QuadVertexBufferPtr->Color = tintColor;
      s_Data.QuadVertexBufferPtr->TextureCoord = textureCoords[i];
      s_Data.QuadVertexBufferPtr->TextureIndex = textureIndex;
      s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
      s_Data.QuadVertexBufferPtr++;
    }

    s_Data.QuadIndexCount += 6;

    s_Data.Stats.QuadCount++;
  }

  Renderer2D::Statistics Renderer2D::GetStats()
  {
    return s_Data.Stats;
  }
  
  void Renderer2D::ResetStats()
  {
    memset(&s_Data.Stats, 0, sizeof(Renderer2D::Statistics));
  }
}