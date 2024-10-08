#define MATERIAL_DIFFUSE_MAP_SET 1
#define MATERIAL_SPECULAR_MAP_SET 1 << 1
#define MATERIAL_EMISSION_MAP_SET 1 << 2
#define MATERIAL_NORMAL_MAP_SET 1 << 3
#define MATERIAL_DISPLACEMENT_MAP_SET 1 << 4

struct Material
{
  vec3 AmbientColor;
  vec3 DiffuseColor;
  vec3 SpecularColor;
  vec3 Tint;
  float Shininess;
  bool ReceivesShadows;
  int AvailableTextures;
  sampler2D DiffuseMap;
  sampler2D SpecularMap;
  sampler2D EmissionMap;
  sampler2D NormalMap;
  sampler2D DisplacementMap;
};

struct DirectionalLight
{
  vec4 Color;
  vec4 Ambient;
  vec4 Diffuse;
  vec4 Specular;
  float Intensity;
  bool Enabled;
  vec4 Direction;
  bool CastsShadows;
  float Bias;
  vec2 NearFarPlane;
  mat4 LightSpaceMatrix;
};

struct PointLight
{
  vec4 Position;
  vec4 Color;
  vec4 Ambient;
  vec4 Diffuse;
  vec4 Specular;
  float Intensity;
  bool Enabled;
  float Constant;
  float Linear;
  float Quadratic;
  bool CastsShadows;
  float Bias;
  vec2 NearFarPlane;
  mat4 LightSpaceMatrices[6];
};

struct SpotLight
{
  vec4 Position;
  vec4 Color;
  vec4 Ambient;
  vec4 Diffuse;
  vec4 Specular;
  float Intensity;
  bool Enabled;
  float Constant;
  float Linear;
  float Quadratic;
  vec4 Direction;
  float InnerCutoff;
  float OuterCutoff;
  bool CastsShadows;
  float Bias;
  vec2 NearFarPlane;
  mat4 LightSpaceMatrix;
};

#define MAX_DIRECTIONAL_LIGHTS ${MAX_DIRECTIONAL_LIGHTS}
#define MAX_POINT_LIGHTS ${MAX_POINT_LIGHTS}
#define MAX_SPOT_LIGHTS ${MAX_SPOT_LIGHTS}
layout (std140, binding = ${UNIFORM_BUFFER_BINDING_SHARED}) uniform Shared
{
  mat4 u_ViewProjection;
  vec4 u_CameraPosition;
  DirectionalLight u_DirectionalLights[MAX_DIRECTIONAL_LIGHTS];
  PointLight u_PointLights[MAX_POINT_LIGHTS];
  SpotLight u_SpotLights[MAX_SPOT_LIGHTS];
  int u_DirectionalLightCount;
  int u_PointLightCount;
  int u_SpotLightCount;
};