#include <iostream>
#include <cmath>
#include "header.h"
#include "shader.h"
#include "mesh_vao.h"
#include "mesh_vbo.h"
#include "mesh_ebo.h"


int main()
{
    //Init GL
    glfwInit();
    // Using Version 3.3 of OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Core Profile we use (only modern functions)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // vertex data
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, //Bottom left
        0.5f, -0.5f, 0.0f, // Bottom right
        0.5f, 0.5f, 0.0f, // Top right
        -0.5f, 0.5f, 0.0f // Top left
    };

    GLuint indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    // Creates a GLFWwindow object size of 800 x 800 px, named "Hello"
    GLFWwindow *window = glfwCreateWindow(800, 800, "Hello", nullptr, nullptr);
    // Error check for if nothing gets created
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Make var window the one getting managed
    glfwMakeContextCurrent(window);

    gladLoadGL();
    // viewport at 800 x 800 px (size of the painting) for dynamics need a better version
    glViewport(0, 0, 800, 800);
    glfwSwapInterval(1);
    glEnable(GL_BLEND);

    // shader files are located in the top-level "shaders/" folder (copied by CMake)
    Tenasi::Shader::TShader shaderProgram("shaders/distk.vert", "shaders/distk.frag");

    Tenasi::Shader::VAO VAO;

    // Bind the VAO before creating/binding VBO and EBO so
    // vertex attribute pointers and the element buffer are stored in the VAO.
    VAO.bind();

    Tenasi::Shader::VBO VBO(vertices, sizeof(vertices));
    Tenasi::Shader::EBO EBO(indices, sizeof(indices));

    VBO.readFormat(0);

    // Unbind VAO (optional). It's fine to unbind VBO; do not unbind the EBO while
    // the VAO is still bound if you want the EBO to remain associated with the VAO.
    VAO.unbind();
    VBO.unbind();
    EBO.unbind();



    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);

    constexpr GLuint res = (sizeof(indices) / sizeof(unsigned int));

        while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.use();
        VAO.bind();
        glDrawElements(GL_TRIANGLES, res,  GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);


        glfwPollEvents();
    }

    VAO.deletion();
    VBO.deletion();
    EBO.deletion();
    shaderProgram.deletion();
    
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}