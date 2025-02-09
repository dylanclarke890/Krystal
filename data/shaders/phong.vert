#version 330 core
layout (location = 0) in vec4 i_Position;
layout (location = 1) in vec4 i_Normal;
layout (location = 2) in vec4 i_Colour;
layout (location = 3) in vec4 i_TextureCoords;

out vec4 v_Normal;
out vec4 v_Colour;
out vec4 v_TextureCoords;
out vec3 v_FragmentPosition;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
  gl_Position = u_Projection * u_View * u_Model * vec4(i_Position.xyz, 1.0);
  v_Normal = i_Normal;
  v_Colour = i_Colour;
  v_TextureCoords = i_TextureCoords;
  v_FragmentPosition = vec3(u_Model * vec4(i_Position.xyz, 1.0));
}