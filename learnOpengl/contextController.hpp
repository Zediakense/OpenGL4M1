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
class contextController{
public:
    contextController(unsigned int width = 800,unsigned int height = 600,std::string name = "default");
    bool init();
    bool ifClose();
    void tick();
    void addGameObject(std::string path);
    GLFWwindow * getWindow(){return m_window;}
    static contextController& Instance();
private:
    unsigned int                m_width;
    unsigned int                m_height;
    std::string                 m_name;
    GLFWwindow*                 m_window;
    
};
#endif /* contextController_hpp */
