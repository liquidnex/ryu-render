#include <fstream>
#include "global.h"
#include <sstream>
#include "shader.h"

using namespace std;

Shader::Shader(ShaderType shaderType, std::string shaderTextFilePath)
{
    try
    {
        ifstream is;
        is.open(shaderTextFilePath);
        if (!is)
            return;

        stringstream ss;
        ss << is.rdbuf();
        is.close();

        string shaderStr = ss.str();
        const char* shaderCode = shaderStr.c_str();

        GLenum e = ShaderTypeToGLenum(shaderType);
        if (e == 0)
            return;

        shaderID = glCreateShader(e);
        glShaderSource(shaderID, 1, &shaderCode, NULL);
        glCompileShader(shaderID);
        int fCompSuccess;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &fCompSuccess);
        if (!fCompSuccess)
        {
            char fCompInfo[shaderLogBufferSize];
            glGetShaderInfoLog(shaderID, shaderLogBufferSize, NULL, fCompInfo);
            return;
        }

        isLoaded = true;
    }
    catch (exception e) {}
}

unsigned int Shader::GetShaderID()
{
    return shaderID;
}

void Shader::Delete()
{
    isLoaded = false;
    glDeleteShader(shaderID);
    shaderID = 0;
}

bool Shader::IsVaild()
{
    return isLoaded;
}

GLenum Shader::ShaderTypeToGLenum(ShaderType shaderType)
{
    if (shaderType == VERTEX)
        return GL_VERTEX_SHADER;
    else if (shaderType == FRAGMENT)
        return GL_FRAGMENT_SHADER;
    return 0;
}