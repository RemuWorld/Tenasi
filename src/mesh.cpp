#include "mesh.h"

namespace Tenasi::Mesh
{
    TMesh::TMesh(GLfloat *verts, GLsizeiptr vSize, GLuint *inds, GLsizeiptr iSize, GLsizei count)
        : vbo(verts, vSize), ebo(inds, iSize), indexCount(count)
    {
        vao.bind();
        vbo.bind();
        ebo.bind();
        // setup attribs
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
        glEnableVertexAttribArray(0);
    }
}