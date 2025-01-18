#version 450

layout(location = 0) in vec4 i_Position;
layout(location = 2) in vec4 i_Color;

#import "uniform-buffers.krys";

out vec4 v_Color;

void main()
{
  gl_Position = u_ViewProjection * i_Position;
  v_Color = i_Color;
}