#version 330 core
layout (location = 0) in vec4 i_Position;
layout (location = 1) in vec4 i_Colour;
layout (location = 2) in vec2 i_TexCoord;

out vec2 v_TexCoord;
out vec4 v_Colour;

uniform mat4 u_Transform;

void main()
{
  gl_Position = u_Transform * vec4(i_Position.xyz, 1.0);
  // gl_Position = vec4(i_Position.xyz, 1.0);
  v_Colour = i_Colour;
  v_TexCoord = i_TexCoord;
}