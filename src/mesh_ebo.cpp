#include "mesh_ebo.h"

#include <cerrno>
#include <stdexcept>
#include <string>

namespace Tenasi::Mesh
{
    EBO::EBO(GLuint* indices, GLsizeiptr size)
    {
        glGenBuffers(1, &ID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);

        GLenum err = glGetError();
        if (err != GL_NO_ERROR)
        {
            throw std::runtime_error("EBO creation failed: " + std::to_string(err));
        }
    }
}