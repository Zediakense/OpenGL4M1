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
#include <glm/glm.hpp>

class Model{
    
public:
    enum DataType{
        VertexPos   = 0,
        VertexUV    = 1,
        VertexColor = 2,
        indices     = 3,
        compnent    = 4
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
    std::vector<unsigned int>   getElements(){return m_elements;}
    void                        combineVertex(std::vector<std::vector<float>>points);
    //temp use before we get a better way to deal whole engine
    bool                        ParseComponent(std::string&Data,const std::string buf);//temp use once
    std::string                 GetComponent(){return m_temComponent;}
    
    
    
    
private:
    
    std::string                     m_modelPath;
    std::vector<float>              m_vertices;
    std::vector<unsigned int>       m_indices;
    std::vector<float>              m_uv;
    std::vector<unsigned int>       m_elements;
    bool                            m_posFlag = false;
    bool                            m_colorFlag = false;
    bool                            m_uvFlag = false;
    std::string                     m_temComponent = "";//we can use one component for an object once
};

#endif /* modelController_hpp */
