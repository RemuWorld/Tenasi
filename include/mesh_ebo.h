#pragma once

#include <glad/glad.h>

namespace Tenasi::Shader
{
    struct EBO
    {
        GLuint ID = 0;
        EBO(GLuint* indices, GLsizeiptr size);

        void bind() const noexcept
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
        }

        void unbind() const noexcept
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        void deletion() const noexcept
        {
            glDeleteBuffers(1, &ID);
        }
    };
}