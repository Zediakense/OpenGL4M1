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
    std::vector<std::vector<float>>temVertexBuffer(4);
    DataType state = DataType::VertexPos;
    while(getline(file, buf)){
        if(buf.find("#position") != std::string::npos){
            state = DataType::VertexPos;
            m_posFlag = true;
            m_elements.push_back(3);//positions are always a vector 3
            m_elements.push_back(3);//norm comes with pos
            continue;
        }
        else if(buf.find("#uv") != std::string::npos){
            state = DataType::VertexUV;
            m_uvFlag = true;
            m_elements.push_back(2);//let's define all vertices use 2d texture
            continue;
        }
        else if(buf.find("#color") != std::string::npos){
            state = DataType::VertexColor;//colors are always a vector 3
            m_colorFlag = true;
            m_elements.push_back(3);
            continue;
        }
        else if(buf.find("#indices") != std::string::npos){
            state = DataType::indices;
            continue;
        }
        else if(buf.find("#component") != std::string::npos){
            state = DataType::compnent;
        }
        //后续需要补齐texture和component@todo
        if(state == DataType::VertexPos || state == DataType::indices || state == DataType::VertexUV || state == DataType::VertexColor){
            ParseModel(temVertexBuffer[state],buf);
        }
        else if(state == DataType::compnent){
            ParseComponent(m_temComponent, buf);
        }
    }
//    m_vertices = temVertexBuffer[DataType::VertexPos];
//    m_indices = std::vector<unsigned int>(temVertexBuffer[DataType::indices].begin(),temVertexBuffer[DataType::indices].end());
    
    combineVertex(temVertexBuffer);
    
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

bool Model::ParseComponent(std::string &Data, const std::string buf){
    bool res = false;
    //tem use
    Data = buf;
    //tem use
    return res;
}

