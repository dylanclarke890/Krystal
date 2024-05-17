#version 450

layout(location = 0) in vec4 position;

uniform mat4 u_ViewProjection;

void main()
{
  gl_Position = u_ViewProjection * position;
}