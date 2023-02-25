//
//  gameObject.cpp
//  learnOpengl
//
//  Created by Suchantso on 2023/2/17.
//

#include "gameObject.hpp"


GameObject::GameObject(std::string ModelPath,std::string shaderPath):
m_modelPath(ModelPath),
m_shaderPath(shaderPath)
{
    m_shader = std::make_shared<Shader>(m_shaderPath);
    m_model  = std::make_unique<Model>(m_modelPath);
//    m_shader ->ReadShader(m_shaderPath);
    m_vao.Bind();
    m_vbo = std::make_unique<VertexBuffer>(m_model->getData().data(),m_model->getDataSize());
    m_ibo = std::make_unique<IndexBuffer>(m_model->getIndices().data(),(unsigned int)(m_model->getIndices().size()));
    m_layout = std::make_shared<VertexBufferLayout>();
    m_layout->Push(3, "float");//pos
    m_layout->Push(3, "float");//color
    m_layout->Push(2, "float");//uv
    m_vao.AddBuffer(*m_vbo, *m_layout);
    m_vao.UnBind();

    
}
GameObject::GameObject(){
    
}

void GameObject::draw(const Renderer &renderer){
    if(!m_enable){
        return;
    }
    //behavior update@tode
    renderer.Drawer(m_vao, *m_ibo, *m_shader);
    
}
