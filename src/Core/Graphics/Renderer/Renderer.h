#pragma once

#include <array>
#include <algorithm>

#include "Core.h"
#include "Window.h"
#include "Graphics/GraphicsContext.h"
#include "Graphics/Colors.h"
#include "Graphics/Camera/Camera.h"
#include "Graphics/Camera/Orthographic.h"
#include "Graphics/Transform.h"
#include "Graphics/Mesh.h"
#include "Graphics/Lighting/LightManager.h"

namespace Krys
{
  constexpr uint REN2D_MAX_TRIANGLES = 10000;
  constexpr uint REN2D_MAX_QUADS = REN2D_MAX_TRIANGLES / 2;
  constexpr uint REN2D_MAX_VERTICES = REN2D_MAX_QUADS * 4;
  constexpr uint REN2D_MAX_INDICES = REN2D_MAX_QUADS * 6;
  constexpr int REN2D_RESERVED_TEXTURE_SLOTS = 2;
  static Vec4 REN2D_DEFAULT_COLOR = {1.0f, 1.0f, 1.0f, 1.0f};

  struct VertexData
  {
    Vec4 Position;
    Vec3 Normal;
    Vec4 Color;
    Vec2 TextureCoords;
    int TextureSlotIndex;
    int SpecularTextureSlotIndex;
    int EmissionTextureSlotIndex;
    int NormalTextureSlotIndex;
    int DisplacementTextureSlotIndex;
    float Shininess;
    Vec3 Tangent;
  };

  struct TextureData
  {
    const Vec2 *TextureCoords;
    Vec4 Tint;
    int Texture = -1;
    int Specular = -1;
    int Emission = -1;
    int Normal = -1;
    int Displacement = -1;
    float Shininess = 32.0f;
  };

  struct DeferredRendererData
  {
    Ref<Framebuffer> GBuffer;
    Ref<Texture2D> GPosition, GNormal, GAlbedoSpecular;
  };

  enum class RenderMode
  {
    Forward,
    Deferred
  };

  struct TextureBindingInfo
  {
    std::vector<Ref<Texture>> Slots;
    int CurrentSlotIndex, MaxSlots, ReservedSlots, BindingOffset;
    std::vector<int> Samplers;

    void Bind()
    {
      for (int i = 0; i < CurrentSlotIndex; i++)
        Slots[i]->Bind(i + BindingOffset);
    }

    bool HasSlotsRemaining()
    {
      return MaxSlots - (CurrentSlotIndex + 1) > 0;
    }
  };

  struct ActiveTextureUnits
  {
    TextureBindingInfo Texture2D;
    TextureBindingInfo TextureCubemap;

    void Bind()
    {
      Texture2D.Bind();
      TextureCubemap.Bind();
    }

    void SetSamplerUniforms(std::vector<Ref<Shader>> shaders)
    {
      std::for_each(shaders.begin(), shaders.end(),
                    [&](auto s)
                    { SetSamplerUniforms(s); });
    }

    void SetSamplerUniforms(Ref<Shader> shader)
    {
      shader->TrySetUniform("u_Textures", Texture2D.Samplers.data(), Texture2D.MaxSlots);
      shader->TrySetUniform("u_Cubemaps", TextureCubemap.Samplers.data(), TextureCubemap.MaxSlots);
    }

    NO_DISCARD int MaxUnits() const { return Texture2D.MaxSlots + TextureCubemap.MaxSlots; }
  };

  inline static void CalcTangentSpace(VertexData &v1, VertexData &v2, VertexData &v3, Mat3 &normalMatrix) noexcept
  {
    Vec3 edge1 = v2.Position - v1.Position;
    Vec3 edge2 = v3.Position - v1.Position;

    Vec2 deltaUV1 = v2.TextureCoords - v1.TextureCoords;
    Vec2 deltaUV2 = v3.TextureCoords - v1.TextureCoords;

    float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

    Vec3 tangent;
    tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
    tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
    tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

    tangent = glm::normalize(normalMatrix * tangent);

    v1.Tangent = tangent;
    v2.Tangent = tangent;
    v3.Tangent = tangent;
  }

