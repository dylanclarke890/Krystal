#version 450 core

#import "shared.glsl";

uniform Material u_Material;

in vec3 v_FragmentPosition;
in vec3 v_Normal;
in vec4 v_Color;
in vec2 v_TextureCoords;

out vec4 o_FragmentColor;

// Lights (assuming one directional light for simplicity)
// uniform vec3 u_LightPosition;
// uniform vec3 u_LightColor;
// uniform vec3 u_LightDirection;  // For directional light
// uniform float u_LightIntensity;

// vec3 CalculateLighting(vec3 normal, vec3 lightDir, vec3 viewDir, vec3 lightColor, float shininess, vec3 specularColor)
// {
//     // Ambient lighting
//   vec3 ambient = u_Material.AmbientColor * lightColor * u_LightIntensity;

//   // Diffuse lighting (Lambertian reflection)
//   float diff = max(dot(normal, lightDir), 0.0);
//   vec3 diffuse = diff * u_Material.DiffuseColor * lightColor;

//   // Specular lighting (Phong reflection model)
//   vec3 reflectDir = reflect(-lightDir, normal);
//   float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
//   vec3 specular = spec * specularColor * lightColor;

//   return ambient + diffuse + specular;
// }

void main()
{
  // Get the normal from the normal map if available, otherwise use interpolated normal
  vec3 normal = normalize(v_Normal);
  if (texture(u_Material.NormalMap, v_TextureCoords).r > 0.0)
  {
    normal = normalize(texture(u_Material.NormalMap, v_TextureCoords).rgb * 2.0 - 1.0); // Convert from [0,1] to [-1,1]
  }

  // // Light direction (for directional light, it's constant)
  // vec3 lightDir = normalize(-u_LightDirection); // Assuming it's a directional light

  // // View direction
  // vec3 viewDir = normalize(u_CameraPosition.xyz - v_FragmentPosition);

  // // Calculate lighting
  // vec3 lighting = CalculateLighting(normal, lightDir, viewDir, u_LightColor, u_Material.Shininess, u_Material.SpecularColor);

  // Sample the diffuse texture and apply the tint color
  vec4 diffuseTextureColor = texture(u_Material.DiffuseMap, v_TextureCoords) * vec4(u_Material.Tint, 1.0);

  // // Final color
  // vec3 finalColor = lighting * diffuseTextureColor.rgb;

  // FragColor = vec4(finalColor, diffuseTextureColor.a);

  o_FragmentColor = diffuseTextureColor + v_Color;
}
