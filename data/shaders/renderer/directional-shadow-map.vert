#version 450 core

#import "uniform-buffers.krys";

layout (location = 0) in vec4 i_Position;

void main()
{
  gl_Position = u_DirectionalLights[0].LightSpaceMatrix * i_Position;
}