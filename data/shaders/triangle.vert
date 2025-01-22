#version 330 core
layout (location = 0) in vec4 i_Position;
layout (location = 1) in vec4 i_Colour;
layout (location = 2) in vec2 i_TexCoord;

out vec2 v_TexCoord;
out vec4 v_Colour;

void main()
{
  gl_Position = vec4(i_Position.x, i_Position.y, i_Position.z, 1.0);
  v_Colour = i_Colour;
  v_TexCoord = i_TexCoord;
}