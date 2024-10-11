#pragma once

#include "Core.h"

#include "Maths/Maths.h"
#include "Buffer.h"
#include "BufferLayout.h"
#include "Framebuffer.h"
#include "Shaders/Shader.h"
#include "Transform.h"
#include "VertexArray.h"

namespace Krys
{
  const uint32 MATERIAL_DIFFUSE_MAP_SET = 1;
  const uint32 MATERIAL_SPECULAR_MAP_SET = 1 << 1;
  const uint32 MATERIAL_EMISSION_MAP_SET = 1 << 2;
  const uint32 MATERIAL_NORMAL_MAP_SET = 1 << 3;
  const uint32 MATERIAL_DISPLACEMENT_MAP_SET = 1 << 4;

  enum class PrimitiveType : ushort
  {
    Points,
    Lines,
    LineLoop,
    LineStrip,
    Triangles,
    TriangleStrip,
    TriangleFan
  };

  enum class LightingModelType : ushort
  {
    Phong,
    BlinnPhong
  };

  struct Vertex
  {
    Vec3 Position;
    Vec3 Normal;
    Vec4 Color;
    Vec2 TextureCoords;
    Vec3 Tangent;
  };

  struct Material
  {
    uint32 Id;
    Vec3 AmbientColor{1.0f}, DiffuseColor{1.0f}, SpecularColor{1.0f};
    Ref<Texture> DiffuseMap, SpecularMap, EmissionMap, NormalMap, DisplacementMap;
    Vec3 Tint = Vec3(1.0f);
    float Shininess = 32.0f;
    Ref<Shader> Shader;
    bool CastsShadows = true;

    NO_DISCARD uint32 GetAvailableTextures() const noexcept
    {
      uint32 flags = 0;

      if (DiffuseMap)
        flags |= MATERIAL_DIFFUSE_MAP_SET;

      if (SpecularMap)
        flags |= MATERIAL_SPECULAR_MAP_SET;

      if (EmissionMap)
        flags |= MATERIAL_EMISSION_MAP_SET;

      if (NormalMap)
        flags |= MATERIAL_NORMAL_MAP_SET;

      if (DisplacementMap)
        flags |= MATERIAL_DISPLACEMENT_MAP_SET;

      return flags;
    }
  };

  struct Mesh
  {
    PrimitiveType PrimitiveType = PrimitiveType::Triangles;
    List<Vertex> Vertices;
    List<uint32> Indices;
  };

  struct SceneObject
  {
    Ref<Material> Material;
    Ref<Mesh> Mesh;
    Ref<Transform> Transform;
    bool CastsShadows;
  };

  struct GraphicsCapabilities
  {
    // this *could* be more fine-grained. Some of the limits vary based on shader stage.
    int MaxInputComponents;
    int MaxOutputComponents;
    int MaxTextureImageUnits;
    int MaxTextureSize;
    int MaxTextureColorSamples;
    int MaxTextureDepthSamples;
    int MaxUniformComponents;
    int MaxUniformBlocks;
    int MaxVertexAttributes;
    int MaxRecommendedVertices;
    int MaxRecommendedIndices;
    int MaxFramebufferColorAttachments;
    int MaxFramebufferDrawBuffers;

    void Log() const
    {
      KRYS_LOG("Graphics Capabilities:");
      KRYS_LOG("MaxInputComponents: %d", MaxInputComponents);
      KRYS_LOG("MaxOutputComponents: %d", MaxOutputComponents);
      KRYS_LOG("MaxTextureImageUnits: %d", MaxTextureImageUnits);
      KRYS_LOG("MaxTextureSize: %d", MaxTextureSize);
      KRYS_LOG("MaxTextureColorSamples: %d", MaxTextureColorSamples);
      KRYS_LOG("MaxTextureDepthSamples: %d", MaxTextureDepthSamples);
      KRYS_LOG("MaxUniformComponents: %d", MaxUniformComponents);
      KRYS_LOG("MaxUniformBlocks: %d", MaxUniformBlocks);
      KRYS_LOG("MaxVertexAttributes: %d", MaxVertexAttributes);
      KRYS_LOG("MaxRecommendedVertices: %d", MaxRecommendedVertices);
      KRYS_LOG("MaxRecommendedIndices: %d", MaxRecommendedIndices);
      KRYS_LOG("MaxFramebufferColorAttachments: %d", MaxFramebufferColorAttachments);
      KRYS_LOG("MaxFramebufferDrawBuffers: %d", MaxFramebufferDrawBuffers);
    }
  };

  enum class RenderMode
  {
    Forward,
    Deferred
  };

#pragma region Lights

  struct BaseShadowSettings
  {
    float Bias = 0.005f;
    int ShadowMapResolution = 1024;
    bool Enabled;
    Vec2 NearFarPlane;
    Ref<Framebuffer> ShadowMapFramebuffer;
    Ref<Texture> DepthTexture;
  };

  struct DirectionalLightShadowSettings : BaseShadowSettings
  {
    BoundingBox<float> Bounds = {-10.0f, 10.0f, -10.0f, 10.0f};
    Mat4 LightSpaceMatrix;
  };

  struct PointLightShadowSettings : BaseShadowSettings
  {
    Mat4 LightSpaceMatrices[6];
  };

  struct SpotLightShadowSettings : BaseShadowSettings
  {
    Mat4 LightSpaceMatrix;
  };

