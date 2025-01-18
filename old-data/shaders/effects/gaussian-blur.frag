#version 450 core

in vec2 v_TextureCoord;

uniform sampler2D u_Image;
  
uniform bool u_BlurHorizontally;
uniform float u_Weights[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);

out vec4 o_Color;

void main()
{             
  vec2 tex_offset = 1.0 / textureSize(u_Image, 0); // gets size of single texel
  vec3 result = texture(u_Image, v_TextureCoord).rgb * u_Weights[0]; // current fragment's contribution
  if (u_BlurHorizontally)
  {
    for (int i = 1; i < 5; ++i)
    {
      result += texture(u_Image, v_TextureCoord + vec2(tex_offset.x * i, 0.0)).rgb * u_Weights[i];
      result += texture(u_Image, v_TextureCoord - vec2(tex_offset.x * i, 0.0)).rgb * u_Weights[i];
    }
  }
  else
  {
    for (int i = 1; i < 5; ++i)
    {
      result += texture(u_Image, v_TextureCoord + vec2(0.0, tex_offset.y * i)).rgb * u_Weights[i];
      result += texture(u_Image, v_TextureCoord - vec2(0.0, tex_offset.y * i)).rgb * u_Weights[i];
    }
  }
  o_Color = vec4(result, 1.0);
}