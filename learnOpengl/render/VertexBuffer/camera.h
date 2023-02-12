#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
class Camera{
private:
    glm::vec3 m_Pos;
    glm::vec3 m_Target;
    glm::vec3 m_UpVec;

    glm::vec3 goUp;
    glm::vec3 goLeft;
    glm::vec3 goDown;
    glm::vec3 goRight;

public:
    Camera(glm::vec3 position,glm::vec3 target,glm::vec3 upvector);
    ~Camera();

    void MovePos(bool*key,int action,float deltaTime,glm::vec3 cameraFront);


    glm::vec3 getPos()const;
    glm::vec3 getTarget()const;
    glm::vec3 getUpvec()const;
};
