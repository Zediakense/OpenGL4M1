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
#include <fstream>

class Model{
    
public:
    enum DataType{
        vertex      = 0,
        indices     = 1,
        compnent    = 2
    };
public:
    
    Model(std::string path);
    Model();
    bool                        ReadModel();
    bool                        ReadModel(const std::string path);
    std::vector<float>          getData(){return m_vertices;}
    std::vector<unsigned int>   getIndices(){return m_indices;}
    std::vector<float>          getUV(){return m_uv;}
    unsigned int                getDataSize(){return m_vertices.size() * sizeof(float);}
    bool                        ParseModel(std::vector<float>&Data,const std::string buf);
    bool                        ParseModel(std::vector<std::string>&Data,const std::string buf);
    
    
    
private:
    
    std::string                     m_modelPath;
    std::vector<float>              m_vertices;
    std::vector<unsigned int>       m_indices;
    std::vector<float>              m_uv;
};

#endif /* modelController_hpp */
