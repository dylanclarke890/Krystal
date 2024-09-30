#version 420 core
layout (triangles) in;
layout (triangle_strip, max_vertices=18) out;

#import "uniform-buffers.krys";

out vec4 g_FragmentPosition; // (output per emitvertex)

uniform int u_CurrentShadowCaster;

void main()
{
  PointLightShadowCaster caster = u_PointLightShadowCasters[u_CurrentShadowCaster];
  for (int face = 0; face < 6; ++face)
  {
    gl_Layer = face; // built-in variable that specifies to which face we render.
    for (int i = 0; i < 3; i++) // for each triangle vertex
    {
      g_FragmentPosition = gl_in[i].gl_Position;
      gl_Position = caster.LightSpaceMatrices[face] * g_FragmentPosition;
      EmitVertex();
    }    
    EndPrimitive();
  }
}