#version 450 core

// NOTE: position, normal, tangent should be passed in world space. 
layout(location = 0) in vec4 i_Position;
layout(location = 1) in vec3 i_Normal;
layout(location = 2) in vec4 i_Color;
layout(location = 3) in vec2 i_TextureCoord;
layout(location = 4) in int i_TextureSlot;
layout(location = 5) in int i_SpecularSlot;
layout(location = 6) in int i_EmissionSlot;
layout(location = 7) in int i_NormalSlot;
layout(location = 8) in int i_DisplacementSlot;
layout(location = 9) in float i_Shininess;
layout(location = 10) in vec3 i_Tangent;

layout (std140, binding = 0) uniform Shared
{
  mat4 u_ViewProjection;
  vec4 u_CameraPosition;
};

#define MAX_DIRECTIONAL_LIGHTS 5
#define MAX_POINT_LIGHTS 32
#define MAX_SPOT_LIGHTS 32

struct DirectionalLight
{
  vec4 Ambient;
  vec4 Diffuse;
  vec4 Specular;

  bool Enabled;
  float Intensity;

  vec4 Direction;
};

struct PointLight
{
  vec4 Ambient;
  vec4 Diffuse;
  vec4 Specular;

  float Constant;
  float Linear;
  float Quadratic;

  bool Enabled;
  float Intensity;

  vec4 Position;
};

struct SpotLight
{
  vec4 Ambient;
  vec4 Diffuse;
  vec4 Specular;

  float Constant;
  float Linear;
  float Quadratic;

  bool Enabled;
  float Intensity;

  vec4 Direction;
  vec4 Position;

  float InnerCutoff;
  float OuterCutoff;
};

layout (std140, binding = 1) uniform Lights
{
  DirectionalLight u_DirectionalLights[MAX_DIRECTIONAL_LIGHTS];
  PointLight u_PointLights[MAX_POINT_LIGHTS];
  SpotLight u_SpotLights[MAX_SPOT_LIGHTS];
  int u_DirectionalLightCount;
  int u_PointLightCount;
  int u_SpotLightCount;
  bool u_UseBlinnLightingModel;
  bool u_LightingEnabled;
};

uniform mat4 u_DirectionalLightSpaceMatrix;

out vec3 v_FragmentPosition;
out vec4 v_DirectionalLightSpaceFragmentPosition;
out vec4 v_Color;
out vec3 v_Normal;
out vec2 v_TextureCoord;
out vec3 v_TangentLightPosition;
out vec3 v_TangentCameraPosition;
out vec3 v_TangentFragmentPosition;
flat out int v_TextureSlot;
flat out int v_SpecularSlot;
flat out int v_EmissionSlot;
flat out int v_NormalSlot;
flat out int v_DisplacementSlot;
flat out float v_Shininess;

void main()
{
  gl_Position = u_ViewProjection * i_Position;
  v_FragmentPosition = vec3(i_Position);
  v_DirectionalLightSpaceFragmentPosition = u_DirectionalLightSpaceMatrix * vec4(v_FragmentPosition, 1.0);
  v_Color = i_Color;
  v_TextureCoord = i_TextureCoord;
  v_TextureSlot = i_TextureSlot;
  v_SpecularSlot = i_SpecularSlot;
  v_EmissionSlot = i_EmissionSlot;
  v_NormalSlot = i_NormalSlot;
  v_DisplacementSlot = i_DisplacementSlot;
  v_Shininess = i_Shininess;

  vec3 T = normalize(i_Tangent);
  vec3 N = normalize(i_Normal);

  T = normalize(T - dot(T, N) * N);
  vec3 B = cross(N, T);
  
  mat3 TBN = transpose(mat3(T, B, N));   
  v_TangentLightPosition     = TBN * vec3(u_PointLights[0].Position.xyz);
  v_TangentCameraPosition    = TBN * vec3(u_CameraPosition);
  v_TangentFragmentPosition  = TBN * v_FragmentPosition;

  // Transform the vertex normal to tangent space if we don't have a normal map to sample
  v_Normal = v_NormalSlot == -1 ? TBN * i_Normal : i_Normal;
}