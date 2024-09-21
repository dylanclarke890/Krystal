#version 450 core
layout (location = 0) in vec4 i_Position;

uniform mat4 u_DirectionalLightSpaceMatrix;

void main()
{
  gl_Position = u_DirectionalLightSpaceMatrix * i_Position;
}