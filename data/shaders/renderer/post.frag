#version 450 core
  
in vec2 v_TextureCoord;

out vec4 o_Color;

uniform sampler2D u_Textures[32];
uniform bool u_IsHDREnabled;
uniform float u_Exposure = 1.0;

vec4 ToneMapping(vec3 color);
vec3 ReinhardToneMapping(vec3 color);
vec3 ExposureToneMapping(vec3 color, float exposure);
vec3 GammaCorrection(vec3 color);

void main()
{ 
  /* 
  Display the contents of a depth buffer.
    float depthValue = texture(u_Textures[1], v_TextureCoord).r;
    o_Color = vec4(vec3(depthValue), 1.0);
  */

  o_Color = texture(u_Textures[0], v_TextureCoord);

  if (u_IsHDREnabled) 
  {
    o_Color = ToneMapping(o_Color.rgb);
  }
}

vec4 ToneMapping(vec3 color)
{
  vec3 mapped = u_Exposure == 1.0 ? ReinhardToneMapping(color) : ExposureToneMapping(color, u_Exposure);
  mapped = GammaCorrection(mapped);
  return vec4(mapped.rgb, 1.0);
}

vec3 ReinhardToneMapping(vec3 color)
{
  return color / (color + vec3(1.0));
}

vec3 ExposureToneMapping(vec3 color, float exposure)
{
  return vec3(1.0) - exp(-color * exposure);
}

vec3 GammaCorrection(vec3 color) 
{
  const float gamma = 2.2;
  return pow(color, vec3(1.0 / gamma));
}