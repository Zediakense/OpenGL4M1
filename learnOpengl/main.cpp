#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

//#include "shaderProgram.hpp"
#include "contextController.hpp"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "model/modelController.hpp"
#include "Texture.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "camera.h"
#include "gameObject.hpp"


bool keys[1024];

float deltaTime = 0.f;
float lastFrame = 0.f;
Camera camera(glm::vec3(0.0,0.0,3.0),glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,1.0,0.0));


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow *window);

void keyInput_callback(GLFWwindow *window, int key, int scancode, int action ,int mode);

int main()
{
    contextController::Instance().init();

    glfwSetKeyCallback(contextController::Instance().getWindow(), keyInput_callback);
    
    
    
    Renderer renderer;
    
    
    GameObject gotest("","shader/pureColor.shader");
    
    while(!glfwWindowShouldClose(contextController::Instance().getWindow())){
        glfwPollEvents();
        
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
       
        
        gotest.draw(renderer);
        

        glfwSwapBuffers(contextController::Instance().getWindow());
        
    }
    
    
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
        
        camera.MovePos(keys, action, deltaTime, glm::vec3(0.0,0.0,-1.0));
    }
}
