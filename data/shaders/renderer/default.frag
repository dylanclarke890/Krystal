#version 450 core

#import "uniform-buffers.krys";
#import "samplers.krys";
#import "utils/attenuation.krys";
#import "utils/specular.krys";
#import "utils/directional.krys";
#import "utils/point-light.krys";

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
      lighting += Lighting(
        u_DirectionalLights[i],
        v_DirectionalLightSpaceFragmentPosition,
        v_TangentFragmentPosition,
        v_TangentCameraPosition,
        v_TangentLightDirection,
        normal,
        diffuseSample,
        specularSample,
        v_Shininess,
        u_Textures[0], // TODO: pass the index for the sampler in
        u_UseBlinnLightingModel);
    }

    for (int i = 0; i < u_PointLightCount; i++)
    {
      lighting += Lighting(
        u_PointLights[i],
        v_FragmentPosition,
        v_TangentFragmentPosition,
        v_TangentCameraPosition,
        v_TangentLightPosition,
        normal,
        diffuseSample,
        specularSample,
        v_Shininess,
        u_Cubemaps[0],
        u_PointLightShadowCasters[0].NearFarPlane.y,
        u_UseBlinnLightingModel
      );
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
