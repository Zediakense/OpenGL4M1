vertexShader
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 anorm;

out vec3 norm;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;

void main(){
  gl_Position = proj * view * model * vec4(aPos, 1.0);
  norm = anorm;
  fragPos = vec3(model * vec4(aPos,1.0));
}

fragmentShader
#version 330 core
out vec4 fragColor;
in vec3 norm;
in vec3 fragPos;

struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
uniform Material material;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 viewPos;
void main(){
    vec3 ambient = lightColor * material.ambient;
    
    vec3 Norm = normalize(norm);
    vec3 lightDir = normalize(lightPos - fragPos);
    vec3 viewDir1 = normalize(viewPos - fragPos);
    vec3 halfDir = viewDir1 + lightDir;
    float diff = max(dot(Norm, halfDir), 0.0);
    vec3 diffuse = lightColor * (diff * material.diffuse);
    
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, Norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = lightColor * (spec * material.specular);
    
    vec3 result = vec3(0.2f) * ambient + vec3(0.5f) * diffuse + specular;
    
    fragColor = vec4(result, 1.0);
}
