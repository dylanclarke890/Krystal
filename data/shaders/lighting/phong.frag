#version 450 core

#define MAX_DIRECTIONAL_LIGHTS 5
#define MAX_POINT_LIGHTS 32
#define MAX_SPOT_LIGHTS 32

struct DirectionalLight
{
  vec3 Ambient;
  vec3 Diffuse;
  vec3 Specular;

  bool Enabled;
  float Intensity;

  vec3 Direction;
};

struct PointLight
{
  vec3 Ambient;
  vec3 Diffuse;
  vec3 Specular;

  float Constant;
  float Linear;
  float Quadratic;

  bool Enabled;
  float Intensity;

  vec3 Position;
};

struct SpotLight
{
  vec3 Ambient;
  vec3 Diffuse;
  vec3 Specular;

  float Constant;
  float Linear;
  float Quadratic;

  bool Enabled;
  float Intensity;

  vec3 Direction;
  vec3 Position;

  float InnerCutoff;
  float OuterCutoff;
};

in vec3 v_FragmentPosition;
in vec4 v_Color;
in vec3 v_Normal;
in vec2 v_TextureCoord;
flat in int v_TextureSlot;
flat in int v_SpecularSlot;
flat in int v_EmissionSlot;
flat in float v_Shininess;

layout (std140, binding = 0) uniform Shared
{
  mat4 u_ViewProjection;
  vec3 u_CameraPosition;
};

layout (std140, binding = 7) uniform DirectionalLights
{
  DirectionalLight u_DirectionalLights[MAX_DIRECTIONAL_LIGHTS];
};

layout (std140, binding = 8) uniform PointLights
{
  PointLight u_PointLights[MAX_POINT_LIGHTS];
};

layout (std140, binding = 9) uniform SpotLights
{
  SpotLight u_SpotLights[MAX_SPOT_LIGHTS];
};

layout (std140, binding = 10) uniform LightCounts
{
  int u_DirectionalLightCount;
  int u_PointLightCount;
  int u_SpotLightCount;
};

uniform sampler2D u_Textures[32];

out vec4 o_Color;

vec4 GetTextureSample(int textureSlotIndex, vec4 defaultColor);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 diffuseSample, vec3 specularSample);
vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 diffuseSample, vec3 specularSample);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 diffuseSample, vec3 specularSample);

void main()
{
  vec3 normal = normalize(v_Normal);

  vec4 textureSample = GetTextureSample(v_TextureSlot, vec4(1.0)) * v_Color;

  vec3 diffuseSample = vec3(textureSample);
  vec3 specularSample = vec3(GetTextureSample(v_SpecularSlot, vec4(0.1)));
  vec3 emissionSample = vec3(GetTextureSample(v_EmissionSlot, vec4(0.0)));

  vec3 lighting = vec3(0.0);
  for (int i = 0; i < u_DirectionalLightCount; i++) {
    lighting += CalcDirectionalLight(u_DirectionalLights[i], normal, diffuseSample, specularSample);
  }

  for (int i = 0; i < u_PointLightCount; i++) {
    lighting += CalcPointLight(u_PointLights[i], normal, diffuseSample, specularSample);
  }

  for (int i = 0; i < u_SpotLightCount; i++) {
    lighting += CalcSpotLight(u_SpotLights[i], normal, diffuseSample, specularSample);
  }

  o_Color = vec4(lighting, 1.0);
}

