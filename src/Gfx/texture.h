#pragma once

#include <glad/glad.h>

#include "shader.h"

namespace Tenasi::Gfx
{
    class Texture
    {
    public:
        GLuint type;
        Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

        void texUnit(Shader shader, const char* uniform, GLuint unit);
        
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