#version 450 core

#import "uniform-buffers.krys";
#import "utils/calculate-tbn.krys";

// NOTE: position, normal, tangent should be passed in world space. 
layout(location = 0) in vec4 i_Position;
layout(location = 1) in vec3 i_Normal;
layout(location = 2) in vec4 i_Color;
layout(location = 3) in vec2 i_TextureCoord;
layout(location = 4) in int i_TextureSlot;
layout(location = 5) in int i_SpecularSlot;
layout(location = 6) in int i_EmissionSlot;
layout(location = 7) in int i_NormalSlot;
layout(location = 8) in int i_DisplacementSlot;
layout(location = 9) in float i_Shininess;
layout(location = 10) in vec3 i_Tangent;

flat out vec3 v_TangentCameraPosition;

out vec4 v_Color;
out vec3 v_Normal;
out vec2 v_TextureCoord;
out vec3 v_FragmentPosition;
out vec3 v_TangentFragmentPosition;

flat out float v_Shininess;
flat out int v_TextureSlot;
flat out int v_SpecularSlot;
flat out int v_EmissionSlot;
flat out int v_NormalSlot;
flat out int v_DisplacementSlot;

flat out vec3 v_DirectionalLightTangentDirections[MAX_DIRECTIONAL_LIGHTS];
out vec4 v_DirectionalLightFragmentPositions[MAX_DIRECTIONAL_SHADOW_CASTERS];

flat out vec3 v_PointLightTangentLightPositions[MAX_POINT_LIGHTS];

flat out vec3 v_SpotLightTangentDirections[MAX_SPOT_LIGHTS];
flat out vec3 v_SpotLightTangentPositions[MAX_SPOT_LIGHTS];
out vec4 v_SpotLightFragmentPositions[MAX_SPOT_LIGHT_SHADOW_CASTERS];

void main()
{
  gl_Position = u_ViewProjection * i_Position;
  v_FragmentPosition = vec3(i_Position);
  v_Color = i_Color;
  v_TextureCoord = i_TextureCoord;
  v_TextureSlot = i_TextureSlot;
  v_SpecularSlot = i_SpecularSlot;
  v_EmissionSlot = i_EmissionSlot;
  v_NormalSlot = i_NormalSlot;
  v_DisplacementSlot = i_DisplacementSlot;
  v_Shininess = i_Shininess;

  mat3 TBN = CalcTBN(i_Tangent, i_Normal);
  v_TangentCameraPosition   = TBN * vec3(u_CameraPosition);
  v_TangentFragmentPosition = TBN * v_FragmentPosition;

  for (int i = 0; i < u_DirectionalShadowCasterCount; i++)
  {
    if (!u_DirectionalShadowCasters[i].Enabled)
      continue;
    v_DirectionalLightFragmentPositions[i] = u_DirectionalShadowCasters[i].LightSpaceMatrix * vec4(v_FragmentPosition, 1.0);
  }

  for (int i = 0; i < u_DirectionalLightCount; i++)
  {
    if (!u_DirectionalLights[i].Enabled)
      continue;
    v_DirectionalLightTangentDirections[i] = TBN * normalize(-vec3(u_DirectionalLights[i].Direction));
  }

  for (int i = 0; i < u_PointLightCount; i++)
  {
    if (!u_PointLights[i].Enabled)
      continue;

    v_PointLightTangentLightPositions[i] = TBN * vec3(u_PointLights[i].Position);
  }

  for (int i = 0; i < u_SpotLightShadowCasterCount; i++)
  {
    if (!u_SpotLightShadowCasters[i].Enabled)
      continue;

    v_SpotLightFragmentPositions[i] = u_SpotLightShadowCasters[i].LightSpaceMatrix * vec4(v_FragmentPosition, 1.0);
  }

  for (int i = 0; i < u_SpotLightCount; i++)
  {
    if (!u_SpotLights[i].Enabled)
      continue;

    v_SpotLightTangentDirections[i] = TBN * normalize(-vec3(u_SpotLights[i].Direction));
    v_SpotLightTangentPositions[i]  = TBN * vec3(u_SpotLights[i].Position);
  }

  // Transform the vertex normal to tangent space if we don't have a normal map to sample
  v_Normal = v_NormalSlot == -1 ? TBN * i_Normal : i_Normal;
}