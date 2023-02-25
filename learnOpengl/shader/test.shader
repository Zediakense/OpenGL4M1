vertexShader
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 pTexCoord;



out vec2 texCoord;

uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;

void main(){
  gl_Position = vec4(aPos, 1.0);
  texCoord = pTexCoord;
}

fragmentShader
#version 330 core
out vec4 fragColor;
in vec2 texCoord;
uniform sampler2D BaseTex;
uniform sampler2D tex1;
void main(){
  fragColor = vec4(0.0,1.0,0.0,1.0);
}
