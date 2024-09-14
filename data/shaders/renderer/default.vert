#version 450 core

layout(location = 0) in vec4 i_WorldSpacePosition;
layout(location = 1) in vec3 i_Normal;
layout(location = 2) in vec4 i_Color;
layout(location = 3) in vec2 i_TextureCoord;
layout(location = 4) in int i_TextureSlot;
layout(location = 5) in int i_SpecularSlot;
layout(location = 6) in int i_EmissionSlot;
layout(location = 7) in float i_Shininess;

layout (std140, binding = 0) uniform Shared
{
  mat4 u_ViewProjection;
  vec4 u_CameraPosition;
};
uniform mat4 u_DirectionalLightSpaceMatrix;

out vec3 v_FragmentPosition;
out vec4 v_DirectionalLightSpaceFragmentPosition;
out vec4 v_Color;
out vec3 v_Normal;
out vec2 v_TextureCoord;
flat out int v_TextureSlot;
flat out int v_SpecularSlot;
flat out int v_EmissionSlot;
flat out float v_Shininess;

void main()
{
  gl_Position = u_ViewProjection * i_WorldSpacePosition;
  v_FragmentPosition = vec3(i_WorldSpacePosition);
  v_DirectionalLightSpaceFragmentPosition = u_DirectionalLightSpaceMatrix * vec4(v_FragmentPosition, 1.0);
  v_Normal = i_Normal;
  v_Color = i_Color;
  v_TextureCoord = i_TextureCoord;
  v_TextureSlot = i_TextureSlot;
  v_SpecularSlot = i_SpecularSlot;
  v_EmissionSlot = i_EmissionSlot;
  v_Shininess = i_Shininess;
}