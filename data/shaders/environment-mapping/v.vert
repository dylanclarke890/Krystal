#version 450

layout(location = 0) in vec4 i_WorldSpacePosition;
layout(location = 1) in vec3 i_Normal;
layout(location = 2) in vec4 i_Color;
layout(location = 3) in vec2 i_TextureCoord;
layout(location = 4) in int i_TextureSlot;
layout(location = 5) in int i_SpecularSlot;
layout(location = 6) in int i_EmissionSlot;
layout(location = 7) in float i_Shininess;

out vec3 v_Normal;
out vec3 v_Position;

layout (std140, binding = 0) uniform Shared
{
  mat4 u_ViewProjection;
  vec4 u_CameraPosition;
};

uniform mat4 u_Model;

void main()
{
  v_Normal = i_Normal;
  v_Position = vec3(i_WorldSpacePosition);
  gl_Position = u_ViewProjection * i_WorldSpacePosition;
}