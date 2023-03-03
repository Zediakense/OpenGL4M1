#include"Shader.h"
#include<string>
#include<fstream>
#include<sstream>
#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))
void GLClearError();
bool GLLogCall(const char* function,const char* file,int line);


Shader::Shader(const std::string& filepath)
: m_FilePath(filepath),m_RendererID(0){
    ShaderProgramSource source =ReadShader(filepath);
    m_RendererID=CreateShader(source.VertexSource,source.FragmentSource);
}
Shader::Shader(){
    
};

Shader::~Shader(){
    glDeleteProgram(m_RendererID);
}

unsigned int Shader::CompileShader(unsigned int type,const std::string &source){
    unsigned int id=glCreateShader(type);
    const char* src=source.c_str();
    glShaderSource(id,1,&src,nullptr);
    glCompileShader(id);

    //TODO:Error handling;
    int result;
    glGetShaderiv(id,GL_COMPILE_STATUS,&result);
    if(result==GL_FALSE){
        int length;
        glGetShaderiv(id,GL_INFO_LOG_LENGTH,&length);
        char *message=(char*)alloca(length*sizeof(char));
        glGetShaderInfoLog(id,length,&length,message);
        std::cout<<"failed to compile"<<(type==GL_VERTEX_SHADER?" vertex":" fragment")<<std::endl<<message<<std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

void Shader::Bind()const{
    glUseProgram(m_RendererID);
}
void Shader::UnBind()const{
    glUseProgram(0);
}

void Shader::SetUniform4f(const std::string &name,float v0,float v1,float v2,float v3){
    glUniform4f(GetUniformLocation(name),v0,v1,v2,v3);
}
void Shader::SetUniform3f(const std::string &name,float v0,float v1,float v2){
    glUniform3f(GetUniformLocation(name),v0,v1,v2);
}
void Shader::SetUniform1f(const std::string &name,float value){
    glUniform1f(GetUniformLocation(name),value);
}

void Shader::SetUniform1i(const std::string &name,int value){
    glUniform1i(GetUniformLocation(name),value);
}

void Shader::SetUniformMat4f(const std::string &name,const glm::mat4 &matrix){
 glUniformMatrix4fv(GetUniformLocation(name),1,GL_FALSE,glm::value_ptr(matrix));
}

unsigned int Shader::GetUniformLocation(const std::string &name){
   if(m_UniformLocationCache.find(name)!=m_UniformLocationCache.end()){
       return m_UniformLocationCache[name];
   }
    else{
   int location= glGetUniformLocation(m_RendererID,name.c_str());
   if(location==-1){
       std::cout<<"Warning: uniform "<<name<<" doesn't exists"<<std::endl;
       
    }
    else{
        m_UniformLocationCache[name]=location;
    }
    std::cout<<"get "<<name<<" location = "<<location<<std::endl;
    return location;
    }
}

unsigned int Shader::CreateShader(const std::string & vertexShader,const std::string &fragmentShader){
    unsigned int program=glCreateProgram();
    unsigned int vs=CompileShader(GL_VERTEX_SHADER,vertexShader);
    unsigned int fs=CompileShader(GL_FRAGMENT_SHADER,fragmentShader);

    glAttachShader(program,vs);
    glAttachShader(program,fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}


ShaderProgramSource Shader::ParseShader(const std::string &filepath){
    std::ifstream stream(filepath);
    enum class ShaderType{
        NONE=-1,VERTEX=0,FRAGMENT=1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type=ShaderType::NONE;
    while (getline(stream,line))
    {
        if(line.find("#shader")!=std::string::npos){
            if(line.find("vertex")!=std::string::npos)
                type=ShaderType::VERTEX;
            else if(line.find("fragment")!=std::string::npos)
                type=ShaderType::FRAGMENT;
        }
        else{
            ss[(int)type] <<line<<'\n';
        }
    }
    return {ss[0].str(),ss[1].str()};
}

ShaderProgramSource Shader::ReadShader(const std::string &path){
    bool res = false;
    std::ifstream f;
    f.open(path.c_str());
    if(!f.is_open()){
        printf("open %s failed!\n",path.c_str());
//        return res;
    }
    std::string buf;
    std::string shader[2];
    int flag = 0;
    while(getline(f,buf)){
        if(buf == "vertexShader"){
            continue;
        }
        if(buf == "fragmentShader"){
            flag = 1;
            continue;
        }
        shader[flag] += buf + "\n";
        
    }
    printf("read vs---------------\n%sfs---------------\n%s\n",shader[0].c_str(),shader[1].c_str());
    f.close();
    res = true;
//    return res;
    return {shader[0],shader[1]};
}
