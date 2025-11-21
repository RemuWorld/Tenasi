#pragma once

#include <glad/glad.h>

namespace Tenasi::Gfx
{
    /**
     * @class TShader
     * @brief Manages shading
     * @namespace Tenasi::Shader
     */
    class Shader
    {
    
    public:
        Shader(const char*, const char*);

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