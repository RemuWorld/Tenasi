#include <iostream>
#include <cmath>
#include "header.h"
#include "shader.h"
#include "mesh.h"
#include "mesh_vao.h"
#include "mesh_vbo.h"
#include "mesh_ebo.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

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
    GLfloat vertices[] = 
    {  //------Coord------//  //-----Color------//
        -0.6f, -0.5f, 0.0f,    0.2f, 0.3f, 0.4f,    0.0f, 0.0f,              // Bottom left
        -0.6f,  0.5f, 0.0f,    0.3f, 0.4f, 0.5f,    0.0f, 1.0f,              // Top left
         0.6f,  0.5f, 0.0f,    0.4f, 0.5f, 0.6f,    1.0f, 1.0f,              // Top right
         0.6f, -0.5f, 0.0f,    0.5f, 0.6f, 0.7f,    1.0f, 0.0f               // Bottom right
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

    Tenasi::Shader::TShader shaderProgram("resource/shaders/distk.vert", "resource/shaders/distk.frag");
    int widthImg, heightImg, numColCh;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load("resource/textures/VScode.png", &widthImg, &heightImg, &numColCh, 0);
    if (!bytes)
    {
        fprintf(stderr, "stbi_load failed\n"); /* bail */
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);

    GLuint tex0Uni = glGetUniformLocation(shaderProgram.getID(), "tex0");
    shaderProgram.use();
    glUniform1i(tex0Uni, 0);



    
    constexpr GLuint res = (sizeof(indices) / sizeof(unsigned int));
    Tenasi::Mesh::TMesh obj(vertices, sizeof(vertices), indices, sizeof(indices), res);

    obj.unbind();


    GLuint uniID= glGetUniformLocation(shaderProgram.getID(), "scale");



    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);

    

        while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.use();
        glUniform1f(uniID, 0.5f);
        glBindTexture(GL_TEXTURE_2D, texture);
        obj.draw();
        glfwSwapBuffers(window);


        glfwPollEvents();
    }

    obj.deletion();
    shaderProgram.deletion();
    
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}