#version 450 core

#import "uniform-buffers.krys";

layout (location = 0) in vec4 i_Position;

uniform int u_CurrentShadowCaster;

void main()
{
  SpotLightShadowCaster caster = u_SpotLightShadowCasters[u_CurrentShadowCaster];
  gl_Position = caster.LightSpaceMatrix * i_Position;
}