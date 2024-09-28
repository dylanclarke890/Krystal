#version 450 core

#import "uniform-buffers.krys";
#import "samplers.krys";
#import "utils/attenuation.krys";
#import "utils/specular.krys";

in vec3 v_FragmentPosition;
in vec4 v_DirectionalLightSpaceFragmentPosition;
in vec4 v_Color;
in vec3 v_Normal;
in vec2 v_TextureCoord;
in vec3 v_TangentLightPosition;
in vec3 v_TangentLightDirection;
in vec3 v_TangentCameraPosition;
in vec3 v_TangentFragmentPosition;
flat in int v_TextureSlot;
flat in int v_SpecularSlot;
flat in int v_EmissionSlot;
flat in int v_NormalSlot;
flat in int v_DisplacementSlot;
flat in float v_Shininess;

out vec4 o_Color;

float CalcDirectionalShadow(vec4 lightSpaceFragmentPosition, vec3 normal, vec3 lightDirection);
float CalcOmniDirectionalShadow(vec3 lightPosition, float farPlane);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 diffuseSample, vec3 specularSample);
vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 diffuseSample, vec3 specularSample);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 diffuseSample, vec3 specularSample);
vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir);

void main()
{
  vec3 viewDirection = normalize(v_TangentCameraPosition - v_TangentFragmentPosition);
  vec2 textureCoord = ParallaxMapping(v_TextureCoord, viewDirection);

  vec3 normal;
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

vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 diffuseSample, vec3 specularSample)
{
  if (!light.Enabled) return vec3(0.0);

  vec3 lightDirection = normalize(v_TangentLightDirection);
  float diffuseFactor = max(dot(normal, lightDirection), 0.0);

  vec3 ambient = vec3(light.Ambient) * diffuseSample;
  vec3 diffuse = vec3(light.Diffuse) * diffuseFactor * diffuseSample;
  vec3 specular = Specular(v_TangentCameraPosition, v_TangentFragmentPosition, lightDirection, normal, vec3(light.Specular), specularSample, v_Shininess, u_UseBlinnLightingModel);
  float shadow = CalcDirectionalShadow(v_DirectionalLightSpaceFragmentPosition, normal, lightDirection);
  
  return (ambient + (1.0 - shadow) * (diffuse + specular)) * light.Intensity;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 diffuseSample, vec3 specularSample)
{
  if (!light.Enabled) return vec3(0.0);

  vec3 lightPosition = v_TangentLightPosition;
  vec3 lightDirection = normalize(lightPosition - v_TangentFragmentPosition);
  float diffuseFactor = max(dot(normal, lightDirection), 0.0);

  vec3 ambient = vec3(light.Ambient) * diffuseSample;
  vec3 diffuse = vec3(light.Diffuse) * diffuseFactor * diffuseSample;
  vec3 specular = Specular(v_TangentCameraPosition, v_TangentFragmentPosition, lightDirection, normal, vec3(light.Specular), specularSample, v_Shininess, u_UseBlinnLightingModel);
  
  float attenuation = Attenuation(lightPosition, v_TangentFragmentPosition, light.Linear, light.Quadratic, light.Constant);
  ambient *= attenuation;
  diffuse *= attenuation;
  specular *= attenuation;

  float shadow = CalcOmniDirectionalShadow(lightPosition, u_PointLights[0].FarPlane);

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

    vec3 ambient = vec3(light.Ambient) * diffuseSample;
    vec3 diffuse = vec3(light.Diffuse) * diffuseFactor * diffuseSample;
    vec3 specular = Specular(v_TangentCameraPosition, v_TangentFragmentPosition, lightDirection, normal, vec3(light.Specular), specularSample, v_Shininess, u_UseBlinnLightingModel);
    
    float attenuation = Attenuation(vec3(light.Position), v_TangentFragmentPosition, light.Linear, light.Quadratic, light.Constant);
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    
    return (ambient + diffuse + specular) * light.Intensity;
  }
  else
  {
    return vec3(light.Ambient) * diffuseSample * light.Intensity;
  }
}

float CalcDirectionalShadow(vec4 lightSpaceFragmentPosition, vec3 normal, vec3 lightDirection)
{
  // perform perspective divide and transform to [0,1] range
  vec3 projectionCoords = lightSpaceFragmentPosition.xyz / lightSpaceFragmentPosition.w;
  projectionCoords = projectionCoords * 0.5 + 0.5;

  if (projectionCoords.z > 1.0)
  {
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

float CalcOmniDirectionalShadow(vec3 lightPosition, float farPlane)
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
    float closestDepth = GetTextureSample(u_CubemapShadowMapSlotIndex, vec4(0.0), 
      fragToLight + sampleOffsetDirections[i] * diskRadius).r;
    closestDepth *= farPlane;   // undo mapping [0;1]
    if(currentDepth - bias > closestDepth)
      shadow += 1.0;
  }
  shadow /= float(samples); 

  return shadow;
}

// TODO: artifacts from using the fancier version, fix in some way.
vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir) 
{
  if (v_DisplacementSlot == -1)
    return texCoords;

  // number of depth layers
  const float minLayers = 32;
  const float maxLayers = 64;
  const float heightScale = 0.1;

  float numLayers = mix(maxLayers, minLayers, abs(dot(vec3(0.0, 0.0, 1.0), viewDir)));  
  // calculate the size of each layer
  float layerDepth = 1.0 / numLayers;
  // depth of current layer
  float currentLayerDepth = 0.0;
  // the amount to shift the texture coordinates per layer (from vector P)
  vec2 P = viewDir.xy / viewDir.z * heightScale; 
  vec2 deltaTexCoords = P / numLayers;

  // get initial values
  vec2  currentTexCoords     = texCoords;
  float currentDepthMapValue = GetTextureSample(v_DisplacementSlot, vec4(1.0), texCoords).r;
    
  while(currentLayerDepth < currentDepthMapValue)
  {
    // shift texture coordinates along direction of P
    currentTexCoords -= deltaTexCoords;
    // get depthmap value at current texture coordinates
    currentDepthMapValue = GetTextureSample(v_DisplacementSlot, vec4(1.0), texCoords).r;
    // get depth of next layer
    currentLayerDepth += layerDepth;  
  }

    // get texture coordinates before collision (reverse operations)
  vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

  // get depth after and before collision for linear interpolation
  float afterDepth  = currentDepthMapValue - currentLayerDepth;
  float beforeDepth = GetTextureSample(v_DisplacementSlot, vec4(1.0), prevTexCoords).r - currentLayerDepth + layerDepth;

  // interpolation of texture coordinates
  float weight = afterDepth / (afterDepth - beforeDepth);
  vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

  if (finalTexCoords.x > 1.0 || finalTexCoords.y > 1.0 || finalTexCoords.x < 0.0 || finalTexCoords.y < 0.0)
    discard;

  return finalTexCoords;
}
