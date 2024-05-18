#version 450

in vec3 v_FragmentPosition;
in vec4 v_Color;
in vec3 v_Normal;
in vec2 v_TextureCoord;
flat in int v_TextureSlotIndex;

out vec4 o_Color;

uniform sampler2D u_Textures[32];

uniform vec3 u_CameraPosition;

uniform vec4 u_LightColor;
uniform vec3 u_LightPosition;

uniform float u_AmbientStrength;
uniform float u_SpecularStrength;
uniform int u_ShineStrength;

void main()
{
  vec4 texColor;
  switch(v_TextureSlotIndex)
  {
      case  0: texColor = texture(u_Textures[ 0], v_TextureCoord); break;
      case  1: texColor = texture(u_Textures[ 1], v_TextureCoord); break;
      case  2: texColor = texture(u_Textures[ 2], v_TextureCoord); break;
      case  3: texColor = texture(u_Textures[ 3], v_TextureCoord); break;
      case  4: texColor = texture(u_Textures[ 4], v_TextureCoord); break;
      case  5: texColor = texture(u_Textures[ 5], v_TextureCoord); break;
      case  6: texColor = texture(u_Textures[ 6], v_TextureCoord); break;
      case  7: texColor = texture(u_Textures[ 7], v_TextureCoord); break;
      case  8: texColor = texture(u_Textures[ 8], v_TextureCoord); break;
      case  9: texColor = texture(u_Textures[ 9], v_TextureCoord); break;
      case 10: texColor = texture(u_Textures[10], v_TextureCoord); break;
      case 11: texColor = texture(u_Textures[11], v_TextureCoord); break;
      case 12: texColor = texture(u_Textures[12], v_TextureCoord); break;
      case 13: texColor = texture(u_Textures[13], v_TextureCoord); break;
      case 14: texColor = texture(u_Textures[14], v_TextureCoord); break;
      case 15: texColor = texture(u_Textures[15], v_TextureCoord); break;
      case 16: texColor = texture(u_Textures[16], v_TextureCoord); break;
      case 17: texColor = texture(u_Textures[17], v_TextureCoord); break;
      case 18: texColor = texture(u_Textures[18], v_TextureCoord); break;
      case 19: texColor = texture(u_Textures[19], v_TextureCoord); break;
      case 20: texColor = texture(u_Textures[20], v_TextureCoord); break;
      case 21: texColor = texture(u_Textures[21], v_TextureCoord); break;
      case 22: texColor = texture(u_Textures[22], v_TextureCoord); break;
      case 23: texColor = texture(u_Textures[23], v_TextureCoord); break;
      case 24: texColor = texture(u_Textures[24], v_TextureCoord); break;
      case 25: texColor = texture(u_Textures[25], v_TextureCoord); break;
      case 26: texColor = texture(u_Textures[26], v_TextureCoord); break;
      case 27: texColor = texture(u_Textures[27], v_TextureCoord); break;
      case 28: texColor = texture(u_Textures[28], v_TextureCoord); break;
      case 29: texColor = texture(u_Textures[29], v_TextureCoord); break;
      case 30: texColor = texture(u_Textures[30], v_TextureCoord); break;
      case 31: texColor = texture(u_Textures[31], v_TextureCoord); break;
      default: texColor = vec4(1.0); // Fallback to white color if texture slot index is invalid
  }

  // Ambient lighting
  vec3 ambient = u_AmbientStrength * vec3(u_LightColor);

  // Diffuse lighting
  vec3 norm = normalize(v_Normal);
  vec3 lightDir = normalize(u_LightPosition - v_FragmentPosition);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * vec3(u_LightColor);

  // Specular lighting
  vec3 viewDir = normalize(u_CameraPosition - v_FragmentPosition);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_ShineStrength);
  vec3 specular = u_SpecularStrength * spec * vec3(u_LightColor);

  // Combine results
  vec3 lighting = (ambient + diffuse + specular) * vec3(v_Color) * vec3(texColor);
  o_Color = vec4(lighting, v_Color.a * texColor.a);
}
