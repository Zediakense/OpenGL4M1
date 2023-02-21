//
//  modelController.hpp
//  learnOpengl
//
//  Created by user on 2023/2/5.
//

#ifndef modelController_hpp
#define modelController_hpp

#include <stdio.h>
#include <string>
#include <vector>

class Model{
public:
    Model(std::string path);
    Model();
    bool ReadModel();
    std::vector<float>          getData(){return m_vertices;}
    std::vector<unsigned int>   getIndices(){return m_indices;}
    std::vector<float>          getUV(){return m_uv;}
    unsigned int                getDataSize(){return m_vertices.size() * sizeof(float);}
    
    
    
private:
    std::string                     m_modelPath;
    std::vector<float>              m_vertices;
    std::vector<unsigned int>       m_indices;
    std::vector<float>              m_uv;
};

#endif /* modelController_hpp */
