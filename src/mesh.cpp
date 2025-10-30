#include "mesh.h"

namespace Tenasi::Mesh
{
    TMesh::TMesh(GLfloat *verts, GLsizeiptr vSize, GLuint *inds, GLsizeiptr iSize, GLsizei count)
        : vbo(verts, vSize), ebo(inds, iSize), indexCount(count)
    {
        vao.bind();
        vbo.bind();
        ebo.bind();
        setupAttributes();
    }
}