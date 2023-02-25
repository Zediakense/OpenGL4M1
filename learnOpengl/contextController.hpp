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
public:
    contextController(unsigned int width = 800,unsigned int height = 600,std::string name = "default");
    bool init(unsigned int width,unsigned int height,std::string name);
    bool ifClose();
    void tick();
    void addGameObject(std::string path);//as a whole resource,it should find its model path and shader path in one file
    void addGameObject(std::string ModelPath,std::string ShaderPath);//for quick use,let gave it an exsit model path and a shader path
    GLFWwindow * getWindow(){return m_window;}
    static contextController& Instance();
    void shutDown();
    void LoadDummyNode();
    void tickSystem();
    void tickGameObject();
    
private:
    unsigned int                m_width;
    unsigned int                m_height;
    std::string                 m_name;
    GLFWwindow*                 m_window;
    std::shared_ptr<GameObject> m_go = nullptr;
    
};
#endif /* contextController_hpp */
