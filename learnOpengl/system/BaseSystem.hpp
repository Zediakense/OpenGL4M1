//
//  BaseSystem.hpp
//  learnOpengl
//
//  Created by Suchantso on 2023/2/25.
//

#ifndef BaseSystem_hpp
#define BaseSystem_hpp

#include <stdio.h>
#include "gameObject.hpp"
class System{
public:
    enum SystemType{
        base      = 0,
        motion    = 1,
        light     = 2
    };
public:
    void AddComponent(GameObject * gameObject,SystemType type = SystemType::base);
    SystemType  ParseComponentByName(const std::string name);
    virtual void tick();
private:
    std::vector<GameObject*>    m_gameObjects;
};

#endif /* BaseSystem_hpp */
