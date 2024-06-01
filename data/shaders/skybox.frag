#version 450
out vec4 o_Color;

in vec3 v_TextureCoords;

uniform samplerCube skyboxTexture;

void main()
{
  o_Color = texture(skyboxTexture, v_TextureCoords);
}