#version 450 core

#extension GL_ARB_bindless_texture : require

struct Material
{
  vec3 Ambient;
  float Padding1;
  vec3 Diffuse;
  float Padding2;
  vec3 Specular;
  float Padding3;
  vec3 Emissive;
  float Padding4;
  int AmbientTexture;
  int DiffuseTexture;
  int SpecularTexture;
  int EmissiveTexture;
  float Shininess;
  float Padding[3];
};

#define POINT_LIGHT_TYPE 0
#define DIRECTIONAL_LIGHT_TYPE 1
#define SPOT_LIGHT_TYPE 2

struct Light
{
  vec3 Intensity;
  float Padding1;
  vec3 Position;
  float Padding2;
  vec3 Direction;
  float Padding3;
  vec3 Attenuation;
  float Padding4;
  int Type;
  float Padding5[3];
  float InnerCutOff;
  float OuterCutOff;
  float Padding6[2];
};

Material GetMaterial(int index);
vec4 GetTextureSample(int index, vec4 coords);
vec4 GetTextureSample(int index, vec4 coords, vec4 defaultSample);
vec4 GetAmbient(Material material, vec4 coords);
vec4 GetDiffuse(Material material, vec4 coords);
vec4 GetSpecular(Material material, vec4 coords);
vec4 GetEmissive(Material material, vec4 coords);
float CalculateAttenuation(Light light, vec3 fragmentPosition, vec3 lightDirection);
vec4 CalculateAmbient(Light light, vec4 ambient, float attenuation);
vec4 CalculateDiffuse(Light light, vec4 diffuse, vec3 lightDirection, vec3 normal, float attenuation);
vec4 CalculateSpecular(Light light, vec4 specular, vec3 lightDirection, vec3 normal, float attenuation, float shininess);

in vec4 v_Normal;
in vec4 v_Colour;
in vec4 v_TextureCoords;
in vec3 v_FragmentPosition;

out vec4 o_Colour;

uniform int u_MaterialIndex;
uniform mat4 u_Model;
uniform mat3 u_Normal;
uniform vec3 u_CameraPosition;
uniform int u_LightCount;

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
  Light u_Lights[];
};

void main()
{
  Material material = GetMaterial(u_MaterialIndex);

  vec3 normal = normalize((u_Normal * v_Normal.xyz));
  vec3 viewDirection = normalize(u_CameraPosition - v_FragmentPosition);

  o_Colour = vec4(0);
  for (int i = 0; i < u_LightCount; i++)
  {
    Light light = u_Lights[i];
    if (light.Type == POINT_LIGHT_TYPE)
    {
      vec3 lightDirection = normalize(light.Position - v_FragmentPosition);

      float attenuation = CalculateAttenuation(light, v_FragmentPosition, lightDirection);
      vec4 ambientColour = CalculateAmbient(light, GetAmbient(material, v_TextureCoords), attenuation);
      vec4 diffuseColour = CalculateDiffuse(light, GetDiffuse(material, v_TextureCoords), lightDirection, normal, attenuation);
      vec4 specularColour = CalculateSpecular(light, GetSpecular(material, v_TextureCoords), lightDirection, normal, attenuation, material.Shininess);

      o_Colour += v_Colour * (ambientColour + diffuseColour + specularColour) * vec4(light.Intensity, 1);
    }
    else if (light.Type == DIRECTIONAL_LIGHT_TYPE)
    {
      vec3 lightDirection = normalize(light.Direction);

      vec4 ambientColour = CalculateAmbient(light, GetAmbient(material, v_TextureCoords), 1.0);
      vec4 diffuseColour = CalculateDiffuse(light, GetDiffuse(material, v_TextureCoords), lightDirection, normal, 1.0);
      vec4 specularColour = CalculateSpecular(light, GetSpecular(material, v_TextureCoords), lightDirection, normal, 1.0, material.Shininess);

      o_Colour += v_Colour * (ambientColour + diffuseColour + specularColour) * vec4(light.Intensity, 1);
    }
    else if (light.Type == SPOT_LIGHT_TYPE)
    {
      vec3 lightDirection = normalize(light.Position - v_FragmentPosition);
      vec3 spotDirection = normalize(light.Direction);

      float lightDistance = length(light.Position - v_FragmentPosition);
      float spotFactor = clamp(dot(lightDirection, spotDirection), -1.0, 1.0);
      float attenuation = CalculateAttenuation(light, v_FragmentPosition, lightDirection);
      float spotAttenuation = smoothstep(light.OuterCutOff, light.InnerCutOff, spotFactor);
      attenuation *= spotAttenuation;

      vec4 ambientColour = CalculateAmbient(light, GetAmbient(material, v_TextureCoords), attenuation);
      vec4 diffuseColour = CalculateDiffuse(light, GetDiffuse(material, v_TextureCoords), lightDirection, normal, attenuation);
      vec4 specularColour = CalculateSpecular(light, GetSpecular(material, v_TextureCoords), lightDirection, normal, attenuation, material.Shininess);

      o_Colour += v_Colour * (ambientColour + diffuseColour + specularColour) * vec4(light.Intensity, 1);
    }
  }
  o_Colour += GetEmissive(material, v_TextureCoords);
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

float CalculateAttenuation(Light light, vec3 fragmentPosition, vec3 lightDirection)
{
  float distance = length(light.Position - fragmentPosition);
  float attenuation = 1.0 / (light.Attenuation.x + light.Attenuation.y * distance + light.Attenuation.z * distance * distance);
  return attenuation;
}

vec4 CalculateAmbient(Light light, vec4 ambient, float attenuation)
{
  float ambientStrength = 0.1;
  vec4 ambientColour = ambient * ambientStrength * attenuation;
  return ambientColour;
}

vec4 CalculateDiffuse(Light light, vec4 diffuse, vec3 lightDirection, vec3 normal, float attenuation)
{
  float diffuseFactor = max(dot(normal, lightDirection), 0.0);
  vec4 diffuseColour = diffuse * diffuseFactor * attenuation;
  return diffuseColour;
}

vec4 CalculateSpecular(Light light, vec4 specular, vec3 lightDirection, vec3 normal, float attenuation, float shininess)
{
  vec3 viewDirection = normalize(u_CameraPosition - v_FragmentPosition);
  vec3 reflectDirection = reflect(-lightDirection, normal);
  float specularStrength = 1.0;
  float specularFactor = pow(max(dot(viewDirection, reflectDirection), 0.0), shininess);
  vec4 specularColour = specular * specularStrength * specularFactor * attenuation;
  return specularColour;
}

vec4 GetAmbient(Material material, vec4 coords)
{
  return GetTextureSample(material.AmbientTexture, coords, vec4(1)) * vec4(material.Ambient, 1);
}

vec4 GetDiffuse(Material material, vec4 coords)
{
  return GetTextureSample(material.DiffuseTexture, coords, vec4(1)) * vec4(material.Diffuse, 1);
}

vec4 GetSpecular(Material material, vec4 coords)
{
  return GetTextureSample(material.SpecularTexture, coords, vec4(1)) * vec4(material.Specular, 1);
}

vec4 GetEmissive(Material material, vec4 coords)
{
  return GetTextureSample(material.EmissiveTexture, coords, vec4(0)) * vec4(material.Emissive, 1);
}