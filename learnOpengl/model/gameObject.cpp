//
//  gameObject.cpp
//  learnOpengl
//
//  Created by user on 2023/2/1.
//

#include "gameObject.hpp"

void gameObject::bindVBO(){
    if(m_vbo == 0){
        glGenBuffers(1,&m_vbo);
    }
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), m_vertices.data(), GL_STATIC_DRAW);

}

void gameObject::bindVAO(){
    if(m_vao == 0){
        glGenVertexArrays(1,&m_vao);
    }
    glBindVertexArray(m_vao);
}

void gameObject::bindEBO(){
    if(m_ibo == 0){
        glGenBuffers(1,&m_ibo);
    }
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,m_pointIndex.size() * sizeof(float), m_pointIndex.data(), GL_STATIC_DRAW);
}

void gameObject::draw(){
    if(!m_enable){
        return ;
    }
    testBind();
    glVertexAttribPointer(m_layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(m_layout);
    bindShader();
    glDrawElements(GL_TRIANGLES, int(m_pointIndex.size()), GL_UNSIGNED_INT, 0);
    
    unBind();
    
}

void gameObject::unBind(){
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void gameObject::destroy(){
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ibo);
    if(shader != nullptr){
        delete shader;
        shader = nullptr;
    }
}

void gameObject::bindShader(){
    shader = new shaderController::shaderController(m_shaderPath);
    shader->MakeProgram();
}

bool gameObject::readModel(std::string path){
    bool res = false;
    m_vertices =  {
         0.5f,  0.5f, 0.0f, // top right
         0.5f, -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f, // top left
    };
    m_pointIndex =  {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    res = true;
    return res;
}

void gameObject::testBind(){
    if(m_vao != 0){
        glGenVertexArrays(1, &m_vao);
    }
    if(m_vbo != 0){
        glGenBuffers(1, &m_vbo);
    }
    if(m_ibo != 0){
        glGenBuffers(1, &m_ibo);
    }
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER,m_vertices.size() * sizeof(float), m_vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,m_pointIndex.size() * sizeof(float), m_pointIndex.data(), GL_STATIC_DRAW);

}
