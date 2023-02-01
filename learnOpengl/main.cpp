#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "shaderProgram.hpp"
#include "contextController.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;



int main()
{
    // glfw: initialize and configure
    // ------------------------------
    

    contextController context(SCR_WIDTH,SCR_HEIGHT,"learn");
    context.init();
    context.addGameObject("");
    
    

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    
    
    context.tick();
   

    return 0;
}

