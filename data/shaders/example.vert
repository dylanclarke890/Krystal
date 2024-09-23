#version 450 core

#import "uniform-buffers.krys";

void main()
{
  gl_Position = vec4(0.0) * u_ViewProjection;
}