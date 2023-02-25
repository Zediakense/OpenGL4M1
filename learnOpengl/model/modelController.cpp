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
    ReadModel(path);
}

Model::Model(){
    
};

bool Model::ReadModel(){
    bool res = false;
    
    std::vector<float> vtem = {
        -0.5 , -0.5 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,//bottom left
         0.5 , -0.5 , 0.0 , 0.0 , 0.0 , 0.0 , 1.0 , 0.0 ,//bottom right
        -0.5 ,  0.5 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 1.0 ,//top left
         0.5 ,  0.5 , 0.0 , 0.0 , 0.0 , 0.0 , 1.0 , 1.0  //top right
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


bool Model::ReadModel(const std::string path){
    //for quick use, let's define that model files are consisted like
    //#vertex 4 //which means there are vertices for 4 lines which include position for 3 floats,color for 3 floats and uv for 2 floats
    //vertex datas are following below
    //#indices 2 //which means there are vertices index for 2 lines which include 3 floats for a triangle
    //all datas are seperated by a space
    bool res = false;
    std::ifstream file;
    file.open(path.c_str());
    if(!file.is_open()){
        printf("failed to open Model : %s\n",path.c_str());
        return res;
    }
    std::string buf;
    std::vector<std::vector<float>>temVertexBuffer(2);
    DataType state = DataType::vertex;
    while(getline(file, buf)){
        if(buf.find("#vertex") != std::string::npos){
            state = DataType::vertex;
            continue;
        }
        else if(buf.find("#indices") != std::string::npos){
            state = DataType::indices;
            continue;
        }
        //后续需要补齐texture和component@todo
        ParseModel(temVertexBuffer[state],buf);
    }
    m_vertices = temVertexBuffer[DataType::vertex];
    m_indices = std::vector<unsigned int>(temVertexBuffer[DataType::indices].begin(),temVertexBuffer[DataType::indices].end());
    
    res = true;
    
    return res;
}

bool Model::ParseModel(std::vector<float> &Data, const std::string buf){
    bool res = false;
    int length = buf.length();
    int start = 0, p = 0;
    while(start < length){
        if(buf[p] == ' ' || p == length - 1){
            int offset = p == (length - 1) ? 1 : 0;
            float temData = std::stof(buf.substr(start,p - start + offset));
            Data.emplace_back(temData);
            start = p + 1;
            p = start;
        }
        else{
            p ++;
        }
    }
    res = true;
    return res;
}
