#include <algorithm>
#include "glenv.h"
#include "global.h"
#include "shader_program.h"

using namespace std;

ShaderProgram::ShaderProgram(vector<Shader> shaders)
{
    shaderProgramID = glCreateProgram();

    for (Shader s : shaders)
    {
        if (!s.IsVaild())
            continue;

        glAttachShader(shaderProgramID, s.GetShaderID());
    }

    glLinkProgram(shaderProgramID);
    for (Shader s : shaders)
    {
        if (!s.IsVaild())
            continue;

        s.Delete();
    }

    int spLinkSuccess;
    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &spLinkSuccess);
    if (!spLinkSuccess)
    {
        char spCompInfo[shaderLogBufferSize];
        glGetProgramInfoLog(shaderProgramID, shaderLogBufferSize, NULL, spCompInfo);
        return;
    }
}

template <typename... Args>
bool ShaderProgram::SetUniform(string uniformName, Args... args)
{
    if constexpr (conjunction_v<is_same<Args, bool>...>) {
        vector<bool> bools;
        return _SetUniformToBool(uniformName, bools, args...);
    }
    else if constexpr (std::conjunction_v<std::is_same<Args, int>...>) {
        vector<int> ints;
        return _SetUniformToInt(uniformName, ints, args...);
    }
    else if constexpr (std::conjunction_v<std::is_same<Args, unsigned int>...>) {
        vector<unsigned int> unsignedInts;
        return _SetUniformToUnsignedInt(uniformName, unsignedInts, args...);
    }
    else if constexpr (std::conjunction_v<std::is_same<Args, float>...>) {
        vector<float> floats;
        return _SetUniformToFloat(uniformName, floats, args...);
    }
    else if constexpr (std::conjunction_v<std::is_same<Args, double>...>) {
        vector<double> doubles;
        return _SetUniformToDouble(uniformName, doubles, args...);
    }
    else if constexpr (std::conjunction_v<std::is_same<Args, vector<bool>>...>) {
        vector<vector<bool>> boolArrays;
        return _SetUniformToBoolArrays(uniformName, boolArrays, args...);
    }
    else if constexpr (std::conjunction_v<std::is_same<Args, vector<int>>...>) {
        vector<vector<int>> intArrays;
        return _SetUniformToIntArrays(uniformName, intArrays, args...);
    }
    else if constexpr (std::conjunction_v<std::is_same<Args, vector<unsigned int>>...>) {
        vector<vector<unsigned int>> unsignedIntArrays;
        return _SetUniformToUnsignedIntArrays(uniformName, unsignedIntArrays, args...);
    }
    else if constexpr (std::conjunction_v<std::is_same<Args, vector<float>>...>) {
        vector<vector<float>> floatArrays;
        return _SetUniformToFloatArrays(uniformName, floatArrays, args...);
    }
    else if constexpr (std::conjunction_v<std::is_same<Args, vector<double>>...>) {
        vector<vector<double>> doubleArrays;
        return _SetUniformToDoubleArrays(uniformName, doubleArrays, args...);
    }
    return false;
}

bool ShaderProgram::Enable()
{
    glUseProgram(shaderProgramID);
    return true;
}

template<typename ...Args>
bool ShaderProgram::_SetUniformToBool(const string& uniformName, vector<bool>& bools, bool value, Args ...args)
{
    bools.push_back(value);
    return _SetUniformToBool(uniformName, bools, args...);
}

bool ShaderProgram::_SetUniformToBool(const string& uniformName, vector<bool>& bools)
{
    int vertexLocation = glGetUniformLocation(shaderProgramID, uniformName.c_str());
    if (vertexLocation < 0)
        return false;

    if (bools.size() == 1) {
        glUniform1i(vertexLocation, bools[0]);
    }
    else if (bools.size() == 2) {
        glUniform2i(vertexLocation, bools[0], bools[1]);
    }
    else if (bools.size() == 3) {
        glUniform3i(vertexLocation, bools[0], bools[1], bools[2]);
    }
    else if (bools.size() >= 4) {
        glUniform4i(vertexLocation, bools[0], bools[1], bools[2], bools[3]);
    }

    return true;
}

