#version 450 core

#define MAX_DIRECTIONAL_LIGHTS 5
#define MAX_POINT_LIGHTS 32
#define MAX_SPOT_LIGHTS 32

struct DirectionalLight
{
  vec4 Ambient;
  vec4 Diffuse;
  vec4 Specular;

  bool Enabled;
  float Intensity;

  vec4 Direction;
};

struct PointLight
{
  vec4 Ambient;
  vec4 Diffuse;
  vec4 Specular;

  float Constant;
  float Linear;
  float Quadratic;

  bool Enabled;
  float Intensity;

  vec4 Position;
};

struct SpotLight
{
  vec4 Ambient;
  vec4 Diffuse;
  vec4 Specular;

  float Constant;
  float Linear;
  float Quadratic;

  bool Enabled;
  float Intensity;

  vec4 Direction;
  vec4 Position;

  float InnerCutoff;
  float OuterCutoff;
};

in vec3 v_FragmentPosition;
in vec4 v_DirectionalLightSpaceFragmentPosition;
in vec4 v_Color;
in vec3 v_Normal;
in vec2 v_TextureCoord;
in vec3 v_TangentLightPosition;
in vec3 v_TangentCameraPosition;
in vec3 v_TangentFragmentPosition;
flat in int v_TextureSlot;
flat in int v_SpecularSlot;
flat in int v_EmissionSlot;
flat in int v_NormalSlot;
flat in int v_DisplacementSlot;
flat in float v_Shininess;

layout (std140, binding = 0) uniform Shared
{
  mat4 u_ViewProjection;
  vec4 u_CameraPosition;
};

layout (std140, binding = 1) uniform Lights
{
  DirectionalLight u_DirectionalLights[MAX_DIRECTIONAL_LIGHTS];
  PointLight u_PointLights[MAX_POINT_LIGHTS];
  SpotLight u_SpotLights[MAX_SPOT_LIGHTS];
  int u_DirectionalLightCount;
  int u_PointLightCount;
  int u_SpotLightCount;
  bool u_UseBlinnLightingModel;
  bool u_LightingEnabled;
};

uniform sampler2D u_Textures[32];
uniform samplerCube u_CubeDepthMap;
uniform float u_FarPlane;
uniform float u_ParallaxHeightScale = 0.05;

out vec4 o_Color;

vec4 GetTextureSample(int textureSlotIndex, vec4 defaultColor, vec2 textureCoord);

float CalcDirectionalShadow(vec4 lightSpaceFragmentPosition, vec3 normal, vec3 lightDirection);
float CalcOmniDirectionalShadow(vec3 lightPosition);

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 diffuseSample, vec3 specularSample);
vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 diffuseSample, vec3 specularSample);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 diffuseSample, vec3 specularSample);
vec3 CalcSpecularFactor(vec3 lightSpecular, vec3 lightDirection, vec3 normal, vec3 specularSample);
vec3 CalcGammaCorrection(vec3 color);
float CalcAttenuation(vec4 lightPosition, float linear, float quadratic, float constant);
vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir);

void main()
{
  vec3 viewDirection = normalize(v_TangentCameraPosition - v_TangentFragmentPosition);
  vec2 textureCoord = ParallaxMapping(v_TextureCoord, viewDirection);

  vec3 normal; // normal is in tangent space
  if (v_NormalSlot == -1)
  {
    normal = normalize(v_Normal);
  } 
  else 
  {
    normal = GetTextureSample(v_NormalSlot, vec4(v_Normal, 1.0), textureCoord).rgb;
    normal = normalize(normal * 2.0 - 1.0);
  }

  vec4 textureSample = GetTextureSample(v_TextureSlot, vec4(1.0), textureCoord) * v_Color;
  vec3 diffuseSample = textureSample.rgb;
  vec3 specularSample = GetTextureSample(v_SpecularSlot, vec4(0.3), textureCoord).rgb;
  vec3 emissionSample = GetTextureSample(v_EmissionSlot, vec4(0.0), textureCoord).rgb; // TODO: this is currently unused.

  vec3 lighting = vec3(0.0);
  if (u_LightingEnabled)
  { 
    for (int i = 0; i < u_DirectionalLightCount; i++)
    {
      lighting += CalcDirectionalLight(u_DirectionalLights[i], normal, diffuseSample, specularSample);
    }
    for (int i = 0; i < u_PointLightCount; i++)
    {
      lighting += CalcPointLight(u_PointLights[i], normal, diffuseSample, specularSample);
    }
    for (int i = 0; i < u_SpotLightCount; i++)
    {
      lighting += CalcSpotLight(u_SpotLights[i], normal, diffuseSample, specularSample);
    }
  }
  else 
  {
    lighting = diffuseSample;
  }

  o_Color = vec4(lighting, 1.0);
}

