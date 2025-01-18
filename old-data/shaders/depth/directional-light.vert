#version 450 core

#import "shared.glsl";

layout (location = 0) in vec3 i_Position;

uniform int u_CurrentLight;
uniform mat4 u_Model;

void main()
{
  gl_Position = u_DirectionalLights[u_CurrentLight].LightSpaceMatrix * u_Model * vec4(i_Position, 1.0);
}