template<typename ...Args>
bool ShaderProgram::_SetUniformToInt(const string& uniformName, vector<int>& ints, int value, Args ...args)
{
    ints.push_back(value);
    return _SetUniformToInt(uniformName, ints, args...);
}

bool ShaderProgram::_SetUniformToInt(const string& uniformName, vector<int>& ints)
{
    int vertexLocation = glGetUniformLocation(shaderProgramID, uniformName.c_str());
    if (vertexLocation < 0)
        return false;

    if (ints.size() == 1)
    {
        glUniform1i(vertexLocation, ints[0]);
    }
    else if (ints.size() == 2)
    {
        glUniform2i(vertexLocation, ints[0], ints[1]);
    }
    else if (ints.size() == 3)
    {
        glUniform3i(vertexLocation, ints[0], ints[1], ints[2]);
    }
    else if (ints.size() >= 4)
    {
        glUniform4i(vertexLocation, ints[0], ints[1], ints[2], ints[3]);
    }

    return true;
}

template<typename ...Args>
bool ShaderProgram::_SetUniformToUnsignedInt(const string& uniformName, vector<unsigned int>& unsignedInts, unsigned int value, Args ...args)
{
    unsignedInts.push_back(value);
    return _SetUniformToUnsignedInt(uniformName, unsignedInts, args...);
}

bool ShaderProgram::_SetUniformToUnsignedInt(const string& uniformName, vector<unsigned int>& unsignedInts)
{
    int vertexLocation = glGetUniformLocation(shaderProgramID, uniformName.c_str());
    if (vertexLocation < 0)
        return false;

    if (unsignedInts.size() == 1)
    {
        glUniform1ui(vertexLocation, unsignedInts[0]);
    }
    else if (unsignedInts.size() == 2)
    {
        glUniform2ui(vertexLocation, unsignedInts[0], unsignedInts[1]);
    }
    else if (unsignedInts.size() == 3)
    {
        glUniform3ui(vertexLocation, unsignedInts[0], unsignedInts[1], unsignedInts[2]);
    }
    else if (unsignedInts.size() >= 4)
    {
        glUniform4ui(vertexLocation, unsignedInts[0], unsignedInts[1], unsignedInts[2], unsignedInts[3]);
    }

    return true;
}

template<typename ...Args>
bool ShaderProgram::_SetUniformToFloat(const string& uniformName, vector<float>& floats, float value, Args ...args)
{
    floats.push_back(value);
    return _SetUniformToFloat(uniformName, floats, args...);
}

bool ShaderProgram::_SetUniformToFloat(const string& uniformName, vector<float>& floats)
{
    int vertexLocation = glGetUniformLocation(shaderProgramID, uniformName.c_str());
    if (vertexLocation < 0)
        return false;

    if (floats.size() == 1)
    {
        glUniform1f(vertexLocation, floats[0]);
    }
    else if (floats.size() == 2)
    {
        glUniform2f(vertexLocation, floats[0], floats[1]);
    }
    else if (floats.size() == 3)
    {
        glUniform3f(vertexLocation, floats[0], floats[1], floats[2]);
    }
    else if (floats.size() >= 4)
    {
        glUniform4f(vertexLocation, floats[0], floats[1], floats[2], floats[3]);
    }

    return true;
}

template<typename ...Args>
bool ShaderProgram::_SetUniformToDouble(const string& uniformName, vector<double>& doubles, double value, Args ...args)
{
    doubles.push_back(value);
    return _SetUniformToDouble(uniformName, doubles, args...);
}

bool ShaderProgram::_SetUniformToDouble(const string& uniformName, vector<double>& doubles)
{
    int vertexLocation = glGetUniformLocation(shaderProgramID, uniformName.c_str());
    if (vertexLocation < 0)
        return false;

    if (doubles.size() == 1)
    {
        glUniform1d(vertexLocation, doubles[0]);
    }
    else if (doubles.size() == 2)
    {
        glUniform2d(vertexLocation, doubles[0], doubles[1]);
    }
    else if (doubles.size() == 3)
    {
        glUniform3d(vertexLocation, doubles[0], doubles[1], doubles[2]);
    }
    else if (doubles.size() >= 4)
    {
        glUniform4d(vertexLocation, doubles[0], doubles[1], doubles[2], doubles[3]);
    }

    return true;
}

