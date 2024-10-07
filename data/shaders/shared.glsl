layout (std140, binding = ${UNIFORM_BUFFER_BINDING_SHARED}) uniform Shared
{
  mat4 u_ViewProjection;
  vec4 u_CameraPosition;
};

struct Material
{
  vec3 AmbientColor;
  vec3 DiffuseColor;
  vec3 SpecularColor;
  vec3 Tint;
  sampler2D DiffuseMap;
  sampler2D SpecularMap;
  sampler2D EmissionMap;
  sampler2D NormalMap;
  sampler2D DisplacementMap;
  float Shininess;
};