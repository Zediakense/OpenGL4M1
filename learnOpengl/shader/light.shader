vertexShader
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 pTexCoord;

out vec2 texCoord;

uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;

void main(){
  gl_Position = proj * view * model *vec4(aPos, 1.0);
  texCoord = pTexCoord;
}

fragmentShader
#version 330 core
out vec4 fragColor;
in vec2 texCoord;
uniform vec3 lightPos;
uniform vec3 lightColor;
void main(){
    vec3 pos = lightPos;
    fragColor = vec4(lightColor,1.0);
}
