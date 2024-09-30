#version 450 core
in vec4 g_FragmentPosition;

#import "uniform-buffers.krys";

uniform int u_CurrentShadowCaster;

void main()
{
  PointLightShadowCaster caster = u_PointLightShadowCasters[u_CurrentShadowCaster];
  // get distance between fragment and light source
  float lightDistance = length(g_FragmentPosition.xyz - u_PointLights[caster.LightIndex].Position.xyz);
  // map to [0;1] range by dividing by far plane
  gl_FragDepth = lightDistance / caster.NearFarPlane.y;
}