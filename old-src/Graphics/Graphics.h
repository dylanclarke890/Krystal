#pragma once

#include "Types.h"
#include "Maths/Vector.h"
#include "Graphics/BufferLayout.h"

namespace Krys::Gfx
{
  using namespace Krys::Maths;

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

#pragma region Lights

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
  };

  struct PointLight : BaseLight
  {
    Vec3 Position;
    float Constant;
    float Linear;
    float Quadratic;
  };

  struct SpotLight : PointLight
  {
    Vec3 Direction;
    float InnerCutoff;
    float OuterCutoff;
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