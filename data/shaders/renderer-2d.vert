#version 450

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 textureCoord;
layout(location = 3) in float textureSlotIndex;

out vec4 v_Color;
out vec2 v_TextureCoord;
flat out float v_TextureSlotIndex;

void main()
{
	gl_Position = vec4(position, 1.0);
  v_Color = color;
  v_TextureCoord = textureCoord;
  v_TextureSlotIndex = textureSlotIndex;
}