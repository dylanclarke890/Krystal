#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 textureCoord;

out vec4 v_Color;
out vec2 v_TextureCoord;

void main()
{
  v_Color = color;
  v_TextureCoord = textureCoord;
	gl_Position = vec4(position, 1.0);
}