  struct BaseLight
  {
    Vec3 Color = Vec3(1.0f);
    Vec3 Ambient;
    Vec3 Diffuse;
    Vec3 Specular;
    float Intensity = 1.0f;
    bool Enabled = true;
    bool CastsShadows = true;
  };

  struct DirectionalLight : BaseLight
  {
    Vec3 Direction;

    DirectionalLightShadowSettings ShadowSettings;
  };

  struct PointLight : BaseLight
  {
    Vec3 Position;
    float Constant;
    float Linear;
    float Quadratic;

    PointLightShadowSettings ShadowSettings;
  };

  struct SpotLight : PointLight
  {
    Vec3 Direction;
    float InnerCutoff;
    float OuterCutoff;

    SpotLightShadowSettings ShadowSettings;
  };

#pragma endregion Lights

#pragma region Uniform Buffers

  constexpr uint32 UNIFORM_BUFFER_BINDING_SHARED = 0;
  constexpr uint32 LIGHTING_MAX_DIRECTIONAL_LIGHTS = 2;
  constexpr uint32 LIGHTING_MAX_POINT_LIGHTS = 32;
  constexpr uint32 LIGHTING_MAX_SPOT_LIGHTS = 32;

  static UniformStructLayout UNIFORM_STRUCT_DIRECTIONAL_LIGHT = {
      {UniformDataType::Vec3, "Color"},
      {UniformDataType::Vec3, "Ambient"},
      {UniformDataType::Vec3, "Diffuse"},
      {UniformDataType::Vec3, "Specular"},
      {UniformDataType::Scalar, "Intensity"},
      {UniformDataType::Scalar, "Enabled"},
      {UniformDataType::Vec3, "Direction"},
      {UniformDataType::Scalar, "CastsShadows"},
      {UniformDataType::Scalar, "Bias"},
      {UniformDataType::Vec2, "NearFarPlane"},
      {UniformDataType::Mat4, "LightSpaceMatrix"},
  };

  static UniformStructLayout UNIFORM_STRUCT_POINT_LIGHT = {
      {UniformDataType::Vec3, "Color"},
      {UniformDataType::Vec3, "Ambient"},
      {UniformDataType::Vec3, "Diffuse"},
      {UniformDataType::Vec3, "Specular"},
      {UniformDataType::Scalar, "Intensity"},
      {UniformDataType::Scalar, "Enabled"},
      {UniformDataType::Vec3, "Position"},
      {UniformDataType::Scalar, "Constant"},
      {UniformDataType::Scalar, "Linear"},
      {UniformDataType::Scalar, "Quadratic"},
      {UniformDataType::Scalar, "CastsShadows"},
      {UniformDataType::Scalar, "Bias"},
      {UniformDataType::Vec2, "NearFarPlane"},
      // TODO: this should be an array instead.
      {UniformDataType::Mat4, "LightSpaceMatrices", 6},
  };

  static UniformStructLayout UNIFORM_STRUCT_SPOT_LIGHT = {
      {UniformDataType::Vec3, "Color"},
      {UniformDataType::Vec3, "Ambient"},
      {UniformDataType::Vec3, "Diffuse"},
      {UniformDataType::Vec3, "Specular"},
      {UniformDataType::Scalar, "Intensity"},
      {UniformDataType::Scalar, "Enabled"},
      {UniformDataType::Vec3, "Position"},
      {UniformDataType::Vec3, "Direction"},
      {UniformDataType::Scalar, "Constant"},
      {UniformDataType::Scalar, "Linear"},
      {UniformDataType::Scalar, "Quadratic"},
      {UniformDataType::Scalar, "InnerCutoff"},
      {UniformDataType::Scalar, "OuterCutoff"},
      {UniformDataType::Scalar, "CastsShadows"},
      {UniformDataType::Scalar, "Bias"},
      {UniformDataType::Vec2, "NearFarPlane"},
      {UniformDataType::Mat4, "LightSpaceMatrix"},
  };

  static UniformBufferLayout UNIFORM_BUFFER_LAYOUT_SHARED = {
      {UniformDataType::Mat4, "u_ViewProjection"},
      {UniformDataType::Vec3, "u_CameraPosition"},
      {UniformDataType::Struct, "u_DirectionalLights", UNIFORM_STRUCT_DIRECTIONAL_LIGHT, 2},
      {UniformDataType::Struct, "u_PointLights", UNIFORM_STRUCT_POINT_LIGHT, 32},
      {UniformDataType::Struct, "u_SpotLights", UNIFORM_STRUCT_SPOT_LIGHT, 32},
      {UniformDataType::Scalar, "u_DirectionalLightCount"},
      {UniformDataType::Scalar, "u_PointLightCount"},
      {UniformDataType::Scalar, "u_SpotLightCount"},
      {UniformDataType::Scalar, "u_UseBlinnLightingModel"},
  };

#pragma endregion Uniform Buffers

#pragma region Default Vertex Data

  /// @brief 4 floats per vertex, first 2 = position, last 2 = texture coords.
  static float SCREEN_QUAD_VERTICES[] = {
      -1.0f, 1.0f, 0.0f, 1.0f,
      -1.0f, -1.0f, 0.0f, 0.0f,
      1.0f, -1.0f, 1.0f, 0.0f,
      -1.0f, 1.0f, 0.0f, 1.0f,
      1.0f, -1.0f, 1.0f, 0.0f,
      1.0f, 1.0f, 1.0f, 1.0f};

#pragma endregion Default Vertex Data
}