#version 450 core

#import "shared.glsl";

uniform Material u_Material;
uniform sampler2D u_DirectionalLightShadowMap;

in vec3 v_FragmentPosition;
in vec3 v_Normal;
in vec4 v_Color;
in vec2 v_TextureCoords;
in vec4 v_DirectionalLightFragmentPositions[MAX_DIRECTIONAL_LIGHTS];

out vec4 o_FragmentColor;

vec3 CalculateDirectionalLight(int lightIndex, vec3 normal, vec3 viewDir);
float ShadowCalculation(int lightIndex, vec3 lightDirection);

void main()
{
  vec3 normal = normalize(v_Normal);

  if (texture(u_Material.NormalMap, v_TextureCoords).r > 0.0)
    normal = normalize(texture(u_Material.NormalMap, v_TextureCoords).rgb * 2.0 - 1.0); // Convert from [0,1] to [-1,1]

  vec4 diffuseTextureColor = vec4(1.0);
  if ((u_Material.AvailableTextures & MATERIAL_DIFFUSE_MAP_SET) == MATERIAL_DIFFUSE_MAP_SET)
    diffuseTextureColor = texture(u_Material.DiffuseMap, v_TextureCoords) * vec4(u_Material.Tint, 1.0);

  vec3 viewDir = normalize(vec3(u_CameraPosition) - v_FragmentPosition);
  vec3 fragColor = vec3(0.0);
  
  for (int i = 0; i < u_DirectionalLightCount; i++)
  {
    fragColor += CalculateDirectionalLight(i, normal, viewDir);
  }

  o_FragmentColor = vec4(fragColor, 1.0) * (diffuseTextureColor * v_Color);
}

vec3 CalculateDirectionalLight(int lightIndex, vec3 normal, vec3 viewDir)
{
  DirectionalLight light = u_DirectionalLights[lightIndex];

  vec3 lightDir = normalize(-light.Direction.xyz);
  float diff = max(dot(normal, lightDir), 0.0);
  vec3 diffuse = light.Diffuse.rgb * diff * light.Intensity;
  
  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.Shininess);
  vec3 specular = light.Specular.rgb * spec * light.Intensity;

  float shadow = 0.0;
  if (u_Material.ReceivesShadows && light.CastsShadows)
    shadow = ShadowCalculation(lightIndex, light.Direction.xyz);

  vec3 ambient = light.Ambient.rgb * u_Material.AmbientColor;
  vec3 finalColor = ambient + (1.0 - shadow) * (diffuse + specular);

  return finalColor;
}

float ShadowCalculation(int lightIndex, vec3 lightDirection)
{
  vec4 fragPosLight = v_DirectionalLightFragmentPositions[lightIndex];
  vec3 projCoords = fragPosLight.xyz / fragPosLight.w; // Perspective division
  projCoords = projCoords * 0.5 + 0.5; // Transform to [0,1] range

  // Sample the shadow map
  float closestDepth = texture(u_DirectionalLightShadowMap, projCoords.xy).r;
  float currentDepth = projCoords.z;
  
  // Shadow bias to prevent shadow acne
  float bias = max(0.05 * (1.0 - dot(normalize(v_Normal), normalize(lightDirection))), 0.005);
  float shadow = (currentDepth - bias > closestDepth) ? 1.0 : 0.0;

  // Return shadow factor (1 = in shadow, 0 = not in shadow)
  return shadow;
}
