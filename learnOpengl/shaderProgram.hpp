//
//  shaderProgram.hpp
//  learnOpengl
//
//  Created by user on 2023/1/30.
//

#ifndef shaderProgram_hpp
#define shaderProgram_hpp

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stdio.h>
#include <string>

namespace  shaderController{
class shaderController{
public:
    shaderController();
    ~shaderController();
    bool ReadShader(std::string path,std::string& vs,std::string& fs);
    bool MakeProgram();
    static shaderController & Instance();
    void SetUniformByName(std::string name,float value);
    void SetUniformByName(std::string name,glm::vec4 value);
    void SetUniformByName(std::string name,glm::vec3 value);
    void SetUniformByName(std::string name,glm::vec2 value);
    void SetShaderPath(std::string path){m_path = path;}

    
private:
    std::string m_path = "test.shaderam";
    
};

};

#endif /* shaderProgram_hpp */