vec4 GetTextureSample(int textureSlotIndex, vec4 defaultColor)
{
  switch(textureSlotIndex)
  {
    case  0: return texture(u_Textures[ 0], v_TextureCoord);
    case  1: return texture(u_Textures[ 1], v_TextureCoord);
    case  2: return texture(u_Textures[ 2], v_TextureCoord);
    case  3: return texture(u_Textures[ 3], v_TextureCoord);
    case  4: return texture(u_Textures[ 4], v_TextureCoord);
    case  5: return texture(u_Textures[ 5], v_TextureCoord);
    case  6: return texture(u_Textures[ 6], v_TextureCoord);
    case  7: return texture(u_Textures[ 7], v_TextureCoord);
    case  8: return texture(u_Textures[ 8], v_TextureCoord);
    case  9: return texture(u_Textures[ 9], v_TextureCoord);
    case 10: return texture(u_Textures[10], v_TextureCoord);
    case 11: return texture(u_Textures[11], v_TextureCoord);
    case 12: return texture(u_Textures[12], v_TextureCoord);
    case 13: return texture(u_Textures[13], v_TextureCoord);
    case 14: return texture(u_Textures[14], v_TextureCoord);
    case 15: return texture(u_Textures[15], v_TextureCoord);
    case 16: return texture(u_Textures[16], v_TextureCoord);
    case 17: return texture(u_Textures[17], v_TextureCoord);
    case 18: return texture(u_Textures[18], v_TextureCoord);
    case 19: return texture(u_Textures[19], v_TextureCoord);
    case 20: return texture(u_Textures[20], v_TextureCoord);
    case 21: return texture(u_Textures[21], v_TextureCoord);
    case 22: return texture(u_Textures[22], v_TextureCoord);
    case 23: return texture(u_Textures[23], v_TextureCoord);
    case 24: return texture(u_Textures[24], v_TextureCoord);
    case 25: return texture(u_Textures[25], v_TextureCoord);
    case 26: return texture(u_Textures[26], v_TextureCoord);
    case 27: return texture(u_Textures[27], v_TextureCoord);
    case 28: return texture(u_Textures[28], v_TextureCoord);
    case 29: return texture(u_Textures[29], v_TextureCoord);
    case 30: return texture(u_Textures[30], v_TextureCoord);
    case 31: return texture(u_Textures[31], v_TextureCoord);
    default: return defaultColor;
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

  vec3 viewDirection = normalize(u_CameraPosition - v_FragmentPosition);
  vec3 reflectDirection = reflect(-lightDirection, normal);
  float specularFactor = pow(max(dot(viewDirection, reflectDirection), 0.0), v_Shininess);
  vec3 specular = light.Specular * specularFactor * specularSample;

  float distance = length(light.Position - v_FragmentPosition);
  float attenuation = 1.0 / (light.Constant + light.Linear * distance + light.Quadratic * (distance * distance));  
  ambient *= attenuation;
  diffuse *= attenuation;
  specular *= attenuation;

  return ambient + diffuse + specular;
}

vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 diffuseSample, vec3 specularSample)
{
  if (!light.Enabled)
    return vec3(0.0);

  vec3 lightDirection = normalize(-light.Direction);

  vec3 ambient = light.Ambient * diffuseSample;

  float diffuseFactor = max(dot(normal, lightDirection), 0.0);
  vec3 diffuse = light.Diffuse * diffuseFactor * diffuseSample;

  vec3 viewDirection = normalize(u_CameraPosition - v_FragmentPosition);
  vec3 reflectDirection = reflect(-lightDirection, normal);
  float specularFactor = pow(max(dot(viewDirection, reflectDirection), 0.0), v_Shininess);
  vec3 specular = light.Specular * specularFactor * specularSample;

  return ambient + diffuse + specular;
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 diffuseSample, vec3 specularSample) {
  if (!light.Enabled)
    return vec3(0.0);

  vec3 lightDirection = normalize(light.Position - v_FragmentPosition);
  float theta = dot(lightDirection, normalize(-light.Direction));
  
  float epsilon = light.InnerCutoff - light.OuterCutoff;
  float intensity = clamp((theta - light.OuterCutoff) / epsilon, 0.0, 1.0);
  
  if (theta > light.OuterCutoff)
  {
    vec3 ambient = light.Ambient * diffuseSample;
    
    float diffuseFactor = max(dot(normal, lightDirection), 0.0);
    vec3 diffuse = light.Diffuse * diffuseFactor * diffuseSample;
    
    vec3 viewDirection = normalize(u_CameraPosition - v_FragmentPosition);
    vec3 reflectDirection = reflect(-lightDirection, normal);  
    float specularFactor = pow(max(dot(viewDirection, reflectDirection), 0.0), v_Shininess);
    vec3 specular = light.Specular * specularFactor * specularSample;
    
    float distance = length(light.Position - v_FragmentPosition);
    float attenuation = 1.0 / (light.Constant + light.Linear * distance + light.Quadratic * (distance * distance));  
    
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    
    return ambient + diffuse + specular;
  }
  else
  {
    return light.Ambient * diffuseSample;
  }
}