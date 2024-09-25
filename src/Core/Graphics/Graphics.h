#pragma once

#include "Core.h"

#include "Maths/Maths.h"
#include "Graphics/BufferLayout.h"

namespace Krys
{
  // --------- TEXTURE SLOTS ---------
  const int CUBEMAP_SLOTS = 2;

  /// @brief Reserved texture slots always take up the first slots for each sampler type.
  /// Get the actual texture unit index via `ActiveTextureUnit.GetReservedSlotIndex()`.
  const uint RESERVED_TEXTURE_SLOT_SHADOW_MAP_2D = 0;

  /// @brief Reserved texture slots always take up the first slots for each sampler type.
  /// Get the actual texture unit index via `ActiveTextureUnit.GetReservedSlotIndex()`.
  const uint RESERVED_TEXTURE_SLOT_SHADOW_CUBEMAP = 0;
  // --------- TEXTURE SLOTS ---------

  // ----------- LIGHTING ------------
  constexpr uint32 LIGHTING_MAX_DIRECTIONAL_LIGHTS = 5;
  constexpr uint32 LIGHTING_MAX_POINT_LIGHTS = 32;
  constexpr uint32 LIGHTING_MAX_SPOT_LIGHTS = 32;
  constexpr uint SHADOW_MAP_RESOLUTION = 1024;

  // ----------- LIGHTING ------------

  // ------- DIRECTIONAL LIGHT -------

  struct DirectionalLight
  {
    Vec3 Ambient;
    Vec3 Diffuse;
    Vec3 Specular;

    bool Enabled;
    float Intensity;

    Vec3 Direction;
    Mat4 LightSpaceMatrix;
  };

  static UniformStructLayout DirectionalLightStructLayout = {
      {{UniformDataType::Vec3, "Ambient"},
       {UniformDataType::Vec3, "Diffuse"},
       {UniformDataType::Vec3, "Specular"},

       {UniformDataType::Scalar, "Enabled"},
       {UniformDataType::Scalar, "Intensity"},

       {UniformDataType::Vec3, "Direction"},
       {UniformDataType::Mat4, "LightSpaceMatrix"}}};

  // ------- DIRECTIONAL LIGHT -------
  // --------- POINT LIGHT -----------

  struct PointLight
  {
    Vec3 Ambient;
    Vec3 Diffuse;
    Vec3 Specular;

    float Constant;
    float Linear;
    float Quadratic;

    bool Enabled;
    float Intensity;
    float FarPlane;

    Vec3 Position;
  };

  static UniformStructLayout PointLightStructLayout = {
      {{UniformDataType::Vec3, "Ambient"},
       {UniformDataType::Vec3, "Diffuse"},
       {UniformDataType::Vec3, "Specular"},

       {UniformDataType::Scalar, "Constant"},
       {UniformDataType::Scalar, "Linear"},
       {UniformDataType::Scalar, "Quadratic"},

       {UniformDataType::Scalar, "Enabled"},
       {UniformDataType::Scalar, "Intensity"},
       {UniformDataType::Scalar, "FarPlane"},

       {UniformDataType::Vec3, "Position"}}};

  // --------- POINT LIGHT -----------

  // ---------- SPOT LIGHT -----------
  struct SpotLight
  {
    Vec3 Ambient;
    Vec3 Diffuse;
    Vec3 Specular;

    float Constant;
    float Linear;
    float Quadratic;

    bool Enabled;
    float Intensity;

    Vec3 Direction;
    Vec3 Position;

    float InnerCutoff;
    float OuterCutoff;
  };

  static UniformStructLayout SpotLightStructLayout = {
      {UniformDataType::Vec3, "Ambient"},
      {UniformDataType::Vec3, "Diffuse"},
      {UniformDataType::Vec3, "Specular"},

      {UniformDataType::Scalar, "Constant"},
      {UniformDataType::Scalar, "Linear"},
      {UniformDataType::Scalar, "Quadratic"},

      {UniformDataType::Scalar, "Enabled"},
      {UniformDataType::Scalar, "Intensity"},

      {UniformDataType::Vec3, "Direction"},
      {UniformDataType::Vec3, "Position"},

      {UniformDataType::Scalar, "InnerCutoff"},
      {UniformDataType::Scalar, "OuterCutoff"}};

  // ---------- SPOT LIGHT -----------

