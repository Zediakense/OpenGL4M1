//
//  gameObject.hpp
//  learnOpengl
//
//  Created by user on 2023/2/1.
//

#ifndef gameObject_hpp
#define gameObject_hpp

#include <stdio.h>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shaderProgram.hpp"

class gameObject{
public:
    void draw();
    void bindVBO();
    void bindVAO();
    void bindEBO();
    void unBind();
    void destroy();
    void bindShader();
    bool readModel(std::string path);
    void testBind();
    
private:
    bool                    m_enable = true;
    std::vector<float>      m_vertices;
    std::vector<float>      m_pointIndex;
    unsigned int            m_vbo = 0;
    unsigned int            m_vao = 0;
    unsigned int            m_ibo = 0;
    int                     m_layout = 0;
    shaderController::shaderController* shader = nullptr;
    std::string             m_shaderPath = "test.shaderam";
};

#endif /* gameObject_hpp */
