#version 450 core

#import "sampler2d-textures.krys";
  
in vec2 v_TextureCoord;
out vec4 o_Color;

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

  vec3 hdrColor = GetTextureSample(0, vec4(0.0), v_TextureCoord).rgb;      
  vec3 bloomColor = GetTextureSample(1, vec4(0.0), v_TextureCoord).rgb;
  hdrColor += bloomColor; // additive blending

  o_Color = vec4(hdrColor, 1.0); //ToneMapping(texture(u_Textures[0], v_TextureCoord).rgb);
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