vec4 GetTextureSample(int textureSlotIndex, vec4 defaultColor, vec2 textureCoord)
{
  switch(textureSlotIndex)
  {
    case  0: return texture(u_Textures[ 0], textureCoord);
    case  1: return texture(u_Textures[ 1], textureCoord);
    case  2: return texture(u_Textures[ 2], textureCoord);
    case  3: return texture(u_Textures[ 3], textureCoord);
    case  4: return texture(u_Textures[ 4], textureCoord);
    case  5: return texture(u_Textures[ 5], textureCoord);
    case  6: return texture(u_Textures[ 6], textureCoord);
    case  7: return texture(u_Textures[ 7], textureCoord);
    case  8: return texture(u_Textures[ 8], textureCoord);
    case  9: return texture(u_Textures[ 9], textureCoord);
    case 10: return texture(u_Textures[10], textureCoord);
    case 11: return texture(u_Textures[11], textureCoord);
    case 12: return texture(u_Textures[12], textureCoord);
    case 13: return texture(u_Textures[13], textureCoord);
    case 14: return texture(u_Textures[14], textureCoord);
    case 15: return texture(u_Textures[15], textureCoord);
    case 16: return texture(u_Textures[16], textureCoord);
    case 17: return texture(u_Textures[17], textureCoord);
    case 18: return texture(u_Textures[18], textureCoord);
    case 19: return texture(u_Textures[19], textureCoord);
    case 20: return texture(u_Textures[20], textureCoord);
    case 21: return texture(u_Textures[21], textureCoord);
    case 22: return texture(u_Textures[22], textureCoord);
    case 23: return texture(u_Textures[23], textureCoord);
    case 24: return texture(u_Textures[24], textureCoord);
    case 25: return texture(u_Textures[25], textureCoord);
    case 26: return texture(u_Textures[26], textureCoord);
    case 27: return texture(u_Textures[27], textureCoord);
    case 28: return texture(u_Textures[28], textureCoord);
    case 29: return texture(u_Textures[29], textureCoord);
    case 30: return texture(u_Textures[30], textureCoord);
    case 31: return texture(u_Textures[31], textureCoord);
    default: return defaultColor;
  }
}

vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 diffuseSample, vec3 specularSample)
{
  if (!light.Enabled) return vec3(0.0);

  vec3 lightDirection = normalize(-vec3(light.Direction));
  float diffuseFactor = max(dot(normal, lightDirection), 0.0);

  vec3 ambient = vec3(light.Ambient) * diffuseSample;
  vec3 diffuse = vec3(light.Diffuse) * diffuseFactor * diffuseSample;
  vec3 specular = CalcSpecularFactor(vec3(light.Specular), lightDirection, normal, specularSample);
  float shadow = CalcDirectionalShadow(v_DirectionalLightSpaceFragmentPosition, normal, lightDirection);

  return (ambient + (1.0 - shadow) * (diffuse + specular)) * light.Intensity;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 diffuseSample, vec3 specularSample)
{
  if (!light.Enabled) return vec3(0.0);

  vec3 lightPosition = v_TangentLightPosition;
  vec3 lightDirection = normalize(lightPosition - v_TangentFragmentPosition);
  float diffuseFactor = max(dot(normal, lightDirection), 0.0);
  float attenuation = CalcAttenuation(vec4(lightPosition, 1.0), light.Linear, light.Quadratic, light.Constant);

  vec3 ambient = vec3(light.Ambient) * diffuseSample * attenuation;
  vec3 diffuse = vec3(light.Diffuse) * diffuseFactor * diffuseSample * attenuation;
  vec3 specular = CalcSpecularFactor(vec3(light.Specular), lightDirection, normal, specularSample) * attenuation;
  float shadow = CalcOmniDirectionalShadow(lightPosition);

  return (ambient + (1.0 - shadow) * (diffuse + specular)) * light.Intensity;
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 diffuseSample, vec3 specularSample)
{
  if (!light.Enabled) return vec3(0.0);

  vec3 lightDirection = normalize(vec3(light.Position) - v_TangentFragmentPosition);
  float theta = dot(lightDirection, normalize(-vec3(light.Direction)));
  float epsilon = light.InnerCutoff - light.OuterCutoff;
  float intensity = clamp((theta - light.OuterCutoff) / epsilon, 0.0, 1.0);
  
  if (theta > light.OuterCutoff)
  {
    float diffuseFactor = max(dot(normal, lightDirection), 0.0);
    float attenuation = CalcAttenuation(light.Position, light.Linear, light.Quadratic, light.Constant);

    vec3 ambient = vec3(light.Ambient) * diffuseSample;
    vec3 diffuse = vec3(light.Diffuse) * diffuseFactor * diffuseSample * attenuation * intensity;
    vec3 specular = CalcSpecularFactor(vec3(light.Specular), lightDirection, normal, specularSample)* attenuation * intensity;
    
    return (ambient + diffuse + specular) * light.Intensity;
  }
  else
  {
    return vec3(light.Ambient) * diffuseSample * light.Intensity;
  }
}

