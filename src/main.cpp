#include <iostream>
#include <cmath>
#include "header.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

volatile const unsigned int width = 800;
volatile const unsigned int height = 800;

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
    {  //------Coord------//  //-------Color-------//     //--TexCoord--//
        -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,        0.0f, 0.0f,
        -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,        5.0f, 0.0f,
         0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,        0.0f, 0.0f,
         0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,        5.0f, 0.0f,
         0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,        2.5f, 5.0f   
    };

    GLuint indices[] = {
        0, 1, 2,
        0, 2, 3,
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4
    };

    // Creates a GLFWwindow object size of 800 x 800 px, named "Hello"
    GLFWwindow *window = glfwCreateWindow(width, height, "Hello", nullptr, nullptr);
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
    glViewport(0, 0, width, height);
    glfwSwapInterval(1);
    glEnable(GL_BLEND);

    Tenasi::Shader::TShader shaderProgram("resource/shaders/distk.vert", "resource/shaders/distk.frag");
    Tenasi::Mesh::TMesh obj(vertices, sizeof(vertices), indices, sizeof(indices), (sizeof(indices) / sizeof(unsigned int)));

    obj.unbind();


    GLuint uniID= glGetUniformLocation(shaderProgram.getID(), "scale");
    
    Tenasi::Texture::TTexture VScode("resource/textures/VScode.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    VScode.texUnit(shaderProgram, "tex", 0);


    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);

    float rotation = 0.0f;
    double prevTime = glfwGetTime();

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderProgram.use();

        double curTime = glfwGetTime();
        if(curTime - prevTime >= 1/60)
        {
            rotation += 0.5f;
            prevTime = curTime;
        }

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 proj = glm::mat4(1.0f);

        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
        proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

        int modelLoc = glGetUniformLocation(shaderProgram.getID(), "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        int viewLoc = glGetUniformLocation(shaderProgram.getID(), "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        int projLoc = glGetUniformLocation(shaderProgram.getID(), "proj");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

        glUniform1f(uniID, 0.5f);

        VScode.bind();
        obj.draw();

        glfwSwapBuffers(window);


        glfwPollEvents();
    }

    obj.deletion();
    shaderProgram.deletion();
    VScode.deletion();
    
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}