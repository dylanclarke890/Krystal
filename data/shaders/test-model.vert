#version 450 core

layout (location = 0) in vec3 i_Position;
layout (location = 1) in vec3 i_Normal;
layout (location = 2) in vec2 i_TextureCoords;

out vec2 v_TextureCoords;

uniform mat4 u_Model;
uniform mat4 u_ViewProjection;

void main()
{
  v_TextureCoords = i_TextureCoords;
  gl_Position = u_ViewProjection * u_Model * vec4(i_Position, 1.0);
}