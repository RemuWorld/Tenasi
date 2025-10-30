#pragma once

#include <glad/glad.h>

namespace Tenasi::Mesh
{
    /**
     * @struct VAO
     * @brief Manages VAO
     * @namespace Tenasi::Mesh
     */
    struct VAO
    {
        GLuint ID = 0;
        VAO()
        {
            glGenVertexArrays(1, &ID);
        }

        inline void bind() const noexcept
        {
            glBindVertexArray(ID);
        }

        static inline void unbind() noexcept
        {
            glBindVertexArray(0);
        }

        inline void deletion() const noexcept
        {
            glDeleteVertexArrays(1, &ID);
        }
    };
}