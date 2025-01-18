#version 450 core

#import "uniform-buffers.krys";
#import "samplers.krys";
#import "utils/attenuation.krys";
#import "utils/specular.krys";
#import "utils/directional.krys";
#import "utils/point-light.krys";
#import "utils/spot-light.krys";
#import "utils/parallax-mapping.krys";

flat in vec3 v_TangentCameraPosition;

in vec4 v_Color;
in vec3 v_Normal;
in vec2 v_TextureCoord;
in vec3 v_FragmentPosition;
in vec3 v_TangentFragmentPosition;

flat in float v_Shininess;
flat in int v_TextureSlot;
flat in int v_SpecularSlot;
flat in int v_EmissionSlot;
flat in int v_NormalSlot;
flat in int v_DisplacementSlot;

flat in vec3 v_DirectionalLightTangentDirections[MAX_DIRECTIONAL_LIGHTS];
in vec4 v_DirectionalLightFragmentPositions[MAX_DIRECTIONAL_SHADOW_CASTERS];

flat in vec3 v_PointLightTangentLightPositions[MAX_POINT_LIGHTS];

flat in vec3 v_SpotLightTangentDirections[MAX_SPOT_LIGHTS];
flat in vec3 v_SpotLightTangentPositions[MAX_SPOT_LIGHTS];
in vec4 v_SpotLightFragmentPositions[MAX_SPOT_LIGHT_SHADOW_CASTERS];

out vec4 o_Color;

void main()
{
  vec2 textureCoords;
  if (v_DisplacementSlot == -1)
  {
    textureCoords = v_TextureCoord;
  }
  else
  {
    vec3 viewDirection = normalize(v_TangentCameraPosition - v_TangentFragmentPosition);
    textureCoords = ParallaxMapping(v_TextureCoord, viewDirection, v_DisplacementSlot);
  }

  vec3 normal;
  if (v_NormalSlot == -1)
  {
    normal = normalize(v_Normal);
  } 
  else 
  {
    normal = GetTextureSample(v_NormalSlot, vec4(v_Normal, 1.0), textureCoords).rgb;
    normal = normalize(normal * 2.0 - 1.0);
  }

  vec4 textureSample = GetTextureSample(v_TextureSlot, vec4(1.0), textureCoords) * v_Color;
  vec3 diffuseSample = textureSample.rgb;
  vec3 specularSample = GetTextureSample(v_SpecularSlot, vec4(0.3), textureCoords).rgb;

  vec3 lighting = vec3(0.0);
  if (u_LightingEnabled)
  { 
    for (int i = 0; i < u_DirectionalLightCount; i++)
    {
      DirectionalShadowCasterSearchResult casterResult = GetDirectionalShadowCaster(i);
      lighting += Lighting(
        u_DirectionalLights[i],
        v_DirectionalLightFragmentPositions[casterResult.Index],
        v_TangentFragmentPosition,
        v_TangentCameraPosition,
        v_DirectionalLightTangentDirections[i],
        normal,
        diffuseSample,
        specularSample,
        v_Shininess,
        Get2DSampler(casterResult.Caster.ShadowMapSlotIndex),
        u_UseBlinnLightingModel);
    }

    for (int i = 0; i < u_PointLightCount; i++)
    {
      PointLightShadowCasterSearchResult casterResult = GetPointLightShadowCaster(i);
      lighting += Lighting(
        u_PointLights[i],
        v_FragmentPosition,
        v_TangentFragmentPosition,
        v_TangentCameraPosition,
        v_PointLightTangentLightPositions[i],
        normal,
        diffuseSample,
        specularSample,
        v_Shininess,
        GetCubemapSampler(casterResult.Caster.ShadowMapSlotIndex),
        casterResult.Caster.NearFarPlane.y,
        u_UseBlinnLightingModel);
    }

    for (int i = 0; i < u_SpotLightCount; i++)
    {
      SpotLightShadowCasterSearchResult casterResult = GetSpotLightShadowCaster(i);
      lighting += Lighting(
        u_SpotLights[i],
        v_SpotLightFragmentPositions[casterResult.Index],
        v_TangentFragmentPosition,
        v_TangentCameraPosition,
        v_SpotLightTangentPositions[i],
        v_SpotLightTangentDirections[i],
        normal,
        diffuseSample,
        specularSample,
        v_Shininess,
        Get2DSampler(casterResult.Caster.ShadowMapSlotIndex),
        u_UseBlinnLightingModel);
    }
  }
  else 
  {
    lighting = diffuseSample;
  }

  vec3 emissionSample = GetTextureSample(v_EmissionSlot, vec4(0.0), textureCoords).rgb;
  lighting += emissionSample;

  o_Color = vec4(lighting, 1.0);
}
