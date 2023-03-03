//
//  motionSystem.hpp
//  learnOpengl
//
//  Created by user on 2023/2/28.
//

#ifndef motionSystem_hpp
#define motionSystem_hpp

#include <stdio.h>
#include "BaseSystem.hpp"
class MotionSystem:public System{
public:
    void AddComponent(GameObject * gameObject,SystemType type = SystemType::base);
};

#endif /* motionSystem_hpp */
