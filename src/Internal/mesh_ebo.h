#pragma once

#include <glad/glad.h>

namespace Tenasi::Internal
{
    /**
     * @struct EBO
     * @brief Manages EBO
     * @namespace Tenasi::Mesh
     */
    struct EBO
    {
        GLuint ID = 0;
        EBO() = delete;
        EBO(GLuint* indices, GLsizeiptr size);

        EBO(const EBO &) = delete;
        EBO &operator=(const EBO &) = delete;
        EBO(EBO &&) noexcept = default;
        EBO &operator=(EBO &&) noexcept = default;

        /**
         * @def bind()
         * @brief Binds a EBO
         * */
        inline void bind() const noexcept
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
        }

        /**
         * @def unbind()
         * @brief Unbinds a EBO
         * */
        static inline void unbind() noexcept
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        /**
         * @def deletion()
         * @brief Deletes a EBO
         * */
        inline void deletion() const noexcept
        {
            glDeleteBuffers(1, &ID);
        }
    };
}