template <typename... Args>
bool ShaderProgram::_SetUniformToBoolArrays(const string& uniformName, vector<vector<bool>>& boolArrays, vector<bool> value, Args ...args)
{
    boolArrays.push_back(value);
    return _SetUniformToBoolArrays(uniformName, boolArrays, args...);
}

bool ShaderProgram::_SetUniformToBoolArrays(const string& uniformName, vector<vector<bool>>& boolArrays)
{
    int vertexLocation = glGetUniformLocation(shaderProgramID, uniformName.c_str());
    if (vertexLocation < 0)
        return false;

    int outerSize = boolArrays.size();
    if (outerSize == 0)
        return false;
    int innerSize = boolArrays[0].size();
    if (innerSize == 0)
        return false;
    innerSize = innerSize > 4 ? 4 : innerSize;

    int* data = new int[outerSize * innerSize];
    for (int i = 0; i < outerSize; ++i)
    {
        for (int j = 0; j < innerSize; ++j)
        {
            data[i * innerSize + j] = boolArrays[i][j];
        }
    }

    if(innerSize == 1)
        glUniform1iv(vertexLocation, outerSize * innerSize, data);
    else if (innerSize == 2)
        glUniform2iv(vertexLocation, outerSize * innerSize, data);
    else if (innerSize == 3)
        glUniform3iv(vertexLocation, outerSize * innerSize, data);
    else if (innerSize == 4)
        glUniform4iv(vertexLocation, outerSize * innerSize, data);
    delete[] data;

    return true;
}

template <typename... Args>
bool ShaderProgram::_SetUniformToIntArrays(const string& uniformName, vector<vector<int>>& intArrays, vector<int> value, Args ...args)
{
    intArrays.push_back(value);
    return _SetUniformToIntArrays(uniformName, intArrays, args...);
}

bool ShaderProgram::_SetUniformToIntArrays(const string& uniformName, vector<vector<int>>& intArrays)
{
    int vertexLocation = glGetUniformLocation(shaderProgramID, uniformName.c_str());
    if (vertexLocation < 0)
        return false;

    int outerSize = intArrays.size();
    if (outerSize == 0)
        return false;
    int innerSize = intArrays[0].size();
    if (innerSize == 0)
        return false;
    innerSize = innerSize > 4 ? 4 : innerSize;

    int* data = new int[outerSize * innerSize];
    for (int i = 0; i < outerSize; ++i)
    {
        for (int j = 0; j < innerSize; ++j)
        {
            data[i * innerSize + j] = intArrays[i][j];
        }
    }

    if (innerSize == 1)
        glUniform1iv(vertexLocation, outerSize * innerSize, data);
    else if (innerSize == 2)
        glUniform2iv(vertexLocation, outerSize * innerSize, data);
    else if (innerSize == 3)
        glUniform3iv(vertexLocation, outerSize * innerSize, data);
    else if (innerSize == 4)
        glUniform4iv(vertexLocation, outerSize * innerSize, data);
    delete[] data;

    return true;
}

template <typename... Args>
bool ShaderProgram::_SetUniformToUnsignedIntArrays(const string& uniformName, vector<vector<unsigned int>>& unsignedIntArrays, vector<unsigned int> value, Args ...args)
{
    unsignedIntArrays.push_back(value);
    return _SetUniformToUnsignedIntArrays(uniformName, unsignedIntArrays, args...);
}

