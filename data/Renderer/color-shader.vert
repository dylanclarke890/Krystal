#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;

out vec4 v_Color;

void main()
{
  v_Color = color;
	gl_Position = vec4(position, 1.0);
}