#include"camera.h"
Camera::Camera(glm::vec3 position,glm::vec3 target,glm::vec3 upvector)
:m_Pos(position),
m_Target(target),
m_UpVec(upvector),
goDown(glm::vec3(0.0f,0.0f,-1.0f)),
goLeft(glm::vec3(-1.0f,0.0f,0.0f)),
goRight(glm::vec3(1.0f,0.0f,0.0f)),
goUp(glm::vec3(0.0f,0.0f,1.0f))
{
}
Camera::~Camera(){

}

void Camera::MovePos(bool*key,int action,float deltaTime,glm::vec3 cameraFront){
    if(key[GLFW_KEY_W]){
        m_Pos+=cameraFront*deltaTime;
//        printf("camera go front");
    }
    if(key[GLFW_KEY_S])m_Pos-=cameraFront*deltaTime;
    if(key[GLFW_KEY_A])m_Pos+=glm::cross(m_UpVec,cameraFront)*deltaTime;
    if(key[GLFW_KEY_D])m_Pos-=glm::cross(m_UpVec,cameraFront)*deltaTime;
}

glm::vec3 Camera::getPos()const{return m_Pos;}
glm::vec3 Camera::getTarget()const{return m_Target;}
glm::vec3 Camera::getUpvec()const{return m_UpVec;}
