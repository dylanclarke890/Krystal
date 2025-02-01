#version 330 core

in vec4 v_Colour;
in vec4 v_TexCoord;

out vec4 o_Colour;

uniform sampler2D u_Texture;

uniform vec3 u_AmbientColour;

void main()
{
  o_Colour = texture(u_Texture, v_TexCoord.xy) * v_Colour + vec4(u_AmbientColour, 1.0);
}