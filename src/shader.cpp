#include "shader.h"

#include <iostream>
#include <stdexcept>


namespace
{
    std::string fileReader(const char* filename)
    {
        std::ifstream in(filename, std::ios::binary);
        if (in)
        {
            std::string contents;
            in.seekg(0, std::ios::end);
            contents.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&contents[0], contents.size());
            in.close();
            return contents;
        }
        throw std::runtime_error(std::string("Failed to open file: ") + filename);
    }
}

namespace Tenasi::Shader
{
    TShader::TShader(const char* vertexFile, const char* fragmentFile)
    {
        std::string vertexCode = fileReader(vertexFile);
        std::string fragmentCode = fileReader(fragmentFile);
        
        const char* contentV = vertexCode.c_str();
        const char* contentF = fragmentCode.c_str();



        GLuint shaderV = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(shaderV, 1, &contentV, nullptr);
        glCompileShader(shaderV);

        GLuint shaderF = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(shaderF, 1, &contentF, nullptr);
        glCompileShader(shaderF);

        ID = glCreateProgram();
        glAttachShader(ID, shaderV);
        glAttachShader(ID, shaderF);
        glLinkProgram(ID);

        glDeleteShader(shaderV);
        glDeleteShader(shaderF);
    }
}