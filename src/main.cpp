#include <iostream>
#include "Tenasi.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

constexpr unsigned int width = 800;
constexpr unsigned int height = 800;

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

    Tenasi::Gfx::Shader shaderProgram("resource/shaders/distk.vert", "resource/shaders/distk.frag");
    Tenasi::Gfx::Mesh obj(vertices, sizeof(vertices), indices, sizeof(indices), (sizeof(indices) / sizeof(unsigned int)));
    Tenasi::Gfx::Camera cam(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

    // The GLFWwindow* window gets a reference of TCamera cam.
    glfwSetWindowUserPointer(window, &cam);
    
    /* Set a frameBufferSizeCallback. In this function (GLFWwindow*, int width, int height) is the variable that get's fitted.              \
       we use a lambda func to set that width and height part. The frameBuffSizeCallback func needs to know what height and int it is       \
       so we give it a GLFWwindow* to help find what the width and height is. The first variable is the one we are setting callback.        \
       After this function setted when we change the viewport then it will be automatically changed as the OpenGL detects what have changed.\
                                                                                                                                            \
                                     p (what to GLFWwindow is going to be changed)                                                          \
                                     |          p (from what GLFWwindow we get the variables)                                               \
                                     V          V                                                                                           */  
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* win, int w, int h)
    {
        // set viewport
        glViewport(0, 0, w, h);
        // def local camera ptr var
        auto camPtr = static_cast<Tenasi::Gfx::Camera*>(glfwGetWindowUserPointer(win));
        // Initiate the updateProjection function.
        if (camPtr) camPtr->updateProjection(w, h);
    });

    glfwSwapInterval(1);
    // To make planes not be mixed on the screen
    glEnable(GL_BLEND);

    // unbind for saftey
    obj.unbind();

    // uniform ID location getter
    GLuint uniID= glGetUniformLocation(shaderProgram.getID(), "scale");
    
    // The texture we are going to use. In my case it's VScode logo.
    Tenasi::Gfx::Texture VScode("resource/textures/matrix_A.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    // Make texture present
    VScode.texUnit(shaderProgram, "tex", 0);

    // Set clear color
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    // Clear type
    glClear(GL_COLOR_BUFFER_BIT);
    // swap buffer to make cleared buffer present.
    glfwSwapBuffers(window);

    // rotation angle and start time set.
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

        cam.Inputs(window);
        cam.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

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