  class Renderer
  {
  private:
    static Ref<GraphicsContext> Context;
    static Ref<Window> AppWindow;
    static Ref<Framebuffer> MultiSampleFramebuffer, SingleSampleFramebuffer,
        DirectionalShadowMapFramebuffer, OmniDirectionalShadowMapFramebuffer,
        ExtractBrightnessFramebuffer, PostProcessingFramebuffer;
    static Ref<Shader> DefaultShader, DirectionalShadowMapShader, OmniDirectionalShadowMapShader,
        LightSourceShader, SkyboxShader, PostProcessingShader, ActiveShader, ExtractBrightnessShader, GaussianBlurShader;
    static Ref<PingPongFramebuffer> GaussianBlurFramebuffer;
    static Ref<VertexArray> DefaultVertexArray, ScreenQuadVertexArray, SkyboxVertexArray;
    static Ref<VertexBuffer> DefaultVertexBuffer, ScreenQuadVertexBuffer, SkyboxVertexBuffer;
    static Ref<IndexBuffer> DefaultIndexBuffer;
    static Ref<UniformBuffer> SharedUniformBuffer;
    static Ref<TextureCubemap> SkyboxCubemap;

    static Unique<std::array<VertexData, REN2D_MAX_VERTICES>> Vertices;
    static Unique<std::array<uint32, REN2D_MAX_INDICES>> Indices;
    static uint VertexCount, IndexCount;

    static ActiveTextureUnits TextureUnits;

    static Ref<Camera> ActiveCamera;
    static bool IsPostProcessingEnabled, IsWireFrameDrawingEnabled;

    static Ref<Transform> LightSourceTransform;

    static DeferredRendererData DeferredRenderer;
    static RenderMode CurrentRenderMode;

  public:
    static LightManager Lights;

    static void Init(Ref<Window> window, Ref<GraphicsContext> ctx);
    static void Shutdown();

    static void DrawTriangle(Ref<Transform> transform, Vec4 &color);
    static void DrawTriangle(Ref<Transform> transform, Ref<Material> material);
    static void DrawTriangle(Ref<Transform> transform, Ref<SubTexture2D> subTexture, Vec4 &tint = REN2D_DEFAULT_COLOR);

    static void DrawQuad(Ref<Transform> transform, Vec4 &color);
    static void DrawQuad(Ref<Transform> transform, Ref<Material> material);
    static void DrawQuad(Ref<Transform> transform, Ref<SubTexture2D> subTexture, Vec4 &tint = REN2D_DEFAULT_COLOR);

    static void DrawCube(Ref<Transform> transform, Vec4 &color);
    static void DrawCube(Ref<Transform> transform, Ref<Material> material);
    static void DrawCube(Ref<Transform> transform, Ref<TextureCubemap> cubemap);
    static void DrawCube(Ref<Transform> transform, Ref<SubTexture2D> subTexture, Vec4 &tint = REN2D_DEFAULT_COLOR);

    static void SetSkybox(std::array<string, 6> pathsToFaces);
    static void SetPostProcessingEnabled(bool enabled);
    static void SetWireFrameModeEnabled(bool enabled);

    static void BeginScene(Ref<Camera> camera, Ref<Shader> shaderToUse = nullptr);
    static void NextBatch();
    static void EndScene();

  private:
    static void InitFramebuffers();
    static void InitShaders();
    static void InitBuffers();
    static void InitVertexArrays();
    static void InitLighting();
    static void InitDeferredRenderer();
    static void InitTextureUnits();

    static void Reset();
    static void Flush();
    static void ForwardRender();
    static void DeferredRender();

    static void DrawQuad(Ref<Transform> transform, TextureData &textureData);
    static void DrawTriangle(Ref<Transform> transform, TextureData &textureData);
    static void DrawCube(Ref<Transform> transform, TextureData &textureData);

    static void AddVertices(VertexData *vertices, uint vertexCount, uint32 *indices, uint32 indexCount);

    static int GetTextureSlotIndex(Ref<Texture2D> texture);
    static int GetTextureSlotIndex(Ref<TextureCubemap> texture);
    static int GetTextureSlotIndex(Ref<Texture> texture, TextureBindingInfo &bindingInfo);
  };
}