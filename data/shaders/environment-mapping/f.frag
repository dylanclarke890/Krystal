#version 450

out vec4 o_Color;

in vec3 v_Normal;
in vec3 v_Position;

layout (std140, binding = 0) uniform Shared
{
  mat4 u_ViewProjection;
  vec4 u_CameraPosition;
};

uniform samplerCube skyboxTexture;

void Reflect()
{
  vec3 I = normalize(v_Position - vec3(u_CameraPosition));
  vec3 R = reflect(I, normalize(v_Normal));
  o_Color = vec4(texture(skyboxTexture, R).rgb, 1.0);
}

void Refract()
{
  float ratio = 1.00 / 1.52;
  vec3 I = normalize(v_Position - vec3(u_CameraPosition));
  vec3 R = refract(I, normalize(v_Normal), ratio);
  o_Color = vec4(texture(skyboxTexture, R).rgb, 1.0);
}

void main()
{
  Reflect();
}