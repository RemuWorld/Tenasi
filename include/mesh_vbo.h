#pragma once

#include <glad/glad.h>

namespace Tenasi::Shader
{
    struct VBO
    {
        GLuint ID = 0;
        VBO(GLfloat* vertices, GLsizeiptr size);

        void bind() const noexcept
        { 
            glBindBuffer(GL_ARRAY_BUFFER, ID); 
        }

        void unbind() const noexcept
        { 
            glBindBuffer(GL_ARRAY_BUFFER, 0); 
        }

        void deletion() const noexcept
        { 
            glDeleteBuffers(1, &ID); 
        }

        void readFormat(GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
    };
}