#version 450 core

struct PointLight
{
  bool Enabled;
  vec3 Position;

  vec3 Ambient;
  vec3 Diffuse;
  vec3 Specular;

  float Constant;
  float Linear;
  float Quadratic;
};

in vec2 v_TextureCoords;
in vec3 v_Normal;
in vec3 v_FragmentPosition;

out vec4 o_Color;

layout (std140, binding = 0) uniform Shared
{
  mat4 u_ViewProjection;
  vec4 u_CameraPosition;
};

uniform sampler2D u_DiffuseTextures[8];
uniform int u_TotalDiffuseTextures;

uniform sampler2D u_SpecularTextures[8];
uniform int u_TotalSpecularTextures;

uniform sampler2D u_EmissionTextures[8];
uniform int u_TotalEmissionTextures;

uniform float u_Shininess = 32.0;

uniform PointLight u_PointLight;

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 diffuseSample, vec3 specularSample);

void main()
{
  vec4 diffuseSample = vec4(0.0);
  if (u_TotalEmissionTextures > 0)
  {
    diffuseSample = texture(u_EmissionTextures[0], v_TextureCoords);
  }

  if (u_TotalDiffuseTextures > 0)
  {
    diffuseSample = texture(u_DiffuseTextures[0], v_TextureCoords);
  }

  vec3 specularSample = vec3(0.5);
  if (u_TotalSpecularTextures > 0)
  {
    specularSample = vec3(texture(u_SpecularTextures[0], v_TextureCoords));
  }

  if (u_PointLight.Enabled)
  {
    vec3 lighting = vec3(0.0);
    lighting += CalcPointLight(u_PointLight, normalize(v_Normal), vec3(diffuseSample), specularSample);
    o_Color = vec4(lighting, diffuseSample.a);
  }
  else
  {
    o_Color = diffuseSample;
  }
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 diffuseSample, vec3 specularSample)
{
  if (!light.Enabled)
    return vec3(0.0);
  
  vec3 lightDirection = normalize(light.Position - v_FragmentPosition);

  vec3 ambient = light.Ambient * diffuseSample;

  float diffuseFactor = max(dot(normal, lightDirection), 0.0);
  vec3 diffuse = light.Diffuse * diffuseFactor * diffuseSample;

  vec3 viewDirection = normalize(vec3(u_CameraPosition) - v_FragmentPosition);
  vec3 reflectDirection = reflect(-lightDirection, normal);
  float specularFactor = pow(max(dot(viewDirection, reflectDirection), 0.0), u_Shininess);
  vec3 specular = light.Specular * specularFactor * specularSample;

  float distance = length(light.Position - v_FragmentPosition);
  float attenuation = 1.0 / (light.Constant + light.Linear * distance + light.Quadratic * (distance * distance));  
  ambient *= attenuation;
  diffuse *= attenuation;
  specular *= attenuation;

  return ambient + diffuse + specular;
}