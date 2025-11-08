#pragma once

/* OpenGL standard file includes */
#include <glad/glad.h>

/* C++ Standard file includes */
#include <string>
#include <fstream>
#include <sstream>
#include <cerrno>

/* Tenasi file includes*/

/* Extra file includes */

namespace Tenasi::Shader
{
    /**
     * @class TShader
     * @brief Manages shading
     * @namespace Tenasi::Shader
     */
    class TShader
    {
    
    public:
        TShader(const char*, const char*);

        /**
         * @def use()
         * @brief Activates the shader
         * */
        void use() const noexcept 
        { 
            glUseProgram(ID); 
        }

        /**
         * @def unbind()
         * @brief Deactivates the shader
         */
        static inline void unbind() noexcept
        {
            glUseProgram(0);
        }

        /**
         * @def deletion()
         * @brief Deletes the shader
         */
        void deletion() const noexcept
        { 
            glDeleteProgram(ID); 
        }

        GLuint getID() const noexcept { return ID; }
    private:
        GLuint  ID = 0;  
        void compileErrors(unsigned int shader, const char* type);
    };
}