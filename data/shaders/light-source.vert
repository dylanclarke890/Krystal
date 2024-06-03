#version 450

layout(location = 0) in vec4 i_ModelPosition;

layout (std140, binding = 0) uniform Shared
{
  mat4 u_ViewProjection;
  vec3 u_CameraPosition;
};

void main()
{
  gl_Position = u_ViewProjection * i_ModelPosition;
}