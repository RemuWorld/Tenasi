#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Internal/mesh_vao.h"
#include "Internal/mesh_vbo.h"
#include "Internal/mesh_ebo.h"

namespace Tenasi::Gfx
{
    /**
     * @class TMesh
     * @brief Manages meshes / `VAO`, `VBO`, `EBO`
     * @namespace Tenasi::Mesh
     */
    class Mesh
    {
    public:
        Mesh(GLfloat *verts, GLsizeiptr vSize, GLuint *inds, GLsizeiptr iSize, GLsizei count);

        inline void draw() const
        {
            vao.bind();
            glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
        }

        inline void unbind() const
        {
            vao.unbind();
            vbo.unbind();
            ebo.unbind();
        }

        inline void deletion() const
        {
            vao.deletion();
            vbo.deletion();
            ebo.deletion();
        }

    private:
        Internal::VAO vao;
        Internal::VBO vbo;
        Internal::EBO ebo;
        GLsizei indexCount;

        void setupAttributes();
    };
}