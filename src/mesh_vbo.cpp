#include "mesh_vbo.h"

#include <cerrno>
#include <stdexcept>
#include <string>

namespace Tenasi::Mesh
{
    VBO::VBO(GLfloat* vertices, GLsizeiptr size)
    {
        glGenBuffers(1, &ID);
        glBindBuffer(GL_ARRAY_BUFFER, ID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

        GLenum err = glGetError();
        if (err != GL_NO_ERROR)
        {
            throw std::runtime_error("VBO creation failed: " + std::to_string(err));
        }
    }
}