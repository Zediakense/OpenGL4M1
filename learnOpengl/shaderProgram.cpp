//
//  shaderProgram.cpp
//  learnOpengl
//
//  Created by user on 2023/1/30.
//

#include "shaderProgram.hpp"
#include <fstream>
#include <iostream>

namespace  shaderController{

shaderController::shaderController(){

}

shaderController::~shaderController(){
    
}

bool shaderController::ReadShader(std::string path,std::string& vs,std::string& fs){
    bool res = false;
    std::ifstream f;
    f.open(path.c_str());
    if(!f.is_open()){
        printf("open %s failed!\n",path.c_str());
        return res;
    }
    std::string buf;
    std::string shader[2];
    int flag = 0;
    while(getline(f,buf)){
        if(buf == "vertexShader"){
            continue;
        }
        if(buf == "fragmentShader"){
            flag = 1;
            continue;
        }
        shader[flag] += buf + "\n";
        
    }
    vs = shader[0];
    fs = shader[1];
    printf("read vs---------------\n%sfs---------------\n%s\n",vs.c_str(),fs.c_str());
    f.close();
    
    return res;
}

bool shaderController::MakeProgram(){
    bool res = false;
    
    std::string vs ,fs;
    
    bool readShader = ReadShader(m_path, vs, fs);
    if(!readShader){
        
        return false;
    }
    const char* vs1 = vs.c_str(),*fs1 = fs.c_str();
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vs1, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fs1, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return false;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    res = true;
    return res;
}

shaderController & shaderController::Instance(){
    static shaderController shaderController;
    return shaderController;
}

};
