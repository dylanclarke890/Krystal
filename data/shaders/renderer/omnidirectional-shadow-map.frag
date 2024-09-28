#version 450 core
in vec4 g_FragmentPosition;

#import "uniform-buffers.krys";

void main()
{
  // get distance between fragment and light source
  float lightDistance = length(g_FragmentPosition.xyz - u_PointLights[0].Position.xyz);
  // map to [0;1] range by dividing by far plane
  gl_FragDepth = lightDistance / u_PointLightShadowCasters[0].NearFarPlane.y;
}