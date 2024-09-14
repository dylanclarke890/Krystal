#version 450 core
layout (location = 0) in vec4 i_WorldSpacePosition;

void main()
{
  gl_Position = i_WorldSpacePosition;
}