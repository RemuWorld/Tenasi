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

    void TMesh::setupAttributes()
    {
        vao.bind();
        vao.readFormat(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void *)0);
        vao.readFormat(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void *)(3 * sizeof(float)));
        vao.readFormat(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void *)(6 * sizeof(float)));
        unbind();
    }
}