#include "mesh_vbo.h"

namespace Tenasi::Shader
{
    VBO::VBO(GLfloat* vertices, GLsizeiptr size)
    {
        glGenBuffers(1, &ID);
        glBindBuffer(GL_ARRAY_BUFFER, ID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    void VBO::readFormat(GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void *offset)
    {
        glBindBuffer(GL_ARRAY_BUFFER, ID);
        glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
        glEnableVertexAttribArray(layout);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}