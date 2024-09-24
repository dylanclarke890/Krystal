#version 450 core

#import "samplers.krys";
#import "tone-mapping.krys";
  
in vec2 v_TextureCoord;
out vec4 o_Color;

uniform float u_Exposure = 1.0;

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

  o_Color = vec4(hdrColor, 1.0); //ToneMapping(texture(u_Textures[0], v_TextureCoord).rgb, u_Exposure);
}