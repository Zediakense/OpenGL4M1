//
//  contextController.hpp
//  learnOpengl
//
//  Created by suchantso on 2023/2/1.
//

#ifndef contextController_hpp
#define contextController_hpp

#include <stdio.h>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "gameObject.hpp"
class contextController{
    struct go{
        gameObject * go;
        int index ;
        struct go * next;
    };
public:
    contextController(unsigned int width,unsigned int height,std::string name);
    bool init();
    bool ifClose();
    void tick();
    void addGameObject(std::string path);
private:
    unsigned int                m_width;
    unsigned int                m_height;
    std::string                 m_name;
    GLFWwindow*                 m_window;
    struct go *                 m_go = nullptr;
    
};
#endif /* contextController_hpp */
