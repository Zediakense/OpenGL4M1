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
#include "Renderer.h"
#include "Texture.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "camera.h"


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
//    GLFWwindow * window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "default", NULL, NULL);
    
//    glfwSetKeyCallback(contextController::Instance().getWindow(), keyInput_callback);
    glfwSetKeyCallback(contextController::Instance().getWindow(), keyInput_callback);
//    VertexBuffer vb;
    Model m = Model("test");
    
    Texture tex("asset/container.jpeg");
    
    Texture face("asset/awesomeface.png");
    
    
    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    
    glm::mat4 view = glm::mat4(1.0f);
    // 注意，我们将矩阵向我们要进行移动场景的反方向移动。
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.f, 0.1f, 100.0f);


    VertexArray va;

    std::vector<unsigned int> t = m.getIndices();
    
    VertexBuffer vb(m.getData().data(),m.getDataSize());
    
    VertexBufferLayout tLayout;
    
    tLayout.Push(3, "float");
    tLayout.Push(2, "float");
    
    va.AddBuffer(vb, tLayout);
    
    IndexBuffer ib(m.getIndices().data(),(unsigned int)(m.getIndices().size()));
    
    Shader shader("shader/pureColor.shader");
    
    
    
    tex.Bind();
    
    face.Bind(1);
    
    Renderer renderer;
    
    shader.Bind();
    
    shader.SetUniform1i("BaseTex", 0);
    
    shader.SetUniform1i("tex1", 1);
    
    shader.SetUniformMat4f("model", model);

    shader.SetUniformMat4f("proj", projection);
    
//    shader.SetUniformMat4f("view", view);
    
    
    
    shader.UnBind();
    
    
    
    
    while(!glfwWindowShouldClose(contextController::Instance().getWindow())){
        glfwPollEvents();
        
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        // Clear the colorbuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        renderer.Clear();
        shader.Bind();
        
        glm::mat4 view = glm::lookAt(camera.getPos(), camera.getTarget(), camera.getUpvec());
        
        shader.SetUniformMat4f("view", view);
        
        renderer.Drawer(va, ib, shader);
        va.UnBind();
        ib.Unbind();
        shader.UnBind();

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
