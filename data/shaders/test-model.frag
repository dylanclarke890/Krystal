#version 450 core

in vec2 v_TextureCoords;

out vec4 o_Color;

uniform sampler2D u_DiffuseTextures[8];
uniform int u_TotalDiffuseTextures;

uniform sampler2D u_SpecularTextures[8];
uniform int u_TotalSpecularTextures;

uniform sampler2D u_EmissionTextures[8];
uniform int u_TotalEmissionTextures;

void main()
{
  if (u_TotalSpecularTextures > 0)
  {
    o_Color = texture(u_SpecularTextures[0], v_TextureCoords);
  }

  if (u_TotalEmissionTextures > 0)
  {
    o_Color = texture(u_EmissionTextures[0], v_TextureCoords);
  }

  if (u_TotalDiffuseTextures > 0)
  {
    o_Color = texture(u_DiffuseTextures[0], v_TextureCoords);
  }
}