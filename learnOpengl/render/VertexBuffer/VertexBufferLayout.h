#pragma once
#include<vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<string>
struct VertexBufferElement{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;
    static unsigned int GetSizeofType(unsigned int type){
        switch (type)
        {
        case GL_FLOAT:          return  4;
        case GL_UNSIGNED_INT:   return  4;
        case GL_UNSIGNED_BYTE:  return  2;
        }
        // ASSERT(false);
        return 0;
    }
};

class VertexBufferLayout{
private:
    std::vector<VertexBufferElement>m_Elements;
    unsigned int m_stride;
public:
    VertexBufferLayout():m_stride(0){};


    void Push(unsigned int count,std::string type){
        if(type=="float"){
            m_Elements.push_back({GL_FLOAT,count,GL_FALSE});
        m_stride+=count*VertexBufferElement::GetSizeofType(GL_FLOAT);
        }
        else if(type=="unsigned int"){
            m_Elements.push_back({GL_UNSIGNED_INT,count,GL_FALSE});
        m_stride+=count*VertexBufferElement::GetSizeofType(GL_UNSIGNED_INT);
        }
        else if(type=="unsigned char"){
             m_Elements.push_back({GL_UNSIGNED_BYTE,count,GL_TRUE});
        m_stride+=count*VertexBufferElement::GetSizeofType(GL_BYTE);
        }
        else{
            printf("unknown type of layout!!\n");
        }
    }



    inline const std::vector<VertexBufferElement>GetElements()const{return m_Elements;}
    inline unsigned int GetStride()const{return m_stride;}
};
