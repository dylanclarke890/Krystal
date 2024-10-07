#pragma once

#include "Core.h"

#include "Maths/Maths.h"
#include "Buffer.h"
#include "BufferLayout.h"
#include "Framebuffer.h"
#include "Shaders/Shader.h"
#include "VertexArray.h"

namespace Krys
{
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

  struct Transform
  {
    Vec3 Position, Size, Rotation;

    Transform(Vec3 position, Vec3 size, Vec3 rotation = {}) noexcept : Position(position), Size(size), Rotation(rotation) {}
    Transform(Vec3 position, Vec3 size, float rotation) noexcept : Transform(position, size, {0.0f, 0.0f, rotation}) {}
    Transform(Vec2 position, Vec2 size, float rotation = 0.0f) noexcept : Transform({position, 0.0f}, {size, 1.0f}, {0.0f, 0.0f, rotation}) {}

    Mat4 GetModelMatrix() const noexcept
    {
      Mat4 model = glm::translate(MAT4_I, Position);
      if (Rotation.x)
        model *= glm::rotate(MAT4_I, glm::radians(Rotation.x), ROTATE_AXIS_X);

      if (Rotation.y)
        model *= glm::rotate(MAT4_I, glm::radians(Rotation.y), ROTATE_AXIS_Y);

      if (Rotation.z)
        model *= glm::rotate(MAT4_I, glm::radians(Rotation.z), ROTATE_AXIS_Z);

      return model * glm::scale(MAT4_I, Size);
    }
  };

  struct Material
  {
    uint32 Id;
    Vec3 AmbientColor{1.0f}, DiffuseColor{1.0f}, SpecularColor{1.0f};
    Ref<Texture> DiffuseMap, SpecularMap, EmissionMap, NormalMap, DisplacementMap;
    Vec3 Tint = Vec3(1.0f);
    float Shininess = 32.0f;
    Ref<Shader> Shader;
  };

  struct Mesh
  {
    PrimitiveType PrimitiveType;
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

  struct VertexData
  {
    Vec4 Position;
    Vec3 Normal;
    Vec4 Color;
    Vec2 TextureCoords;
    int TextureSlotIndex = -1;
    int SpecularTextureSlotIndex = -1;
    int EmissionTextureSlotIndex = -1;
    int NormalTextureSlotIndex = -1;
    int DisplacementTextureSlotIndex = -1;
    float Shininess = 32;
    Vec3 Tangent;
  };

  // struct Model
  // {
  //   /// @brief The file this model was loaded from.
  //   string Path;

  //   /// @brief The scene index for this model.
  //   uint32 Index;

  //   /// @brief Whether matrices in the model are column-major.
  //   bool ColumnMajor;

  //   List<Ref<Mesh>> Meshes;
  // };

#pragma region Renderer

  constexpr uint RENDERER_MAX_TRIANGLES = 10000;
  constexpr uint RENDERER_MAX_QUADS = RENDERER_MAX_TRIANGLES / 2;
  constexpr uint RENDERER_MAX_VERTICES = RENDERER_MAX_QUADS * 4;
  constexpr uint RENDERER_MAX_INDICES = RENDERER_MAX_QUADS * 6;
  static Vec4 RENDERER_DEFAULT_OBJECT_COLOR = {1.0f, 1.0f, 1.0f, 1.0f};

  // TODO: this *could* be more fine-grained. Some of the limits vary based on shader stage.
  struct GraphicsCapabilities
  {
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
      {ShaderDataType::Float3, "i_Tangent"},
  };

