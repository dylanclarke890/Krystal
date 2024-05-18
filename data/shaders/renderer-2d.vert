#version 450

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec4 color;
layout(location = 3) in vec2 textureCoord;
layout(location = 4) in int textureSlotIndex;

out vec3 v_FragmentPosition;
out vec4 v_Color;
out vec3 v_Normal;
out vec2 v_TextureCoord;
flat out int v_TextureSlotIndex;

uniform mat4 u_ViewProjection;

void main()
{
  gl_Position = u_ViewProjection * position;
  v_FragmentPosition = vec3(position);
  v_Color = color;
  v_Normal = normal;
  v_TextureCoord = textureCoord;
  v_TextureSlotIndex = textureSlotIndex;
}