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

contextController & contextController::Instance(){
    static contextController instance;
    return instance;
}




