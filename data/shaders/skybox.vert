#version 450
layout (location = 0) in vec3 i_Position;

out vec3 v_TextureCoords;

uniform mat4 u_ViewProjection;

void main()
{
  v_TextureCoords = i_Position;
  vec4 pos = u_ViewProjection * vec4(i_Position, 1.0);
  gl_Position = pos.xyww;
}
