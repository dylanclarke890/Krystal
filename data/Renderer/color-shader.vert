#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;

smooth out vec4 v_Color;

void main()
{
	gl_Position = vec4(position, 1.0);
	v_Color = color;
}