#version 450 core

in vec2 v_TextureCoords;
in vec3 v_Normal;
in vec3 v_FragmentPosition;
in vec4 v_Color;

out vec4 o_Color;

#import "uniform-buffers.krys";

void main()
{
  o_Color = v_Color;
}
