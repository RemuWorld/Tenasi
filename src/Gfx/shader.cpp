#include <iostream>
#include <stdexcept>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <cerrno>

#include "shader.h"

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

namespace Tenasi::Gfx
{
    Shader::Shader(const char* vertexFile, const char* fragmentFile)
    {
        std::string vertexCode = fileReader(vertexFile);
        std::string fragmentCode = fileReader(fragmentFile);
        
        const char* contentV = vertexCode.c_str();
        const char* contentF = fragmentCode.c_str();



        GLuint shaderV = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(shaderV, 1, &contentV, nullptr);
        glCompileShader(shaderV);
        compileErrors(shaderV, "VERTEX");

        GLuint shaderF = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(shaderF, 1, &contentF, nullptr);
        glCompileShader(shaderF);
        compileErrors(shaderF, "FRAGMENT");

        ID = glCreateProgram();
        glAttachShader(ID, shaderV);
        glAttachShader(ID, shaderF);
        glLinkProgram(ID);
        compileErrors(ID, "PROGRAM");

        glDeleteShader(shaderV);
        glDeleteShader(shaderF);
    }
    void Shader::compileErrors(unsigned int shader, const char *type)
    {
        GLint hasCompiled = 0;
        char infoLog[1024];

        // compare content safely
        if (std::strcmp(type, "PROGRAM") != 0)
        {
            // shader compilation status
            glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
            if (hasCompiled == GL_FALSE)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "SHADER_COMPILATION_ERR >> " << type << "\n" << infoLog << std::endl;
            }
        }
        else
        {
            // program linking status
            glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
            if (hasCompiled == GL_FALSE)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "SHADER_LINKING_ERR >> " << type << "\n" << infoLog << std::endl;
            }
        }
    }
}