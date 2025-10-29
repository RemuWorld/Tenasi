#include "mesh_vbo.h"

namespace Tenasi::Shader
{
    VBO::VBO(GLfloat* vertices, GLsizeiptr size)
    {
        glGenBuffers(1, &ID);
        glBindBuffer(GL_ARRAY_BUFFER, ID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    void VBO::readFormat(GLuint layout)
    {
        glBindBuffer(GL_ARRAY_BUFFER, ID);
        glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
        glEnableVertexAttribArray(layout);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}