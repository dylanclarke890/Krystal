#version 450 core

#extension GL_ARB_bindless_texture : require

struct Material
{
  int AmbientTexture;
  int DiffuseTexture;
  int SpecularTexture;
  int EmissiveTexture;
  float Shininess;
  float Padding[3];
};

#define POINT_LIGHT_TYPE 0
#define DIRECTIONAL_LIGHT_TYPE 1

struct Light
{
  vec3 Intensity;
  float Padding1;
  vec3 Position;
  float Padding2;
  vec3 Direction;
  float Padding3;
  int Type;
  float Padding[3];
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

  o_Colour = vec4(0);
  for (int i = 0; i < u_LightCount; i++)
  {
    Light light = u_Lights[i];
    if (light.Type == POINT_LIGHT_TYPE)
    {
      vec3 lightDirection = normalize(light.Position - v_FragmentPosition.xyz);
      vec3 viewDirection = normalize(u_CameraPosition - v_FragmentPosition);
      vec3 reflectDirection = reflect(-lightDirection, normal);

      float ambientStrength = 0.4;
      vec4 ambient = GetTextureSample(material.AmbientTexture, v_TextureCoords);
      vec4 ambientColour = ambient * ambientStrength;

      // TODO: use diffuse texture
      vec4 diffuse = GetTextureSample(material.AmbientTexture, v_TextureCoords);
      float diffuseFactor = max(dot(normal, lightDirection), 0.0);
      vec4 diffuseColour = diffuse * diffuseFactor;
  
      float specularStrength = 0.5;
      vec4 specular = GetTextureSample(material.SpecularTexture, v_TextureCoords);
      float specularFactor = pow(max(dot(viewDirection, reflectDirection), 0.0), material.Shininess);
      vec4 specularColour = specular * specularStrength * specularFactor;

      o_Colour += v_Colour * (ambientColour + diffuseColour + specularColour) * vec4(light.Intensity, 1);
    }
    else if (light.Type == DIRECTIONAL_LIGHT_TYPE)
    {
      vec3 lightDirection = normalize(light.Direction);
      vec3 viewDirection = normalize(u_CameraPosition - v_FragmentPosition);
      vec3 reflectDirection = reflect(-lightDirection, normal);

      float ambientStrength = 0.1;
      vec4 ambient = GetTextureSample(material.AmbientTexture, v_TextureCoords);
      vec4 ambientColour = ambient * ambientStrength;
    
      // TODO: use diffuse texture
      vec4 diffuse = GetTextureSample(material.AmbientTexture, v_TextureCoords);
      float diffuseFactor = max(dot(normal, lightDirection), 0.0);
      vec4 diffuseColour = diffuse * diffuseFactor;

      float specularStrength = 0.5;
      vec4 specular = GetTextureSample(material.SpecularTexture, v_TextureCoords);
      float specularFactor = pow(max(dot(viewDirection, reflectDirection), 0.0), material.Shininess);
      vec4 specularColour = specular * specularStrength * specularFactor;

      o_Colour += v_Colour * (ambientColour + diffuseColour + specularColour) * vec4(light.Intensity, 1);
    }
  }
  o_Colour += GetTextureSample(material.EmissiveTexture, v_TextureCoords, vec4(0.0));
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
