#version 450 core

#import "shared.glsl";

uniform mat4 u_Model;
uniform Material u_Material;

layout(location = 0) in vec3 i_Position;
layout(location = 1) in vec3 i_Normal;
layout(location = 2) in vec4 i_Color;
layout(location = 3) in vec2 i_TextureCoords;
layout(location = 4) in vec3 i_Tangent;

out vec3 v_FragmentPosition;
out vec3 v_Normal;
out vec4 v_Color;
out vec2 v_TextureCoords;
out vec4 v_DirectionalLightFragmentPositions[MAX_DIRECTIONAL_LIGHTS];

void main()
{
  v_FragmentPosition = vec3(u_Model * vec4(i_Position, 1.0));
  v_Normal = mat3(transpose(inverse(u_Model))) * i_Normal;
  v_Color = i_Color;
  v_TextureCoords = i_TextureCoords;
  gl_Position = u_ViewProjection * vec4(v_FragmentPosition, 1.0);

  for (int i = 0; i < u_DirectionalLightCount; i++)
  {
    if (!u_DirectionalLights[i].Enabled)
      continue;
    v_DirectionalLightFragmentPositions[i] = u_DirectionalLights[i].LightSpaceMatrix * vec4(v_FragmentPosition, 1.0);
  }
}