#version 450 core

#extension GL_ARB_bindless_texture : require

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
};

struct PointLight
{
  vec3 Position;
  float Padding1;
  vec3 Intensity;
  float Padding2;
};

Material GetMaterial(int index);
vec4 GetTextureSample(int index, vec4 coords);
vec4 GetTextureSample(int index, vec4 coords, vec4 defaultSample);

in vec4 v_Normal;
in vec4 v_Colour;
in vec4 v_TextureCoords;
in vec3 v_FragmentPosition;

out vec4 o_Colour;

uniform int u_MaterialIndex;
uniform mat4 u_Model;
uniform mat3 u_Normal;

layout(std430, binding = 0) buffer MaterialBuffer
{
  Material u_Materials[];
};

layout(std430, binding = 1) buffer TextureTable
{
  sampler2D u_Textures[];
};

layout(std430, binding = 2) buffer LightBuffer
{
  PointLight u_PointLights[];
};

void main()
{
  Material material = GetMaterial(u_MaterialIndex);
  PointLight light = u_PointLights[0];

  vec3 normal = normalize((u_Normal * v_Normal.xyz));

  vec4 ambient = GetTextureSample(material.AmbientTexture, v_TextureCoords);
  ambient += v_Colour * vec4(material.Ambient, 1);
  
  o_Colour = ambient * vec4(light.Intensity, 1) * 0.1;
}

Material GetMaterial(int index)
{
  if (index >= 0 && index < u_Materials.length())
  {
    return u_Materials[index];
  }
  return u_Materials[0];
}

vec4 GetTextureSample(int index, vec4 coords, vec4 defaultSample)
{
  if (index >= 0 && index < u_Textures.length())
  {
    return texture(u_Textures[index], coords.xy);
  }
  return defaultSample;
}

vec4 GetTextureSample(int index, vec4 coords)
{
  return GetTextureSample(index, coords, vec4(1.0));
}
