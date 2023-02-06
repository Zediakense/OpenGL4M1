vertexShader
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 pTexCoord;

out vec2 texCoord;
void main(){
  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
  texCoord = pTexCoord;
}

fragmentShader
#version 330 core
out vec4 fragColor;
in vec2 texCoord;
uniform sampler2D BaseTex;
void main(){
  fragColor = texture(BaseTex , texCoord);
}
