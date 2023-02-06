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

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main()
{
    contextController::Instance().init();
//    GLFWwindow * window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "default", NULL, NULL);
    
//    VertexBuffer vb;
    Model m = Model("test");
    
    Texture tex("shader/lut.png");
    
    VertexArray va;
//    va.Bind();
    std::vector<unsigned int> t = m.getIndices();
    
    VertexBuffer vb(m.getData().data(),m.getDataSize());
    
    VertexBufferLayout tLayout;
    
    tLayout.Push(3, "float");
    tLayout.Push(2, "float");
    
    va.AddBuffer(vb, tLayout);
    
    IndexBuffer ib(m.getIndices().data(),(unsigned int)(m.getIndices().size()));
    
    Shader shader("shader/pureColor.shader");
    
    tex.Bind();
    
    Renderer renderer;
    
    
    
    
    while(!glfwWindowShouldClose(contextController::Instance().getWindow())){
        glfwPollEvents();
        
        // Clear the colorbuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        renderer.Clear();
        shader.Bind();
        
        renderer.Drawer(va, ib, shader);
        va.UnBind();
        ib.Unbind();
        shader.UnBind();

        glfwSwapBuffers(contextController::Instance().getWindow());
        
    }
    return 0;
}

