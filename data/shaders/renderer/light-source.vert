#version 450

layout(location = 0) in vec4 i_WorldSpacePosition;
layout(location = 2) in vec4 i_Color;

layout (std140, binding = 0) uniform Shared
{
  mat4 u_ViewProjection;
  vec4 u_CameraPosition;
};

out vec4 v_Color;

void main()
{
  gl_Position = u_ViewProjection * i_WorldSpacePosition;
  v_Color = i_Color;
}