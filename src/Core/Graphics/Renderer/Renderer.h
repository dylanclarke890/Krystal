#pragma once

#include <array>

#include "Core.h"
#include "Window.h"
#include "Maths/Maths.h"
#include "Graphics/Graphics.h"
#include "Graphics/GraphicsContext.h"
#include "Graphics/Colors.h"
#include "Graphics/Camera/Camera.h"
#include "Graphics/Shaders/Shader.h"

namespace Krys
{
  constexpr uint32 MAX_VERTICES_PER_BATCH = 50000;
  constexpr uint32 MAX_INDICES_PER_BATCH = 200000;

  static VertexBufferLayout VERTEX_BUFFER_LAYOUT_BATCH = {
      {ShaderDataType::Float3, "i_Position"},
      {ShaderDataType::Float3, "i_Normal"},
      {ShaderDataType::Float4, "i_Color"},
      {ShaderDataType::Float2, "i_TextureCoords"},
      {ShaderDataType::Float3, "i_Tangent"},
  };

  struct BatchKey
  {
    PrimitiveType PrimitiveType;
    uint32 ShaderId;
    bool Indexed, CastsShadows;

    bool operator==(const BatchKey &other) const noexcept
    {
      return PrimitiveType == other.PrimitiveType &&
             ShaderId == other.ShaderId &&
             Indexed == other.Indexed &&
             CastsShadows == other.CastsShadows;
    }
  };

  struct BatchKeyHasher
  {
    size_t operator()(const BatchKey &k) const
    {
      size_t hash = 0;
      hash ^= std::hash<uint32>()(static_cast<uint32>(k.PrimitiveType)) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
      hash ^= std::hash<uint32>()(k.ShaderId) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
      hash ^= std::hash<bool>()(k.Indexed) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
      hash ^= std::hash<bool>()(k.CastsShadows) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
      return hash;
    }
  };

  struct Batch
  {
    BatchKey Key;
    List<Ref<SceneObject>> Objects;
  };

  struct RendererDefaults
  {
    Ref<Shader> Shader;
    Ref<Material> Material;
    Ref<Texture> DiffuseMap, SpecularMap, EmissionMap, NormalMap, DisplacementMap;
  };

  class Renderer
  {
  private:
    static Ref<Window> MainWindow;
    static Ref<GraphicsContext> Context;
    static Map<BatchKey, Batch, BatchKeyHasher> Batches;
    static Ref<VertexArray> BatchVertexArray;
    static Ref<VertexBuffer> BatchVertexBuffer;
    static Ref<IndexBuffer> BatchIndexBuffer;
    static Ref<UniformBuffer> SharedUniformBuffer;
    static Ref<Camera> ActiveCamera;
    static RendererDefaults Defaults;
    static LightingModelType LightingModel;
    static List<DirectionalLight> DirectionalLights;
    static List<Ref<Framebuffer>> DirectionalLightShadowFramebuffers;
    static Ref<Shader> DirectionalDepthMapShader;
    static bool IsWireFrameDrawingEnabled;

  public:
    static void Init(Ref<Window> window, Ref<GraphicsContext> context) noexcept;

    static void Begin(Ref<Camera> camera) noexcept;
    static void Draw(Ref<SceneObject> object) noexcept;
    static void End() noexcept;

    static void SetLightingModel(LightingModelType model) noexcept { LightingModel = model; }
    static void AddDirectionalLight(DirectionalLight &light) noexcept;

    static void SetWireFrameModeEnabled(bool enabled) noexcept { IsWireFrameDrawingEnabled = enabled; }

  private:
    static BatchKey GenerateBatchKey(Ref<SceneObject> object) noexcept;
    static Batch &GetOrAddBatch(const BatchKey &key) noexcept;

    static void FlushBatches() noexcept;
    static void SetDrawState(const Batch &batch) noexcept;

    static void ShadowPass() noexcept;
    static void GeometryPass() noexcept;
  };
}