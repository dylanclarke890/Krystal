#version 450

out vec4 o_Color;

in vec3 v_Normal;
in vec3 v_Position;

uniform vec3 u_CameraPosition;
uniform samplerCube skyboxTexture;

void main()
{
  vec3 I = normalize(v_Position - u_CameraPosition);
  vec3 R = reflect(I, normalize(v_Normal));
  o_Color = vec4(texture(skyboxTexture, R).rgb, 1.0);
}