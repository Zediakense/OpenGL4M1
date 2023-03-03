//
//  contextController.cpp
//  learnOpengl
//
//  Created by suchantso on 2023/2/1.
//

#include "contextController.hpp"

contextController::contextController(unsigned int width,unsigned int height,std::string name):
m_width(width),
m_height(height),
m_name(name)
{
    
}

bool contextController::init(unsigned int width,unsigned int height,std::string name){
    m_width = width;
    m_height = height;
    m_name = name;
    
    
    bool res = false;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    m_window = glfwCreateWindow(m_width, m_height, m_name.c_str(), NULL, NULL);
    if (m_window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return res;
    }
    glfwMakeContextCurrent(m_window);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return res;
    }
    
    LoadDummyNode();
    
    
    return true;
}

contextController & contextController::Instance(){
    static contextController instance;
    return instance;
}

void contextController::tick(){
    while(!glfwWindowShouldClose(m_window)){
        glfwPollEvents();

        tickSystem();
        tickGameObject();
        glfwSwapBuffers(m_window);

    }
}

void contextController::shutDown(){
    
}

void contextController::LoadDummyNode(){
    m_go = std::make_shared<GameObject>();
    m_go ->SetChild(nullptr);
    m_go ->SetParent(nullptr);
}

void contextController::tickGameObject(){
    std::shared_ptr<GameObject> p = m_go;
    Renderer renderer;
    while(p != nullptr){
        p->draw(renderer);
        p = p->GetChild();
    }
}

void contextController::tickSystem(){
    //let's replace systems with a pure color instead
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void contextController::addGameObject(std::string ModelPath ,std::string ShaderPath){
    std::shared_ptr<GameObject> p = m_go ;
    while (p -> GetChild() != nullptr) {
        p = p -> GetChild();
    }
    std::shared_ptr<GameObject> add = std::make_shared<GameObject>(ModelPath,ShaderPath);
    p->SetChild(add);
    add->SetParent(p);
    add->SetChild(nullptr);
    add->SetEnable(true);
}



