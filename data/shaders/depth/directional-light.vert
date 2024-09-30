#version 450 core

#import "uniform-buffers.krys";

layout (location = 0) in vec4 i_Position;

uniform int u_CurrentShadowCaster;

void main()
{
  DirectionalShadowCaster caster = u_DirectionalShadowCasters[u_CurrentShadowCaster];
  gl_Position = caster.LightSpaceMatrix * i_Position;
}