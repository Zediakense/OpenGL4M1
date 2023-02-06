//
//  modelController.cpp
//  learnOpengl
//
//  Created by user on 2023/2/5.
//

#include "modelController.hpp"


Model::Model(std::string path):
m_modelPath(path)
{
    ReadModel();
}

bool Model::ReadModel(){
    bool res = false;
    
    std::vector<float> vtem = {
        -0.5 , -0.5 ,  0.0 , 0.0 , 0.0 ,//bottom left
         0.5 , -0.5 ,  0.0 , 1.0 , 0.0 ,//bottom right
        -0.5 ,  0.5 ,  0.0 , 0.0 , 1.0 ,//top left
         0.5 ,  0.5 ,  0.0 , 1.0 , 1.0  //top right
    };
    m_vertices = vtem;
    
    std::vector<unsigned int> item = {
        0 , 1 , 2 ,
        1 , 2 , 3
    };
    
    m_indices = item;
    
    std::vector<float> uvtem = {
        0.0 , 0.0 ,
        1.0 , 0.0 ,
        0.0 , 1.0 ,
        1.0 , 1.0
    };
    m_uv = uvtem;
    
    res = true;
    return res;
}
