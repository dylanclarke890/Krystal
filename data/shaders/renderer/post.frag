#version 330 core
  
in vec2 v_TextureCoord;

out vec4 o_Color;

uniform sampler2D u_Textures[32];

void main()
{ 
  // float depthValue = texture(u_Textures[0], v_TextureCoord).r;
  // o_Color = vec4(vec3(depthValue), 1.0);
  o_Color = texture(u_Textures[0], v_TextureCoord);
}