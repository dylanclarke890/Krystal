#version 330 core
layout (location = 0) in vec4 i_ModelPosition;

uniform mat4 u_LightViewProjection;

void main()
{
    gl_Position = u_LightViewProjection * i_ModelPosition;
}