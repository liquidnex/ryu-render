#ifndef __SHADER_PROGRAM_H__
#define __SHADER_PROGRAM_H__

#include <array>
#include <mutex>
#include "shader.h"
#include <vector>

class ShaderProgram
{
public:
    ShaderProgram(std::vector<Shader> shaders);

    template <typename... Args>
    bool SetUniform(std::string uniformName, Args... args);
    bool Enable();
private:
    template <typename... Args>
    bool _SetUniformToBool(const std::string& uniformName, std::vector<bool>& bools, bool value, Args ...args);
    bool _SetUniformToBool(const std::string& uniformName, std::vector<bool>& bools);
    template <typename... Args>
    bool _SetUniformToInt(const std::string& uniformName, std::vector<int>& ints, int value, Args ...args);
    bool _SetUniformToInt(const std::string& uniformName, std::vector<int>& ints);
    template <typename... Args>
    bool _SetUniformToUnsignedInt(const std::string& uniformName, std::vector<unsigned int>& unsignedInts, unsigned int value, Args ...args);
    bool _SetUniformToUnsignedInt(const std::string& uniformName, std::vector<unsigned int>& unsignedInts);
    template <typename... Args>
    bool _SetUniformToFloat(const std::string& uniformName, std::vector<float>& floats, float value, Args ...args);
    bool _SetUniformToFloat(const std::string& uniformName, std::vector<float>& floats);
    template <typename... Args>
    bool _SetUniformToDouble(const std::string& uniformName, std::vector<double>& doubles, double value, Args ...args);
    bool _SetUniformToDouble(const std::string& uniformName, std::vector<double>& doubles);
    template <typename... Args>
    bool _SetUniformToBoolArrays(const std::string& uniformName, std::vector<std::vector<bool>>& boolArrays, std::vector<bool> value, Args ...args);
    bool _SetUniformToBoolArrays(const std::string& uniformName, std::vector<std::vector<bool>>& boolArrays);
    template <typename... Args>
    bool _SetUniformToIntArrays(const std::string& uniformName, std::vector<std::vector<int>>& intArrays, std::vector<int> value, Args ...args);
    bool _SetUniformToIntArrays(const std::string& uniformName, std::vector<std::vector<int>>& intArrays);
    template <typename... Args>
    bool _SetUniformToUnsignedIntArrays(const std::string& uniformName, std::vector<std::vector<unsigned int>>& unsigendIntArrays, std::vector<unsigned int> value, Args ...args);
    bool _SetUniformToUnsignedIntArrays(const std::string& uniformName, std::vector<std::vector<unsigned int>>& unsigendIntArrays);
    template <typename... Args>
    bool _SetUniformToFloatArrays(const std::string& uniformName, std::vector<std::vector<float>>& floatArrays, std::vector<float> value, Args ...args);
    bool _SetUniformToFloatArrays(const std::string& uniformName, std::vector<std::vector<float>>& floatArrays);
    template <typename... Args>
    bool _SetUniformToDoubleArrays(const std::string& uniformName, std::vector<std::vector<double>>& doubleArrays, std::vector<double> value, Args ...args);
    bool _SetUniformToDoubleArrays(const std::string& uniformName, std::vector<std::vector<double>>& doubleArrays);
    
    unsigned int shaderProgramID;
    static constexpr unsigned int shaderLogBufferSize = 1024;
};

#endif