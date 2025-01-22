#version 330 core

in vec4 v_Colour;
in vec2 v_TexCoord;

out vec4 o_Colour;

uniform sampler2D u_Texture;

void main()
{
  o_Colour = texture(u_Texture, v_TexCoord);
}