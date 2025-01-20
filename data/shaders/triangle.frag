#version 330 core
out vec4 FragColor;

uniform float u_Time;

void main()
{
  float greenValue = (sin(u_Time) / 2.0f) + 0.5f;

  FragColor = vec4(0.0f, greenValue, 0.0f, 1.0f);
}