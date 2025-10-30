#pragma once

/* OpenGL standard file includes */
#include <glad/glad.h>
#include <glm/glm.hpp>

/* C++ Standard file includes */

/* Tenasi file includes*/
#include "mesh_vao.h"
#include "mesh_vbo.h"
#include "mesh_ebo.h"

/* Extra file includes */

namespace Tenasi::Mesh
{
    /**
     * @class TMesh
     * @brief Manages meshes / `VAO`, `VBO`, `EBO`
     * @namespace Tenasi::Mesh
     */
    class TMesh
    {
    public:
        TMesh(GLfloat *verts, GLsizeiptr vSize, GLuint *inds, GLsizeiptr iSize, GLsizei count);

        inline void draw() const
        {
            vao.bind();
            glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
        }

    private:
        VAO vao;
        VBO vbo;
        EBO ebo;
        GLsizei indexCount;

        void setupAttributes()
        {
            // Example: 3 floats = position
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
            glEnableVertexAttribArray(0);
        }
    };
}