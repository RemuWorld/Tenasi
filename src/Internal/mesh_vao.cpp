#include <cerrno>
#include <stdexcept>
#include <string>

#include "mesh_vao.h"

namespace Tenasi::Internal
{
    void VAO::readFormat(const VBO &vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void *offset)
    {
        vbo.bind();
        glBindBuffer(GL_ARRAY_BUFFER, vbo.ID);
        glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
        glEnableVertexAttribArray(layout);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        vbo.unbind();
    }
}