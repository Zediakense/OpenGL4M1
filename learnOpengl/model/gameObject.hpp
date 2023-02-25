//
//  gameObject.hpp
//  learnOpengl
//
//  Created by Suchantso on 2023/2/17.
//

#ifndef gameObject_hpp
#define gameObject_hpp

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "modelController.hpp"
#include <stdio.h>
#include "Shader.h"
#include "Renderer.h"
class GameObject{
public:
    GameObject();
    GameObject(std::string ModelPath,std::string shaderPath);
    void draw(const Renderer & renderer);
    void SetParent(std::shared_ptr<GameObject> parent){m_parent = parent;}
    void SetChild(std::shared_ptr<GameObject> child){m_child = child;}
    void SetEnable(bool enable){m_enable = enable;}
    std::shared_ptr<GameObject>GetChild(){return m_child;}
    
private:
    VertexArray                         m_vao;
    std::unique_ptr<VertexBuffer>       m_vbo = nullptr;
    std::unique_ptr<IndexBuffer>        m_ibo = nullptr;
    std::string                         m_modelPath = "";
    std::string                         m_shaderPath = "";
    std::unique_ptr<Model>              m_model = nullptr;
    std::shared_ptr<Shader>             m_shader = nullptr;
    std::shared_ptr<VertexBufferLayout> m_layout;
    std::shared_ptr<GameObject>         m_parent = nullptr;
    std::shared_ptr<GameObject>         m_child = nullptr;
    bool                                m_enable = false;
    
};


#endif /* gameObject_hpp */
