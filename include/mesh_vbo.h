#pragma once

#include <glad/glad.h>

namespace Tenasi::Mesh
{
    /**
     * @struct VBO
     * @brief Manages VBO
     * @namespace Tenasi::Mesh
     */
    struct VBO
    {
        GLuint ID = 0;
        VBO() = delete;
        VBO(GLfloat* vertices, GLsizeiptr size);
        
        /* ===== RESOURCE SAFTEY ===== */
        VBO(const VBO &) = delete;
        VBO &operator=(const VBO &) = delete;
        VBO(VBO &&) noexcept = default;
        VBO &operator=(VBO &&) noexcept = default;
        /* =========================== */

        /**
         * @def bind()
         * @brief Binds a VBO
         * */
        inline void bind() const noexcept
        { 
            glBindBuffer(GL_ARRAY_BUFFER, ID); 
        }

        /**
         * @def unbind()
         * @brief Unbinds a VBO
         * */
        static inline void unbind() noexcept
        { 
            glBindBuffer(GL_ARRAY_BUFFER, 0); 
        }

        /**
         * @def deletion()
         * @brief Deletes a VBO
         * */
        inline void deletion() const noexcept
        { 
            glDeleteBuffers(1, &ID); 
        }

        void readFormat(GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
    };
}