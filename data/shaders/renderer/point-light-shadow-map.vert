#version 450 core
layout (location = 0) in vec4 i_Position;

void main()
{
  gl_Position = i_Position;
}