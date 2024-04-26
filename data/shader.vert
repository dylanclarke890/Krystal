#version 330

layout(location = 0) in vec4 position;

smooth out vec4 fragColor;

uniform vec2 offset;
uniform mat4 perspectiveMatrix;

void main()
{
  vec4 cameraPos = position + vec4(offset.x, offset.y, 0.0, 0.0);
  gl_Position = perspectiveMatrix * cameraPos;

  fragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);
}