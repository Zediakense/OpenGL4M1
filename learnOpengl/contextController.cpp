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

bool contextController::init(){
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
//        return -1;
    }
    glfwMakeContextCurrent(m_window);
//    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
        return res;
    }
    return true;
}

void contextController::tick(){
    while(!glfwWindowShouldClose(m_window)){
        //draw background
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //draw background
        
        //draw elements
        struct go * p = m_go;
        while(p != nullptr){
            p->go->draw();
            p = p ->next;
        }
        //draw elements
        
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
    //destroy go
    struct go * p = m_go;
    while(p != nullptr){
        p->go->destroy();
        p = p ->next;
    }
    //destroy
    glfwTerminate();

}

void contextController::addGameObject(std::string path){
    if(m_go == nullptr){
        m_go = new struct go();
        m_go -> index = 0;
        m_go -> go = new gameObject();
        m_go -> go -> readModel("");
        
        m_go -> next = nullptr;
        return;
    }
    struct go * p = m_go;
    int indx = 0;
    while(p->next != nullptr){
        indx = p ->index;
        p = p->next;
    }
    struct go * q = new struct go;
    q -> index = indx + 1;
    q -> go = new gameObject();
    q -> next = nullptr;
    p -> next = q;
    
}
