#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const std::string& path)
:m_RendererID(0),m_FilePath(path),
m_localBuffer(nullptr),m_Width(0),m_Height(0),m_BPP(0)
{
    // stbi_set_flip_vertically_on_load(1);
    //翻转图片，从OpenGL的左下角坐标原点开始
    m_localBuffer=stbi_load(path.c_str(),&m_Width,&m_Height,&m_BPP,4);//4 means RGBA
    if(m_localBuffer == NULL){
        printf("unable to load picture\n");
    }

    glGenTextures(1,&m_RendererID);
    glBindTexture(GL_TEXTURE_2D,m_RendererID);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_BORDER);

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,m_Width,m_Height,0,GL_RGBA,GL_UNSIGNED_BYTE,m_localBuffer);
    //0 表示低级纹理，无复合
    //RGBA8中的8表示每个颜色通道是8bit数
    //第二个0表示无边框
    //RGBA表示现有数据类型
    //数据大小是unsigned byte
    //数据内容是 m_localBuffer
    glBindTexture(GL_TEXTURE_2D,0);

    if(m_localBuffer){
        stbi_image_free(m_localBuffer);
    }

}


Texture::Texture(std::vector<const char*>&files)
:m_RendererID(0),m_files(files),
m_localBuffer(nullptr),m_Width(0),m_Height(0),m_BPP(0)
{
    // stbi_set_flip_vertically_on_load(1);
    glGenTextures(1, &m_RendererID);
    glActiveTexture(GL_TEXTURE0);
    unsigned char* image;
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);
    std::cout<<"Texture 45: filesSize:"<<files.size()<<std::endl;
    for(int i = 0; i < files.size(); i++)
    {
        image = stbi_load(files[i], &m_Width, &m_Height, &m_BPP, 4);
        glTexImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
            GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image
        );
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

Texture::~Texture(){
    glDeleteTextures(1, &m_RendererID);
}


void Texture::Bind(unsigned int slot)const{
    glActiveTexture(GL_TEXTURE0+slot);
    glBindTexture(GL_TEXTURE_2D,m_RendererID);
}

void Texture::skyBind()const{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP,m_RendererID);
}

void Texture::UnBind()const{
glBindTexture(GL_TEXTURE_2D,0);
}
