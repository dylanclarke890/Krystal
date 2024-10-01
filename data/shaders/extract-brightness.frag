#version 450 core

in vec2 v_TextureCoord;

uniform sampler2D u_Image;

out vec4 o_BrightColor;

void main()
{
  vec3 outputColor = texture(u_Image, v_TextureCoord).rgb;

  // check whether fragment output is higher than threshold, if so output as brightness color
  float brightness = dot(outputColor, vec3(0.2126, 0.7152, 0.0722));
  if (brightness > 0.5)
    o_BrightColor = vec4(outputColor, 1.0);
  else
    o_BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
  // o_BrightColor = vec4(0.0, 0.0, 1.0, 1.0);
}