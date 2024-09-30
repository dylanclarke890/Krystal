#version 450

in vec2 v_TextureCoord;
in vec4 v_Color;
flat in int v_TextureSlot;

out vec4 o_Color;

uniform sampler2D u_Textures[32];

vec4 GetTextureSample(int textureSlotIndex, vec4 defaultColor, vec2 textureCoords);
vec4 GreyScale(vec4 color);
vec4 Invert(vec4 color);
vec4 Apply3x3Kernel(float[9] kernel);

const float SHARPEN_KERNEL[9] = float[9] (-1.0, -1.0, -1.0, -1.0,  9.0, -1.0, -1.0, -1.0, -1.0);
const float BLUR_KERNEL[9] = float[9] (1.0 / 16, 2.0 / 16, 1.0 / 16, 2.0 / 16, 4.0 / 16, 2.0 / 16, 1.0 / 16, 2.0 / 16, 1.0 / 16);
const float EDGE_KERNEL[9] = float[9] (1.0, 1.0, 1.0, 1.0, -8.0, 1.0, 1.0, 1.0, 1.0);

void main()
{
  // vec4 textureSample = GetTextureSample(v_TextureSlot, vec4(1.0), v_TextureCoord);
  o_Color = Apply3x3Kernel(EDGE_KERNEL);
}

vec4 GetTextureSample(int textureSlotIndex, vec4 defaultColor, vec2 textureCoords)
{
  switch(textureSlotIndex)
  {
    case  0: return texture(u_Textures[ 0], textureCoords);
    case  1: return texture(u_Textures[ 1], textureCoords);
    case  2: return texture(u_Textures[ 2], textureCoords);
    case  3: return texture(u_Textures[ 3], textureCoords);
    case  4: return texture(u_Textures[ 4], textureCoords);
    case  5: return texture(u_Textures[ 5], textureCoords);
    case  6: return texture(u_Textures[ 6], textureCoords);
    case  7: return texture(u_Textures[ 7], textureCoords);
    case  8: return texture(u_Textures[ 8], textureCoords);
    case  9: return texture(u_Textures[ 9], textureCoords);
    case 10: return texture(u_Textures[10], textureCoords);
    case 11: return texture(u_Textures[11], textureCoords);
    case 12: return texture(u_Textures[12], textureCoords);
    case 13: return texture(u_Textures[13], textureCoords);
    case 14: return texture(u_Textures[14], textureCoords);
    case 15: return texture(u_Textures[15], textureCoords);
    case 16: return texture(u_Textures[16], textureCoords);
    case 17: return texture(u_Textures[17], textureCoords);
    case 18: return texture(u_Textures[18], textureCoords);
    case 19: return texture(u_Textures[19], textureCoords);
    case 20: return texture(u_Textures[20], textureCoords);
    case 21: return texture(u_Textures[21], textureCoords);
    case 22: return texture(u_Textures[22], textureCoords);
    case 23: return texture(u_Textures[23], textureCoords);
    case 24: return texture(u_Textures[24], textureCoords);
    case 25: return texture(u_Textures[25], textureCoords);
    case 26: return texture(u_Textures[26], textureCoords);
    case 27: return texture(u_Textures[27], textureCoords);
    case 28: return texture(u_Textures[28], textureCoords);
    case 29: return texture(u_Textures[29], textureCoords);
    case 30: return texture(u_Textures[30], textureCoords);
    case 31: return texture(u_Textures[31], textureCoords);
    default: return defaultColor;
  }
}

const float KERNEL_SAMPLING_OFFSET = 1.0 / 300.0;
const vec2 KERNEL_3x3_TEXTURE_COORD_OFFSETS[9] = vec2[9](
    vec2(-KERNEL_SAMPLING_OFFSET,  KERNEL_SAMPLING_OFFSET), // top-left
    vec2( 0.0f,    KERNEL_SAMPLING_OFFSET),                 // top-center
    vec2( KERNEL_SAMPLING_OFFSET,  KERNEL_SAMPLING_OFFSET), // top-right
    vec2(-KERNEL_SAMPLING_OFFSET,  0.0f),                   // center-left
    vec2( 0.0f,    0.0f),                                   // center-center
    vec2( KERNEL_SAMPLING_OFFSET,  0.0f),                   // center-right
    vec2(-KERNEL_SAMPLING_OFFSET, -KERNEL_SAMPLING_OFFSET), // bottom-left
    vec2( 0.0f,   -KERNEL_SAMPLING_OFFSET),                 // bottom-center
    vec2( KERNEL_SAMPLING_OFFSET, -KERNEL_SAMPLING_OFFSET)  // bottom-right    
  );

vec4 Apply3x3Kernel(float[9] kernel)
{
  vec3 samples[9];
  int i = 0;
  while (i < 9) {
    vec2 textureCoord = v_TextureCoord.st + KERNEL_3x3_TEXTURE_COORD_OFFSETS[i];
    samples[i] = vec3(GetTextureSample(v_TextureSlot, vec4(1.0), textureCoord));
    i++;
  }

  vec3 color = vec3(0.0);
  i = 0;
  while (i < 9) {
    color += samples[i] * kernel[i];
    i++;
  }

  return vec4(color, 1.0);
}
