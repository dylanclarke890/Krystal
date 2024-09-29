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

out vec3 v_FragmentPosition;
out vec4 v_Color;
out vec3 v_Normal;
out vec2 v_TextureCoord;
out vec4 v_DirectionalLightSpaceFragmentPosition;
out vec4 v_SpotLightLightSpaceFragmentPosition;
flat out vec3 v_PointLightTangentLightPosition;
flat out vec3 v_DirectionalTangentLightDirection;
flat out vec3 v_TangentCameraPosition;
out vec3 v_TangentFragmentPosition;
flat out vec3 v_SpotLightTangentDirection;
flat out vec3 v_SpotLightTangentPosition;
flat out int v_TextureSlot;
flat out int v_SpecularSlot;
flat out int v_EmissionSlot;
flat out int v_NormalSlot;
flat out int v_DisplacementSlot;
flat out float v_Shininess;

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

  v_DirectionalLightSpaceFragmentPosition = u_DirectionalShadowCasters[0].LightSpaceMatrix * vec4(v_FragmentPosition, 1.0);
  v_SpotLightLightSpaceFragmentPosition   = u_SpotLightShadowCasters[0].LightSpaceMatrix * vec4(v_FragmentPosition, 1.0);
  mat3 TBN = CalcTBN(i_Tangent, i_Normal);
  
  v_TangentCameraPosition                 = TBN * vec3(u_CameraPosition);
  v_TangentFragmentPosition               = TBN * v_FragmentPosition;

  v_DirectionalTangentLightDirection      = TBN * normalize(-vec3(u_DirectionalLights[0].Direction.xyz));
  
  v_PointLightTangentLightPosition        = TBN * vec3(u_PointLights[0].Position.xyz);

  v_SpotLightTangentDirection             = TBN * normalize(-vec3(u_SpotLights[0].Direction.xyz));
  v_SpotLightTangentPosition              = TBN * vec3(u_SpotLights[0].Position.xyz);

  // Transform the vertex normal to tangent space if we don't have a normal map to sample
  v_Normal = v_NormalSlot == -1 ? TBN * i_Normal : i_Normal;
}