#version 450

layout(location = 0) in vec4 i_ModelPosition;
layout(location = 1) in vec3 i_Normal;
layout(location = 2) in vec4 i_Color;
layout(location = 3) in vec2 i_TextureCoord;
layout(location = 4) in int i_TextureSlot;
layout(location = 5) in int i_SpecularSlot;
layout(location = 6) in int i_EmissionSlot;
layout(location = 7) in float i_Shininess;

out vec3 v_FragmentPosition;
out vec4 v_Color;
out vec3 v_Normal;
out vec2 v_TextureCoord;
flat out int v_TextureSlot;
flat out int v_SpecularSlot;
flat out int v_EmissionSlot;
flat out float v_Shininess;

layout (std140, binding = 0) uniform Shared
{
  mat4 u_ViewProjection;
  vec3 u_CameraPosition;
};

void main()
{
  gl_Position = u_ViewProjection * i_ModelPosition;
  v_FragmentPosition = vec3(i_ModelPosition);
  v_Normal = i_Normal;
  v_Color = i_Color;
  v_TextureCoord = i_TextureCoord;
  v_TextureSlot = i_TextureSlot;
  v_SpecularSlot = i_SpecularSlot;
  v_EmissionSlot = i_EmissionSlot;
  v_Shininess = i_Shininess;
}