float CalcAttenuation(vec4 lightPosition, float linear, float quadratic, float constant)
{
  float distance = length(vec3(lightPosition) - v_TangentFragmentPosition);
  return 1.0 / (constant + linear * distance + quadratic * (distance));  
}

vec3 CalcSpecularFactor(vec3 lightSpecular, vec3 lightDirection, vec3 normal, vec3 specularSample)
{
  vec3 viewDirection = normalize(v_TangentCameraPosition - v_FragmentPosition);

  float specularFactor = 0.0;
  if (u_UseBlinnLightingModel)
  {
    vec3 halfwayDirection = normalize(lightDirection + viewDirection);  
    specularFactor = pow(max(dot(normal, halfwayDirection), 0.0), v_Shininess);
  }
  else
  {
    vec3 reflectDirection = reflect(-lightDirection, normal);
    specularFactor = pow(max(dot(viewDirection, reflectDirection), 0.0), v_Shininess);
  }

  return lightSpecular * specularFactor * specularSample;
}

vec3 CalcGammaCorrection(vec3 color)
{
  const float gamma = 2.2;
  return pow(vec3(color), vec3(1.0/gamma));
}

// TODO: this assumes that the first texture slot is used for the directional shadow map which probably isn't true anymore.
float CalcDirectionalShadow(vec4 lightSpaceFragmentPosition, vec3 normal, vec3 lightDirection)
{
  // perform perspective divide and transform to [0,1] range
  vec3 projectionCoords = lightSpaceFragmentPosition.xyz / lightSpaceFragmentPosition.w;
  projectionCoords = projectionCoords * 0.5 + 0.5;

  if (projectionCoords.z > 1.0) {
    return 0.0;
  } 

  // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
  float closestDepth = texture(u_Textures[0], projectionCoords.xy).r; 
  // get depth of current fragment from light's perspective
  float currentDepth = projectionCoords.z;

  float bias = max(0.05 * (1.0 - dot(normal, lightDirection)), 0.005);
  float shadow = 0.0;
  vec2 texelSize = 1.0 / textureSize(u_Textures[0], 0);
  for (int x = -1; x <= 1; ++x)
  {
    for (int y = -1; y <= 1; ++y)
    {
      float pcfDepth = texture(u_Textures[0], projectionCoords.xy + vec2(x, y) * texelSize).r; 
      shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;        
    }    
  }
  shadow /= 9.0;
  return shadow;
}

float CalcOmniDirectionalShadow(vec3 lightPosition)
{
  vec3 sampleOffsetDirections[20] = vec3[20]
  (
    vec3( 1,  1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1,  1,  1), 
    vec3( 1,  1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1,  1, -1),
    vec3( 1,  1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1,  1,  0),
    vec3( 1,  0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1,  0, -1),
    vec3( 0,  1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0,  1, -1)
  ); 

  vec3 fragToLight = v_FragmentPosition - lightPosition;
  float currentDepth = length(fragToLight);

  float shadow = 0.0;
  float bias   = 0.15;
  int samples  = 20;
  float viewDistance = length(v_TangentCameraPosition - v_TangentFragmentPosition);
  float diskRadius = 0.05;
  for (int i = 0; i < samples; i++)
  {
    float closestDepth = texture(u_CubeDepthMap, fragToLight + sampleOffsetDirections[i] * diskRadius).r;
    closestDepth *= u_FarPlane;   // undo mapping [0;1]
    if(currentDepth - bias > closestDepth)
      shadow += 1.0;
  }
  shadow /= float(samples); 

  return shadow;
}

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir) 
{
  if (v_DisplacementSlot == -1)
    return texCoords;

  float height =  GetTextureSample(v_DisplacementSlot, vec4(1.0), texCoords).r;    
  vec2 p = viewDir.xy / viewDir.z * (height * u_ParallaxHeightScale);
  return texCoords - p;   
}