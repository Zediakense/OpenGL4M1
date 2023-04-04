#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "contextController.hpp"
#include "BaseSystem.hpp"
#include "motionSystem.hpp"


bool keys[1024];

float deltaTime = 0.f;
float lastFrame = 0.f;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void keyInput_callback(GLFWwindow *window, int key, int scancode, int action ,int mode);

int main()
{
    contextController::Instance().init(800, 600, "LearnOpenGL");

    glfwSetKeyCallback(contextController::Instance().getWindow(), keyInput_callback);
    
    
    contextController::Instance().addGameObject("asset/box.model", "shader/box.shader");
    contextController::Instance().addGameObject("asset/light.model", "shader/light.shader");
    contextController::Instance().GetSubsystem<MotionSystem>();
//    assert(false);
    contextController::Instance().tick();
    
    return 0;
}


void keyInput_callback(GLFWwindow *window, int key, int scancode, int action ,int mode){
    if(key >= 0 && key < 1024){
        if(action == GLFW_PRESS){
            keys[key] = true;
        }
        else if(action == GLFW_RELEASE){
            keys[key] = false;
        }
        
    }
}
