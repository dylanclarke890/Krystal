#version 450 core
in vec4 g_FragmentPosition;

uniform vec3 u_LightPosition;
uniform float u_FarPlane;

void main()
{
  // get distance between fragment and light source
  float lightDistance = length(g_FragmentPosition.xyz - u_LightPosition);
  // map to [0;1] range by dividing by u_FarPlane
  gl_FragDepth = lightDistance / u_FarPlane;
}