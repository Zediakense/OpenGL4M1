//
//  lightSystem.hpp
//  learnOpengl
//
//  Created by user on 2023/2/12.
//

#ifndef lightSystem_hpp
#define lightSystem_hpp


#include <stdio.h>
#include <glm/glm.hpp>


enum lightType{
    spotLight = 0
};

struct lightNode{
    glm::vec3 Pos;
    glm::vec4 LightColor;
    lightType type;
};
class lightSystem{
public:
    void addLight(glm::vec3 pos = glm::vec3(0.0,0.0,0.0),glm::vec4 color = glm::vec4(1.0,1.0,1.0,1.0), lightType type = lightType::spotLight);
private:
    
};

#endif /* lightSystem_hpp */
