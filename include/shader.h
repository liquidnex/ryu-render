#ifndef __SHADER_H__
#define __SHADER_H__

#include "glenv.h"
#include <string>

enum ShaderType
{
    VERTEX,
    FRAGMENT
};

class Shader
{
public:
    Shader(ShaderType shaderType, std::string shaderTextFilePath);
    unsigned int GetShaderID();
    void Delete();
    bool IsVaild();
private:
    GLenum ShaderTypeToGLenum(ShaderType shaderType);
    unsigned int shaderID = 0;
    bool isLoaded = false;
    static constexpr unsigned int shaderLogBufferSize = 1024;
};

#endif