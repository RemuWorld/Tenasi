#pragma once

#include <glad/glad.h>

namespace Tenasi::Shader
{
    struct VAO
    {
        GLuint ID = 0;
        VAO()
        {
            glGenVertexArrays(1, &ID);
        }

        void bind() const noexcept
        {
            glBindVertexArray(ID);
        }

        void unbind() const noexcept
        {
            glBindVertexArray(0);
        }

        void deletion() const noexcept
        {
            glDeleteVertexArrays(1, &ID);
        }
    };
}