  // ----------- RENDERER ------------
  constexpr uint RENDERER_MAX_TRIANGLES = 10000;
  constexpr uint RENDERER_MAX_QUADS = RENDERER_MAX_TRIANGLES / 2;
  constexpr uint RENDERER_MAX_VERTICES = RENDERER_MAX_QUADS * 4;
  constexpr uint RENDERER_MAX_INDICES = RENDERER_MAX_QUADS * 6;
  static Vec4 RENDERER_DEFAULT_OBJECT_COLOR = {1.0f, 1.0f, 1.0f, 1.0f};
  // ----------- RENDERER ------------

  // ----------- DEFAULT VERTEX DATA ------------
  /// @brief 4 floats per vertex, first 2 = position, last 2 = texture coords.
  static float SCREEN_QUAD_VERTICES[] = {
      -1.0f, 1.0f, 0.0f, 1.0f,
      -1.0f, -1.0f, 0.0f, 0.0f,
      1.0f, -1.0f, 1.0f, 0.0f,
      -1.0f, 1.0f, 0.0f, 1.0f,
      1.0f, -1.0f, 1.0f, 0.0f,
      1.0f, 1.0f, 1.0f, 1.0f};

  constexpr Vec2 QUAD_DEFAULT_TEXTURE_COORDS[] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};
  constexpr Vec3 QUAD_SURFACE_NORMALS[] = {{0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}};
  constexpr Vec4 QUAD_LOCAL_SPACE_VERTICES[] = {{-0.5f, -0.5f, 0.0f, 1.0f}, {0.5f, -0.5f, 0.0f, 1.0f}, {0.5f, 0.5f, 0.0f, 1.0f}, {-0.5f, 0.5f, 0.0f, 1.0f}};

  constexpr Vec2 TRIANGLE_DEFAULT_TEXTURE_COORDS[] = {{0.0f, 0.0f}, {0.5f, 1.0f}, {1.0f, 0.0f}};
  constexpr Vec3 TRIANGLE_SURFACE_NORMALS[] = {{0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}};
  constexpr Vec4 TRIANGLE_LOCAL_SPACE_VERTICES[] = {{0.5f, -0.5f, 0.0f, 1.0f}, {-0.5f, -0.5f, 0.0f, 1.0f}, {0.0f, 0.5f, 0.0f, 1.0f}};

  // TODO: We don't have texture coords for cubes yet, we currently each face as if it were a 2d quad.
  constexpr Vec4 CUBE_LOCAL_SPACE_VERTICES[] = {
      // Front face
      {-0.5f, -0.5f, 0.5f, 1.0f}, // 0
      {0.5f, -0.5f, 0.5f, 1.0f},  // 1
      {0.5f, 0.5f, 0.5f, 1.0f},   // 2
      {-0.5f, 0.5f, 0.5f, 1.0f},  // 3

      // Back face
      {-0.5f, -0.5f, -0.5f, 1.0f}, // 4
      {0.5f, -0.5f, -0.5f, 1.0f},  // 5
      {0.5f, 0.5f, -0.5f, 1.0f},   // 6
      {-0.5f, 0.5f, -0.5f, 1.0f},  // 7

      // Left face
      {-0.5f, -0.5f, -0.5f, 1.0f}, // 8
      {-0.5f, -0.5f, 0.5f, 1.0f},  // 9
      {-0.5f, 0.5f, 0.5f, 1.0f},   // 10
      {-0.5f, 0.5f, -0.5f, 1.0f},  // 11

      // Right face
      {0.5f, -0.5f, -0.5f, 1.0f}, // 12
      {0.5f, -0.5f, 0.5f, 1.0f},  // 13
      {0.5f, 0.5f, 0.5f, 1.0f},   // 14
      {0.5f, 0.5f, -0.5f, 1.0f},  // 15

      // Top face
      {-0.5f, 0.5f, 0.5f, 1.0f},  // 16
      {0.5f, 0.5f, 0.5f, 1.0f},   // 17
      {0.5f, 0.5f, -0.5f, 1.0f},  // 18
      {-0.5f, 0.5f, -0.5f, 1.0f}, // 19

      // Bottom face
      {-0.5f, -0.5f, 0.5f, 1.0f}, // 20
      {0.5f, -0.5f, 0.5f, 1.0f},  // 21
      {0.5f, -0.5f, -0.5f, 1.0f}, // 22
      {-0.5f, -0.5f, -0.5f, 1.0f} // 23
  };
  constexpr Vec3 CUBE_SURFACE_NORMALS[] = {
      {0.0f, 0.0f, 1.0f}, // Front face
      {0.0f, 0.0f, 1.0f},
      {0.0f, 0.0f, 1.0f},
      {0.0f, 0.0f, 1.0f},

      {0.0f, 0.0f, -1.0f}, // Back face
      {0.0f, 0.0f, -1.0f},
      {0.0f, 0.0f, -1.0f},
      {0.0f, 0.0f, -1.0f},

      {-1.0f, 0.0f, 0.0f}, // Left face
      {-1.0f, 0.0f, 0.0f},
      {-1.0f, 0.0f, 0.0f},
      {-1.0f, 0.0f, 0.0f},

      {1.0f, 0.0f, 0.0f}, // Right face
      {1.0f, 0.0f, 0.0f},
      {1.0f, 0.0f, 0.0f},
      {1.0f, 0.0f, 0.0f},

      {0.0f, 1.0f, 0.0f}, // Top face
      {0.0f, 1.0f, 0.0f},
      {0.0f, 1.0f, 0.0f},
      {0.0f, 1.0f, 0.0f},

      {0.0f, -1.0f, 0.0f}, // Bottom face
      {0.0f, -1.0f, 0.0f},
      {0.0f, -1.0f, 0.0f},
      {0.0f, -1.0f, 0.0f}};
  // ----------- DEFAULT VERTEX DATA ------------

  // -------- UNIFORM BUFFER BINDINGS --------

  constexpr uint32 UNIFORM_BUFFER_BINDING_SHARED = 0;
  constexpr uint32 UNIFORM_BUFFER_BINDING_LIGHT = 1;

  // -------- UNIFORM BUFFER BINDINGS --------

  // -------- UNIFORM BUFFER LAYOUTS ---------

  static UniformBufferLayout UNIFORM_BUFFER_LAYOUT_SHARED = {
      {UniformDataType::Mat4, "u_ViewProjection"},
      {UniformDataType::Vec3, "u_CameraPosition"}};

  static UniformBufferLayout UNIFORM_BUFFER_LAYOUT_LIGHT = {
      {UniformDataType::Struct, "u_DirectionalLights", DirectionalLightStructLayout, LIGHTING_MAX_DIRECTIONAL_LIGHTS},
      {UniformDataType::Struct, "u_PointLights", PointLightStructLayout, LIGHTING_MAX_POINT_LIGHTS},
      {UniformDataType::Struct, "u_SpotLights", SpotLightStructLayout, LIGHTING_MAX_SPOT_LIGHTS},
      {UniformDataType::Scalar, "u_DirectionalLightCount"},
      {UniformDataType::Scalar, "u_PointLightCount"},
      {UniformDataType::Scalar, "u_SpotLightCount"},
      {UniformDataType::Scalar, "u_UseBlinnLightingModel"},
      {UniformDataType::Scalar, "u_LightingEnabled"},
      {UniformDataType::Scalar, "u_Texture2DShadowMapSlotIndex"},
      {UniformDataType::Scalar, "u_CubemapShadowMapSlotIndex"}};

  // -------- UNIFORM BUFFER LAYOUTS ---------

  // -------- VERTEX BUFFER LAYOUTS ----------

  static VertexBufferLayout VERTEX_BUFFER_LAYOUT_SCREEN = {
      {{ShaderDataType::Float2, "i_Position"},
       {ShaderDataType::Float2, "i_TextureCoord"}}};

  static VertexBufferLayout VERTEX_BUFFER_LAYOUT_DEFAULT = {
      {ShaderDataType::Float4, "i_Position"},
      {ShaderDataType::Float3, "i_Normal"},
      {ShaderDataType::Float4, "i_Color"},
      {ShaderDataType::Float2, "i_TextureCoord"},
      {ShaderDataType::Int, "i_TextureSlot"},
      {ShaderDataType::Int, "i_SpecularSlot"},
      {ShaderDataType::Int, "i_EmissionSlot"},
      {ShaderDataType::Int, "i_NormalSlot"},
      {ShaderDataType::Int, "i_DisplacementSlot"},
      {ShaderDataType::Float, "i_Shininess"},
      {ShaderDataType::Float3, "i_Tangent"}};

  // -------- VERTEX BUFFER LAYOUTS ----------
}