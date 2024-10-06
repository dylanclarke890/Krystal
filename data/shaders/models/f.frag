#version 450 core

in vec2 v_TextureCoords;
in vec3 v_Normal;
in vec3 v_FragmentPosition;
in vec4 v_Color;

out vec4 o_Color;

#import "uniform-buffers.krys";

uniform sampler2D u_DiffuseTextures[8];
uniform int u_TotalDiffuseTextures;

uniform sampler2D u_SpecularTextures[8];
uniform int u_TotalSpecularTextures;

uniform sampler2D u_EmissionTextures[8];
uniform int u_TotalEmissionTextures;

uniform float u_Shininess = 32.0;

void main()
{
  o_Color = v_Color;
}