  static VertexBufferLayout VERTEX_BUFFER_LAYOUT_SCREEN = {
      {ShaderDataType::Float2, "i_Position"},
      {ShaderDataType::Float2, "i_TextureCoord"},
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

  enum class RenderMode
  {
    Forward,
    Deferred
  };

  enum class ReservedSlotType
  {
    DirectionalShadowMap,
    PointLightShadowMap,
    SpotLightShadowMap,
  };

#pragma endregion Renderer

#pragma region Lighting

  constexpr uint CUBEMAP_SLOTS = 2;

  constexpr uint LIGHTING_MAX_DIRECTIONAL_LIGHTS = 2;
  constexpr uint LIGHTING_MAX_DIRECTIONAL_SHADOW_CASTERS = 2;

  constexpr uint LIGHTING_MAX_POINT_LIGHTS = 2;
  constexpr uint LIGHTING_MAX_POINT_LIGHT_SHADOW_CASTERS = 2;

  constexpr uint LIGHTING_MAX_SPOT_LIGHTS = 2;
  constexpr uint LIGHTING_MAX_SPOT_LIGHT_SHADOW_CASTERS = 2;

  constexpr float LIGHTING_DEFAULT_SHADOW_BIAS = 0.005f;
  constexpr uint LIGHTING_DEFAULT_SHADOW_MAP_RESOLUTION = 1024;

  struct Light
  {
    Vec3 Ambient;
    Vec3 Diffuse;
    Vec3 Specular;

    float Intensity;

    bool Enabled;
  };

  struct ShadowCaster
  {
    float Bias = LIGHTING_DEFAULT_SHADOW_BIAS;
    int LightIndex;
    int ShadowMapResolution = LIGHTING_DEFAULT_SHADOW_MAP_RESOLUTION;
    int ShadowMapSlotIndex;
    bool Enabled;
    Vec2 NearFarPlane;
    Ref<Framebuffer> ShadowMapFramebuffer;
    Ref<Texture> DepthTexture;
  };

  struct LightSettings
  {
    bool CastShadows;
    Vec2 NearFarPlane = Vec2(1.0f, 25.0f);
  };

#pragma endregion Lighting

#pragma region Directional Light

  struct DirectionalLight : Light
  {
    Vec3 Direction;
  };

  struct DirectionalShadowCaster : ShadowCaster
  {
    RectBounds Bounds = {-10.0f, 10.0f, -10.0f, 10.0f};
    Mat4 LightSpaceMatrix;
  };

  static UniformStructLayout DirectionalLightStructLayout = {{
      {UniformDataType::Vec3, "Ambient"},
      {UniformDataType::Vec3, "Diffuse"},
      {UniformDataType::Vec3, "Specular"},

      {UniformDataType::Scalar, "Enabled"},
      {UniformDataType::Scalar, "Intensity"},

      {UniformDataType::Vec3, "Direction"},
  }};

  static UniformStructLayout DirectionalShadowCasterStructLayout = {{
      {UniformDataType::Scalar, "Bias"},
      {UniformDataType::Scalar, "LightIndex"},
      {UniformDataType::Scalar, "ShadowMapResolution"},
      {UniformDataType::Scalar, "ShadowMapSlotIndex"},
      {UniformDataType::Scalar, "Enabled"},
      {UniformDataType::Vec2, "NearFarPlane"},
      {UniformDataType::Mat4, "LightSpaceMatrix"},
  }};

#pragma endregion Directional Light

#pragma region Point Light

  struct PointLight : Light
  {
    float Constant;
    float Linear;
    float Quadratic;

    Vec3 Position;
  };

  struct PointLightShadowCaster : ShadowCaster
  {
    Mat4 LightSpaceMatrices[6];
  };

  static UniformStructLayout PointLightStructLayout = {
      {UniformDataType::Vec3, "Ambient"},
      {UniformDataType::Vec3, "Diffuse"},
      {UniformDataType::Vec3, "Specular"},

      {UniformDataType::Scalar, "Constant"},
      {UniformDataType::Scalar, "Linear"},
      {UniformDataType::Scalar, "Quadratic"},

      {UniformDataType::Scalar, "Enabled"},
      {UniformDataType::Scalar, "Intensity"},

      {UniformDataType::Vec3, "Position"},
  };

  static UniformStructLayout PointLightShadowCasterStructLayout = {
      {UniformDataType::Scalar, "Bias"},
      {UniformDataType::Scalar, "LightIndex"},
      {UniformDataType::Scalar, "ShadowMapResolution"},
      {UniformDataType::Scalar, "ShadowMapSlotIndex"},
      {UniformDataType::Scalar, "Enabled"},
      {UniformDataType::Vec2, "NearFarPlane"},
      // TODO: this should be an array instead.
      {UniformDataType::Mat4, "LightSpaceMatrices", 6},
  };

#pragma endregion Point Light

#pragma region Spot Light

  struct SpotLight : Light
  {
    float Constant;
    float Linear;
    float Quadratic;

    Vec3 Direction;
    Vec3 Position;

    float InnerCutoff;
    float OuterCutoff;
  };

  struct SpotLightShadowCaster : ShadowCaster
  {
    Mat4 LightSpaceMatrix;
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

  static UniformStructLayout SpotLightShadowCasterStructLayout = {
      {UniformDataType::Scalar, "Bias"},
      {UniformDataType::Scalar, "LightIndex"},
      {UniformDataType::Scalar, "ShadowMapResolution"},
      {UniformDataType::Scalar, "ShadowMapSlotIndex"},
      {UniformDataType::Scalar, "Enabled"},
      {UniformDataType::Vec2, "NearFarPlane"},
      {UniformDataType::Mat4, "LightSpaceMatrix"},
  };

#pragma endregion Spot Light

#pragma region Default Vertex Data

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

  // TODO: We don't have texture coords for cubes yet, we currently texture each face as if it were a 2d quad.
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

#pragma endregion Default Vertex Data

#pragma region Uniform Buffers

  constexpr uint32 UNIFORM_BUFFER_BINDING_SHARED = 0;
  constexpr uint32 UNIFORM_BUFFER_BINDING_LIGHTS = 1;

  static UniformBufferLayout UNIFORM_BUFFER_LAYOUT_SHARED = {
      {UniformDataType::Mat4, "u_ViewProjection"},
      {UniformDataType::Vec3, "u_CameraPosition"}};

  static UniformBufferLayout UNIFORM_BUFFER_LAYOUT_LIGHTS = {
      {UniformDataType::Struct, "u_DirectionalLights", DirectionalLightStructLayout, LIGHTING_MAX_DIRECTIONAL_LIGHTS},
      {UniformDataType::Struct, "u_DirectionalShadowCasters", DirectionalShadowCasterStructLayout, LIGHTING_MAX_DIRECTIONAL_SHADOW_CASTERS},
      {UniformDataType::Scalar, "u_DirectionalLightCount"},
      {UniformDataType::Scalar, "u_DirectionalShadowCasterCount"},

      {UniformDataType::Struct, "u_PointLights", PointLightStructLayout, LIGHTING_MAX_POINT_LIGHTS},
      {UniformDataType::Struct, "u_PointLightShadowCasters", PointLightShadowCasterStructLayout, LIGHTING_MAX_POINT_LIGHT_SHADOW_CASTERS},
      {UniformDataType::Scalar, "u_PointLightCount"},
      {UniformDataType::Scalar, "u_PointLightShadowCasterCount"},

      {UniformDataType::Struct, "u_SpotLights", SpotLightStructLayout, LIGHTING_MAX_SPOT_LIGHTS},
      {UniformDataType::Struct, "u_SpotLightShadowCasters", SpotLightShadowCasterStructLayout, LIGHTING_MAX_SPOT_LIGHT_SHADOW_CASTERS},
      {UniformDataType::Scalar, "u_SpotLightCount"},
      {UniformDataType::Scalar, "u_SpotLightShadowCasterCount"},

      {UniformDataType::Scalar, "u_LightingEnabled"},
      {UniformDataType::Scalar, "u_ShadowsEnabled"},

      {UniformDataType::Scalar, "u_UseBlinnLightingModel"},
  };

#pragma endregion Uniform Buffers
}