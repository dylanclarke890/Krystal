#version 460 core
#extension GL_ARB_bindless_texture : require

in vec4 v_Colour;
in vec4 v_TexCoord;

out vec4 o_Colour;

uniform sampler2D u_Texture;

uniform vec3 u_AmbientColour;
uniform int u_MaterialIndex;

struct Material
{
  vec3 Ambient;
  float Padding1;
  vec3 Diffuse;
  float Padding2;
  vec3 Specular;
  float Shininess;
  int AmbientTexture;
  int DiffuseTexture;
  int SpecularTexture;
  int Padding3;
};

layout(std430, binding = 0) buffer MaterialBuffer
{
  Material Materials[5];
};

layout(std430, binding = 1) buffer TextureTable
{
  sampler2D Textures[];
};

vec4 GetTextureSample(int textureIndex, vec4 textureCoords)
{
  vec2 texCoord = textureCoords.xy;
  switch (textureIndex)
  {
    case 0:
      return texture(Textures[0], texCoord);
    case 1:
      return texture(Textures[1], texCoord);
    case 2:
      return texture(Textures[2], texCoord);
    case 3:
      return texture(Textures[3], texCoord);
    case 4:
      return texture(Textures[4], texCoord);
    case 5:
      return texture(Textures[5], texCoord);
    case 6:
      return texture(Textures[6], texCoord);
    case 7:
      return texture(Textures[7], texCoord);
    case 8:
      return texture(Textures[8], texCoord);
    case 9:
      return texture(Textures[9], texCoord);
    case 10:
      return texture(Textures[10], texCoord);
    case 11:
      return texture(Textures[11], texCoord);
    case 12:
      return texture(Textures[12], texCoord);
    case 13:
      return texture(Textures[13], texCoord);
    case 14:
      return texture(Textures[14], texCoord);
    case 15:
      return texture(Textures[15], texCoord);
    case 16:
      return texture(Textures[16], texCoord);
    case 17:
      return texture(Textures[17], texCoord);
    case 18:
      return texture(Textures[18], texCoord);
    case 19:
      return texture(Textures[19], texCoord);
    case 20:
      return texture(Textures[20], texCoord);
    default:
      break;
  }
  return vec4(1.0);
}

Material GetMaterial(int materialIndex)
{
  switch (materialIndex) {
    case 0:
      return Materials[0];
    case 1:
      return Materials[1];
    case 2:
      return Materials[2];
    case 3:
      return Materials[3];
    case 4:
      return Materials[4];
    // case 5:
    //   return Materials[5];
    // case 6:
    //   return Materials[6];
    // case 7:
    //   return Materials[7];
    // case 8:
    //   return Materials[8];
    // case 9:
    //   return Materials[9];
    // case 10:
    //   return Materials[10];
    // case 11:
    //   return Materials[11];
    // case 12:
    //   return Materials[12];
    // case 13:
    //   return Materials[13];
    // case 14:
    //   return Materials[14];
    // case 15:
    //   return Materials[15];
    // case 16:
    //   return Materials[16];
    // case 17:
    //   return Materials[17];
    // case 18:
    //   return Materials[18];
    // case 19:
    //   return Materials[19];
    // case 20:
    //   return Materials[20];
  }
  return Materials[0];
}

void main()
{
  Material material = Materials[0];
  vec4 ambient = vec4(0.0, 1.0, 0.0, 1.0);
  // vec4 ambient = GetTextureSample(material.AmbientTexture, v_TexCoord);
  o_Colour = ambient * v_Colour + vec4(material.Ambient, 1.0);
  // o_Colour = ambient * v_Colour;
}