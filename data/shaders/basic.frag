#version 450 

// #extension GL_ARB_bindless_texture : enable
// layout(bindless_sampler) uniform;

uniform sampler2D u_Texture;

in vec2 f_TextureCoords;
in vec2 f_Position;

out vec4 o_Color;

void main()
{
  vec4 texColor = texture(u_Texture, f_TextureCoords);
  o_Color = vec4(texColor.rgb, 1.0);
}