bool ShaderProgram::_SetUniformToUnsignedIntArrays(const string& uniformName, vector<vector<unsigned int>>& unsignedIntArrays)
{
    int vertexLocation = glGetUniformLocation(shaderProgramID, uniformName.c_str());
    if (vertexLocation < 0)
        return false;

    int outerSize = unsignedIntArrays.size();
    if (outerSize == 0)
        return false;
    int innerSize = unsignedIntArrays[0].size();
    if (innerSize == 0)
        return false;
    innerSize = innerSize > 4 ? 4 : innerSize;

    unsigned int* data = new unsigned int[outerSize * innerSize];
    for (int i = 0; i < outerSize; ++i)
    {
        for (int j = 0; j < innerSize; ++j)
        {
            data[i * innerSize + j] = unsignedIntArrays[i][j];
        }
    }

    if (innerSize == 1)
        glUniform1uiv(vertexLocation, outerSize * innerSize, data);
    else if (innerSize == 2)
        glUniform2uiv(vertexLocation, outerSize * innerSize, data);
    else if (innerSize == 3)
        glUniform3uiv(vertexLocation, outerSize * innerSize, data);
    else if (innerSize == 4)
        glUniform4uiv(vertexLocation, outerSize * innerSize, data);
    delete[] data;

    return true;
}

template <typename... Args>
bool ShaderProgram::_SetUniformToFloatArrays(const string& uniformName, vector<vector<float>>& floatArrays, vector<float> value, Args ...args)
{
    floatArrays.push_back(value);
    return _SetUniformToFloatArrays(uniformName, floatArrays, args...);
}

bool ShaderProgram::_SetUniformToFloatArrays(const string& uniformName, vector<vector<float>>& floatArrays)
{
    int vertexLocation = glGetUniformLocation(shaderProgramID, uniformName.c_str());
    if (vertexLocation < 0)
        return false;

    int outerSize = floatArrays.size();
    if (outerSize == 0)
        return false;
    int innerSize = floatArrays[0].size();
    if (innerSize == 0)
        return false;
    innerSize = innerSize > 4 ? 4 : innerSize;

    float* data = new float[outerSize * innerSize];
    for (int i = 0; i < outerSize; ++i)
    {
        for (int j = 0; j < innerSize; ++j)
        {
            data[i * innerSize + j] = floatArrays[i][j];
        }
    }

    if (innerSize == 1)
        glUniform1fv(vertexLocation, outerSize * innerSize, data);
    else if (innerSize == 2)
        glUniform2fv(vertexLocation, outerSize * innerSize, data);
    else if (innerSize == 3)
        glUniform3fv(vertexLocation, outerSize * innerSize, data);
    else if (innerSize == 4)
        glUniform4fv(vertexLocation, outerSize * innerSize, data);
    delete[] data;

    return true;
}

template <typename... Args>
bool ShaderProgram::_SetUniformToDoubleArrays(const string& uniformName, vector<vector<double>>& doubleArrays, vector<double> value, Args ...args)
{
    doubleArrays.push_back(value);
    return _SetUniformToDoubleArrays(uniformName, doubleArrays, args...);
}

bool ShaderProgram::_SetUniformToDoubleArrays(const string& uniformName, vector<vector<double>>& doubleArrays)
{
    int vertexLocation = glGetUniformLocation(shaderProgramID, uniformName.c_str());
    if (vertexLocation < 0)
        return false;

    int outerSize = doubleArrays.size();
    if (outerSize == 0)
        return false;
    int innerSize = doubleArrays[0].size();
    if (innerSize == 0)
        return false;
    innerSize = innerSize > 4 ? 4 : innerSize;

    double* data = new double[outerSize * innerSize];
    for (int i = 0; i < outerSize; ++i)
    {
        for (int j = 0; j < innerSize; ++j)
        {
            data[i * innerSize + j] = doubleArrays[i][j];
        }
    }

    if (innerSize == 1)
        glUniform1dv(vertexLocation, outerSize * innerSize, data);
    else if (innerSize == 2)
        glUniform2dv(vertexLocation, outerSize * innerSize, data);
    else if (innerSize == 3)
        glUniform3dv(vertexLocation, outerSize * innerSize, data);
    else if (innerSize == 4)
        glUniform4dv(vertexLocation, outerSize * innerSize, data);
    delete[] data;

    return true;
}