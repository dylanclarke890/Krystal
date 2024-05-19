#version 450

struct Light {
  vec3 Position;

  vec3 Ambient;
  vec3 Diffuse;
  vec3 Specular;
};

in vec3 v_FragmentPosition;
in vec4 v_Color;
in vec3 v_Normal;
in vec2 v_TextureCoord;
flat in int v_TextureSlot;
flat in int v_SpecularSlot;
flat in int v_EmissionSlot;
flat in float v_Shininess;

out vec4 o_Color;

uniform int u_UseAmbientLighting = 1;
uniform int u_UseDiffuseLighting = 1;
uniform int u_UseSpecularLighting = 1;
uniform int u_UseEmissionLighting = 1;
uniform Light u_Light;
uniform vec3 u_CameraPosition;
uniform sampler2D u_Textures[32];

vec4 GetTextureSample(int textureSlotIndex, vec4 defaultColor)
{
  switch(textureSlotIndex)
  {
    case  0: return texture(u_Textures[ 0], v_TextureCoord);
    case  1: return texture(u_Textures[ 1], v_TextureCoord);
    case  2: return texture(u_Textures[ 2], v_TextureCoord);
    case  3: return texture(u_Textures[ 3], v_TextureCoord);
    case  4: return texture(u_Textures[ 4], v_TextureCoord);
    case  5: return texture(u_Textures[ 5], v_TextureCoord);
    case  6: return texture(u_Textures[ 6], v_TextureCoord);
    case  7: return texture(u_Textures[ 7], v_TextureCoord);
    case  8: return texture(u_Textures[ 8], v_TextureCoord);
    case  9: return texture(u_Textures[ 9], v_TextureCoord);
    case 10: return texture(u_Textures[10], v_TextureCoord);
    case 11: return texture(u_Textures[11], v_TextureCoord);
    case 12: return texture(u_Textures[12], v_TextureCoord);
    case 13: return texture(u_Textures[13], v_TextureCoord);
    case 14: return texture(u_Textures[14], v_TextureCoord);
    case 15: return texture(u_Textures[15], v_TextureCoord);
    case 16: return texture(u_Textures[16], v_TextureCoord);
    case 17: return texture(u_Textures[17], v_TextureCoord);
    case 18: return texture(u_Textures[18], v_TextureCoord);
    case 19: return texture(u_Textures[19], v_TextureCoord);
    case 20: return texture(u_Textures[20], v_TextureCoord);
    case 21: return texture(u_Textures[21], v_TextureCoord);
    case 22: return texture(u_Textures[22], v_TextureCoord);
    case 23: return texture(u_Textures[23], v_TextureCoord);
    case 24: return texture(u_Textures[24], v_TextureCoord);
    case 25: return texture(u_Textures[25], v_TextureCoord);
    case 26: return texture(u_Textures[26], v_TextureCoord);
    case 27: return texture(u_Textures[27], v_TextureCoord);
    case 28: return texture(u_Textures[28], v_TextureCoord);
    case 29: return texture(u_Textures[29], v_TextureCoord);
    case 30: return texture(u_Textures[30], v_TextureCoord);
    case 31: return texture(u_Textures[31], v_TextureCoord);
    default: return defaultColor;
  }
}

void main()
{
  vec4 textureSample = GetTextureSample(v_TextureSlot, vec4(1.0));
  vec3 normal = normalize(v_Normal);
  vec3 lightDirection = normalize(u_Light.Position - v_FragmentPosition);

  o_Color = textureSample * v_Color;
  vec3 lighting = vec3(0.0, 0.0, 0.0);

  if (u_UseAmbientLighting == 1)
  {
    lighting += u_Light.Ambient * vec3(o_Color);
  }

  if (u_UseDiffuseLighting == 1)
  {

    float diffuseFactor = max(dot(normal, lightDirection), 0.0);
    lighting += u_Light.Diffuse * diffuseFactor * vec3(o_Color);
  }

  if (u_UseSpecularLighting == 1)
  {
    vec4 specularSample = GetTextureSample(v_SpecularSlot, vec4(0.5));
    vec3 viewDirection = normalize(u_CameraPosition - v_FragmentPosition);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float specularFactor = pow(max(dot(viewDirection, reflectDirection), 0.0), v_Shininess);
    lighting += u_Light.Specular * specularFactor * vec3(specularSample);
  }

  if (u_UseEmissionLighting == 1)
  {
    vec4 emissionSample = GetTextureSample(v_EmissionSlot, vec4(0.0));
    // Add emission component
    lighting += vec3(emissionSample);
  }

  if (u_UseAmbientLighting == 1 || u_UseDiffuseLighting == 1 ||
      u_UseSpecularLighting == 1 || u_UseEmissionLighting == 1)
  {
    o_Color = vec4(lighting, o_Color.a);
  }
}