void Model::combineVertex(std::vector<std::vector<float>> points){
    
    int psize = points[DataType::VertexPos].size();
    int csize = points[DataType::VertexColor].size();
    int usize = points[DataType::VertexUV].size();
    
    std::vector<float>vertex;
    
    for(int i = 0;i<=points[DataType::indices].size() - 3;i+=3){
        unsigned int iv1 = points[DataType::indices][i];
        unsigned int iv2 = points[DataType::indices][i + 1];
        unsigned int iv3 = points[DataType::indices][i + 2];

        int max1 = iv1 * 3 + 2;
        int max2 = iv2 * 3 + 2;
        int max3 = iv3 * 3 + 2;
        
        int umax1 = iv1 * 2 + 1;
        int umax2 = iv2 * 2 + 1;
        int umax3 = iv3 * 2 + 1;
        
        bool posInvalid = m_posFlag && (max1 >= psize || max2 >= psize || max3 >= psize);
        bool uvInvalid = m_uvFlag && (umax1 >= usize || umax2 >= usize || umax3 >= usize);
        bool colorInvalid = m_colorFlag && (max1 >= csize || max2 >= csize || max3 >= csize);
        if(posInvalid || uvInvalid || colorInvalid){
            printf("invalid model\n");
            return;
        }

        glm::vec3 p1 = glm::vec3(0.0);
        glm::vec3 p2 = glm::vec3(0.0);
        glm::vec3 p3 = glm::vec3(0.0);
        
        glm::vec3 color1 = glm::vec3(0.0);
        glm::vec3 color2 = glm::vec3(0.0);
        glm::vec3 color3 = glm::vec3(0.0);
        
        glm::vec2 uv1 = glm::vec2(0.0);
        glm::vec2 uv2 = glm::vec2(0.0);
        glm::vec2 uv3 = glm::vec2(0.0);

        glm::vec3 norm1 = glm::vec3(0.0);
        glm::vec3 norm2 = glm::vec3(0.0);
        glm::vec3 norm3 = glm::vec3(0.0);


        
        //pos
        if(m_posFlag){
            p1 = glm::vec3(points[DataType::VertexPos][iv1 * 3],points[DataType::VertexPos][iv1 * 3 + 1],points[DataType::VertexPos][max1]);
            p2 = glm::vec3(points[DataType::VertexPos][iv2 * 3],points[DataType::VertexPos][iv2 * 3 + 1],points[DataType::VertexPos][max2]);
            p3 = glm::vec3(points[DataType::VertexPos][iv3 * 3],points[DataType::VertexPos][iv3 * 3 + 1],points[DataType::VertexPos][max3]);
        }
        
        //color
        if(m_colorFlag){
            color1 = glm::vec3(points[DataType::VertexColor][iv1 * 3],points[DataType::VertexColor][iv1 * 3 + 1],points[DataType::VertexColor][max1]);
            color2 = glm::vec3(points[DataType::VertexColor][iv2 * 3],points[DataType::VertexColor][iv2 * 3 + 1],points[DataType::VertexColor][max2]);
            color3 = glm::vec3(points[DataType::VertexColor][iv3 * 3],points[DataType::VertexColor][iv3 * 3 + 1],points[DataType::VertexColor][max3]);
        }
        
        //uv
        if(m_uvFlag){
            uv1 = glm::vec2(points[DataType::VertexUV][iv1 * 2],points[DataType::VertexUV][umax1]);
            uv2 = glm::vec2(points[DataType::VertexUV][iv2 * 2],points[DataType::VertexUV][umax2]);
            uv3 = glm::vec2(points[DataType::VertexUV][iv3 * 2],points[DataType::VertexUV][umax3]);
        }
        
        //norm
        if(m_posFlag){
            norm1 = glm::cross(p1 - p2, p1 - p3);
            norm2 = norm1;
            norm3 = norm1;
        }
        
        //combine
        if(m_posFlag){
            vertex.push_back(p1.x);
            vertex.push_back(p1.y);
            vertex.push_back(p1.z);
        }
        if(m_colorFlag){
            vertex.push_back(color1.x);
            vertex.push_back(color1.y);
            vertex.push_back(color1.z);
        }
        if(m_uvFlag){
            vertex.push_back(uv1.x);
            vertex.push_back(uv1.y);
        }
        if(m_posFlag){
            vertex.push_back(norm1.x);
            vertex.push_back(norm1.y);
            vertex.push_back(norm1.z);
        }
        
        if(m_posFlag){
            vertex.push_back(p2.x);
            vertex.push_back(p2.y);
            vertex.push_back(p2.z);
        }
        if(m_colorFlag){
            vertex.push_back(color2.x);
            vertex.push_back(color2.y);
            vertex.push_back(color2.z);
        }
        if(m_uvFlag){
            vertex.push_back(uv2.x);
            vertex.push_back(uv2.y);
        }
        if(m_posFlag){
            vertex.push_back(norm1.x);
            vertex.push_back(norm1.y);
            vertex.push_back(norm1.z);
        }
        
        if(m_posFlag){
            vertex.push_back(p3.x);
            vertex.push_back(p3.y);
            vertex.push_back(p3.z);
        }
        if(m_colorFlag){
            vertex.push_back(color3.x);
            vertex.push_back(color3.y);
            vertex.push_back(color3.z);
        }
        if(m_uvFlag){
            vertex.push_back(uv3.x);
            vertex.push_back(uv3.y);
        }
        if(m_posFlag){
            vertex.push_back(norm1.x);
            vertex.push_back(norm1.y);
            vertex.push_back(norm1.z);
        }
        
        
    }
    m_vertices = vertex;
    for(int i = 0;i<m_vertices.size();i++){
        m_indices.push_back((unsigned int)i);
    }
}



/**
 -0.5 -0.5 -0.5 0.0 0.0 0.0
 -0.5 -0.5 0.5 0.0 0.0 0.0
 -0.5 0.5 -0.5 0.0 0.0 0.0
 -0.5 0.5 0.5 0.0 0.0 0.0
 0.5 -0.5 -0.5 0.0 0.0 0.0
 0.5 -0.5 0.5 0.0 0.0 0.0
 0.5 0.5 -0.5 0.0 0.0 0.0
 0.5 0.5 0.5 0.0 0.0 0.0
 
 
 
 0 1 2
 1 2 3
 0 1 4
 1 4 5
 1 5 7
 1 7 3
 0 4 6
 0 6 2
 3 7 6
 3 6 2
 5 4 7
 4 6 7
 */
