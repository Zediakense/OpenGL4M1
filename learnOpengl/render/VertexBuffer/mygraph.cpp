//#include <iostream>
//
//// GLEW
//#include <GL/glad.h>
//
//// GLFW
//#include <GL/glfw3.h>
//#include<string>
//#include<fstream>
//#include<sstream>
//#include"Renderer.cpp"
//#include"VertexBuffer.cpp"
//#include"IndexBuffer.cpp"
//#include"VertexArray.cpp"
//#include"VertexBufferLayout.h"
//#include"Shader.cpp"
//#include"Texture.cpp"
//#include"libs/glm/glm.hpp"
//#include"libs/glm/gtc/matrix_transform.hpp"
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>
//#include"camera.cpp"
//#include"Model.h"
//
//
//
//const GLuint WIDTH = 800, HEIGHT = 600;
//
//bool keys[1024];
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//float lastX = 400, lastY = 300;
//float yaw =-90.0f,pitch=0.0f;
//glm::vec3 cameraFront=glm::vec3(0.0f,0.0f,-1.0f);
//
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//Camera camera(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f));
//bool firstMouse=true;
//
//int main(){
//    GLFWwindow *window;
//    if(!glfwInit()){
//        return -1;
//    }
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
//    window =glfwCreateWindow(WIDTH,HEIGHT,"hello world",NULL,NULL);
//    if(!window){
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//    glfwSwapInterval(1);
//    glfwSetKeyCallback(window, key_callback);
//    glfwSetCursorPosCallback(window, mouse_callback);
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
//	    std::cout << "Failed to initialize GLAD" << std::endl;
//	    return -1;
//	}
//
//    float positions[]={
//        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//
//        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
//         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
//         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
//         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
//
//        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//
//         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//
//        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//
//        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
//
//    };
//
//    float skybox[]={
//        // Positions
//        -1.0f,  1.0f, -1.0f,
//        -1.0f, -1.0f, -1.0f,
//         1.0f, -1.0f, -1.0f,
//         1.0f, -1.0f, -1.0f,
//         1.0f,  1.0f, -1.0f,
//        -1.0f,  1.0f, -1.0f,
//
//        -1.0f, -1.0f,  1.0f,
//        -1.0f, -1.0f, -1.0f,
//        -1.0f,  1.0f, -1.0f,
//        -1.0f,  1.0f, -1.0f,
//        -1.0f,  1.0f,  1.0f,
//        -1.0f, -1.0f,  1.0f,
//
//         1.0f, -1.0f, -1.0f,
//         1.0f, -1.0f,  1.0f,
//         1.0f,  1.0f,  1.0f,
//         1.0f,  1.0f,  1.0f,
//         1.0f,  1.0f, -1.0f,
//         1.0f, -1.0f, -1.0f,
//
//        -1.0f, -1.0f,  1.0f,
//        -1.0f,  1.0f,  1.0f,
//         1.0f,  1.0f,  1.0f,
//         1.0f,  1.0f,  1.0f,
//         1.0f, -1.0f,  1.0f,
//        -1.0f, -1.0f,  1.0f,
//
//        -1.0f,  1.0f, -1.0f,
//         1.0f,  1.0f, -1.0f,
//         1.0f,  1.0f,  1.0f,
//         1.0f,  1.0f,  1.0f,
//        -1.0f,  1.0f,  1.0f,
//        -1.0f,  1.0f, -1.0f,
//
//        -1.0f, -1.0f, -1.0f,
//        -1.0f, -1.0f,  1.0f,
//         1.0f, -1.0f, -1.0f,
//         1.0f, -1.0f, -1.0f,
//        -1.0f, -1.0f,  1.0f,
//         1.0f, -1.0f,  1.0f
//    };
//
//
//
//    unsigned int indices[]={
//        0,1,2,
//    };
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
//
//
//    // VertexArray va;
//    VertexArray skyVa;
//    // VertexBuffer vb(positions,sizeof(positions)) ;
//    VertexBuffer skyVb(skybox,sizeof(skybox));
//
//    // VertexBufferLayout layout;
//    VertexBufferLayout skyLayout;
//    // layout.Push(3,"float");
//    // layout.Push(3,"float");
//    skyLayout.Push(3,"float");
//    // va.AddBuffer(vb,layout);
//    skyVa.AddBuffer(skyVb,skyLayout);
//    IndexBuffer ib(indices,36),skyIb(indices,36);
//
//
//    // Model testModel("./model/nanosuit/nanosuit.obj");
//
//    glm::mat4 proj=glm::ortho(-1.0f,1.0f,-1.0f,1.0f,-1.0f,1.0f);
//    glm::mat4 model,view;
//    model=glm::rotate(proj,0.0f, glm::vec3(1.0f, 1.0f, 0.0f));
//    view = glm::lookAt(camera.getPos(),camera.getPos()+glm::vec3(0.0f,0.0f,-1.0f),glm::vec3(0.0f,1.0f,0.0f));
//    glm::mat4 projection= glm::perspective(45.0f,4.0f/3, 0.1f, 100.0f);
//    glm::mat4 trans=projection*view*model;
//
//    Shader shader("./res/ModelShader.shader");
//    Shader skyShader("./res/skyShader.shader");
//    skyShader.SetUniform1i("skybox",0);
//    // shader.Bind();
//    // shader.SetUniformMat4f("model",model);
//    // shader.SetUniformMat4f("view",view);
//    // shader.SetUniformMat4f("projection",projection);
//    // // shader.SetUniform3f("light_pos",0.0f,0.0f,4.0f);
//    // shader.SetUniform3f("camera_pos",camera.getPos().x,camera.getPos().y,camera.getPos().z);
//    // shader.SetUniform3f("lightcolor",1.0f,1.0f,1.0f);
//    // shader.SetUniform3f("objectColor",0.8f, 0.2f, 0.31f);//1.0f, 0.5f, 0.31f
//    // shader.SetUniformMat4f("u_m",model);
//    // shader.SetUniformMat4f("u_v",view);
//    // shader.SetUniformMat4f("u_p",projection);
//    std::vector<const char*>images;
//    images.push_back("./stb_image/skybox_right.jpg");
//    images.push_back("./stb_image/skybox_left.jpg");
//    images.push_back("./stb_image/skybox_top3.jpg");
//    images.push_back("./stb_image/skybox_bottom1.jpg");
//    images.push_back("./stb_image/skybox_back.jpg");
//    images.push_back("./stb_image/skybox_front.jpg");
//
//    // images.push_back("./stb_image/fav.jpg");
//    // images.push_back("./stb_image/fav.jpg");
//    // images.push_back("./stb_image/fav.jpg");
//    // images.push_back("./stb_image/fav.jpg");
//    // images.push_back("./stb_image/fav.jpg");
//    // images.push_back("./stb_image/fav.jpg");
//    mTexture texture(images);
//    texture.skyBind();
//    // shader.SetUniform1i("u_Texture",0);
//
//    // va.UnBind();
//    // shader.UnBind();
//    // vb.Unbind();
//    // ib.Unbind();
//
//    Renderer renderer;
//
//    glEnable(GL_DEPTH_TEST);
//    // glEnable(GL_CULL_FACE);//定义点的时候需要统一顺时针或者逆时针
//
//    // view = glm::lookAt(camera.getPos(),camera.getPos()+cameraFront,glm::vec3(0.0f,1.0f,0.0f));
//    //     shader.SetUniformMat4f("view",view);
//    //     shader.SetUniformMat4f("projection",projection);
//    //     glm::mat4 _model;
//    //     _model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // Translate it down a bit so it's at the center of the scene
//    //     _model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// It's a bit too big for our scene, so scale it down
//    //     shader.SetUniformMat4f("model",_model);
//
//
//     while (!glfwWindowShouldClose(window))
//    {
//
//        float currentFrame = glfwGetTime();
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
//
//        glfwPollEvents();
//
//        // Clear the colorbuffer
//        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//
//    //     glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//    //     glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
//    //     glDepthMask(GL_FALSE);
//    //     renderer.Clear();
//        skyShader.Bind();
//        glm::mat4 mview1 = view;	// Remove any translation component of the view matrix
//        glm::mat4 mprojection = glm::perspective(45.0f, 4.0f/3, 0.1f, 100.0f);
//        skyShader.SetUniformMat4f("view",mview1);
//        skyShader.SetUniformMat4f("projection",mprojection);
//        renderer.Drawer(skyVa,skyIb,skyShader);
//        skyVa.UnBind();
//        skyIb.Unbind();
//        skyShader.UnBind();
//
//    //     glDepthMask(GL_TRUE);
//
//
//    //     shader.Bind();
//
//    //     testModel.Draw(shader);
//    //     shader.UnBind();
//    //     // shader.SetUniform3f("camera_pos",camera.getPos().x,camera.getPos().y,camera.getPos().z);
//    //     // renderer.Drawer(va,ib,shader);
//
//
//    //     // shader.SetUniform4f("u_Color",0.8f,0.3f,0.8f,1.0f);
//    //     // trans= glm::rotate(proj,(GLfloat)glfwGetTime() * 50.0f, glm::vec3(0.0f, 0.0f, 1.0f));
//    //     // shader.SetUniformMat4f("u_MVP",trans);
//    // //    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,nullptr);
//    //     glfwSwapBuffers(window);
//
//    //     glfwPollEvents();
//
//        // Check and call events
//
//
//        shader.Bind();   // <-- Don't forget this one!
//        // Transformation matrices
//        glm::mat4 projection = glm::perspective(45.0f, 4.0f/3, 0.1f, 100.0f);
//        glm::mat4 mview = view;
//        shader.SetUniformMat4f("projection",projection);
//        shader.SetUniformMat4f("view",mview);
//        // glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
//        // glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
//
//        // Draw the loaded model
//        glm::mat4 model;
//        model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // Translate it down a bit so it's at the center of the scene
//        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// It's a bit too big for our scene, so scale it down
//        // glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
//        shader.SetUniformMat4f("model",model);
//        // testModel.Draw(shader);
//        shader.UnBind();
//
//        // Swap the buffers
//        glfwSwapBuffers(window);
//
//
//
//
//
//
//
//
//
//
//
//
//
//    }
//    glfwTerminate();
//    return 0;
//}
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
//{
//    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
//        glfwSetWindowShouldClose(window, GL_TRUE);
//        std::cout<<"space pressed"<<std::endl;
//    }
//    if (key >= 0 && key < 1024)
//    {
//
//        if (action == GLFW_PRESS)
//            keys[key] = true;
//        else if (action == GLFW_RELEASE)
//            keys[key] = false;
//
//        camera.MovePos(keys,action,deltaTime,cameraFront);
//    }
//}
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//    printf("test mouse x = %lf, y = %lf\n",xpos,ypos);
//    if(firstMouse)
//    {
//        lastX = xpos;
//        lastY = ypos;
//        firstMouse = false;
//    }
//
//    float xoffset = xpos - lastX;
//    float yoffset = lastY - ypos;
//
//    lastX = xpos;
//    lastY = ypos;
//
//    float sensitivity = 0.05;	// Change this value to your liking
//    xoffset *= sensitivity;
//    yoffset *= sensitivity;
//
//    yaw   += xoffset;
//    pitch += yoffset;
//
//    // Make sure that when pitch is out of bounds, screen doesn't get flipped
//    if (pitch > 89.0f)
//        pitch = 89.0f;
//    if (pitch < -89.0f)
//        pitch = -89.0f;
//
//    glm::vec3 front;
//    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
//    front.y = sin(glm::radians(pitch));
//    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
//    cameraFront = glm::normalize(front);
//}
