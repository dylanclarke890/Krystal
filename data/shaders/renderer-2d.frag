#version 330

in vec4 v_Color;
in vec2 v_TextureCoord;

out vec4 o_Color;

uniform sampler2D u_Texture;

void main()
{
  o_Color = v_Color;
  o_Color *= texture(u_Texture, v_TextureCoord);
}
