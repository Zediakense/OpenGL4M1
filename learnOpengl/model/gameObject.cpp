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
    m_vao.Bind();
    m_vbo = std::make_unique<VertexBuffer>(m_model->getData().data(),m_model->getDataSize());
    m_ibo = std::make_unique<IndexBuffer>(m_model->getIndices().data(),(unsigned int)(m_model->getIndices().size()));
    m_layout = std::make_shared<VertexBufferLayout>();
    
    for(int i = 0;i < m_model->getElements().size();i++){
        m_layout->Push(m_model->getElements()[i],"float");
    }
    
    m_vao.AddBuffer(*m_vbo, *m_layout);
    m_vao.UnBind();

    
}
GameObject::GameObject(){
    
}

void GameObject::draw(const Renderer &renderer){
    if(!m_enable){
        return;
    }
    //behavior update@todo
    temUpdateSystem(m_model->GetComponent());
    //behavior update@todo
    renderer.Drawer(m_vao, *m_ibo, *m_shader);
    
}


void GameObject::temUpdateSystem(std::string name){
    //tem use system for different object
    glm::mat4 view = glm::mat4(1.0f);
    float time = glfwGetTime();
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.f, 0.1f, 100.0f);
    glm::vec3 lightPos = glm::vec3(0.0,0.0,-3.0);
    glm::vec3 lightColor = glm::vec3(0.3,abs(cos(time)),1.0);
    
    m_shader->Bind();
    m_shader->SetUniformMat4f("view", view);
    m_shader->SetUniformMat4f("proj",projection);
    m_shader->SetUniform3f("lightPos", lightPos.x, lightPos.y, lightPos.z);
    m_shader->SetUniform3f("lightColor", lightColor.x, lightColor.y, lightColor.z);
    
    if(name == "motion"){
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(2.0 * sin(time),2.0 * cos(time), -10 * abs(sin(time))));
        glm::vec3 objectColor = glm::vec3(1.0f, 0.5f, 0.31f);
//        m_shader->SetUniform3f("objectColor", objectColor.x, objectColor.y, objectColor.z);
        m_shader->SetUniform3f("viewPos", 0.0, 0.0, -3.0);
        m_shader->SetUniformMat4f("model", model);
        m_shader->SetUniform3f("material.ambient",  1.0f, 0.5f, 0.31f);
        m_shader->SetUniform3f("material.diffuse",  1.0f, 0.5f, 0.31f);
        m_shader->SetUniform3f("material.specular", 0.5f, 0.5f, 0.5f);
        m_shader->SetUniform1f("material.shininess", 32.0f);

        m_shader->UnBind();
    }
    if(name == "light"){
        
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
//        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5,0.5,0.5));
        m_shader->SetUniformMat4f("model", model);
        m_shader->UnBind();
    }
}
