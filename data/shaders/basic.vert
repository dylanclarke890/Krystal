#version 450 core

layout(location = 0) in vec2 v_Position;
layout(location = 1) in vec2 v_TextureCoords;

out vec2 f_TextureCoords;
out vec2 f_Position;

void main()
{
  f_TextureCoords = v_TextureCoords;
  f_Position = v_Position;

  gl_Position = vec4(v_Position, 0.0, 1.0);
}
