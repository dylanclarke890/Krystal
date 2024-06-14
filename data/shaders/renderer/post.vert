#version 330 core

layout (location = 0) in vec2 i_Position;
layout (location = 1) in vec2 i_TextureCoord;

out vec2 v_TextureCoord;

void main()
{
  gl_Position = vec4(i_Position.xy, 0.0, 1.0); 
  v_TextureCoord = i_TextureCoord;
}