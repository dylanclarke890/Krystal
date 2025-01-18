#version 450 core

layout (location = 0) in vec4 i_Position;
layout (location = 1) in vec3 i_Normal;
layout (location = 2) in vec4 i_Color;
layout (location = 3) in vec2 i_TextureCoords;

out vec2 v_TextureCoords;
out vec3 v_Normal;
out vec3 v_FragmentPosition;
out vec4 v_Color;

uniform mat4 u_Model;

layout (std140, binding = 0) uniform Shared
{
  mat4 u_ViewProjection;
  vec4 u_CameraPosition;
};

void main()
{
  vec4 modelPosition = u_Model * i_Position;
  v_TextureCoords = i_TextureCoords;
  v_Normal = i_Normal;
  v_FragmentPosition = vec3(modelPosition);
  v_Color = i_Color;
  gl_Position = u_ViewProjection * modelPosition;
}