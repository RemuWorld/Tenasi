#pragma once

/* OpenGL standard file includes */
#include <glad/glad.h>

/* C++ Standard file includes */

/* Tenasi file includes*/
#include "shader.h"

/* Extra file includes */
#include <stb_image.h>

namespace Tenasi::Texture
{
    class TTexture
    {
    public:
        GLuint type;
        TTexture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

        void texUnit(Shader::TShader shader, const char* uniform, GLuint unit);
        
        void bind()const noexcept
        {
            glBindTexture(type, ID);
        }

        void unbind() const noexcept
        {
            glBindTexture(type, 0);
        }

        void deletion() const noexcept
        {
            glDeleteTextures(1, &ID);
        }

        GLuint getID() const noexcept { return ID; }
    private:
        GLuint ID;
    };
}