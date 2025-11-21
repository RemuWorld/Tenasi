#include "camera.h"

namespace Tenasi::Gfx
{
    #define _velocity (float)(Camera::speed_init + Camera::acceleration * Camera::time)

    Camera::Camera(int width, int height, glm::vec3 position)
    {
        Camera::width = width;
        Camera::height = height;
        Camera::position = position;
        time = glfwGetTime();     
    }

    void Camera::Matrix(float FOVdeg, float nearP, float farP, Shader &shader, const char *uniform)
    {
        view = glm::lookAt(position, position + orientation, up);
        projection = glm::perspective(glm::radians(FOVdeg), (float)(width / height), nearP, farP);

        glUniformMatrix4fv(glGetUniformLocation(shader.getID(), uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
    }

    void  Camera::Inputs(GLFWwindow* window)
    {
        if(glfwGetKey(window, GLFW_KEY_W) ==  GLFW_PRESS)
        {
            position += _velocity * orientation;
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            position += _velocity * -glm::normalize(glm::cross(orientation, up));
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            position += _velocity * -orientation;
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            position += _velocity * glm::normalize(glm::cross(orientation, up));
        }

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            position += _velocity * up;
        }

        if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) ==  GLFW_PRESS)
        {
            position += _velocity * -up;
        }
        
        if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) ==  GLFW_PRESS)
        {
            speed_max = 0.3f;
        }
        else if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) ==  GLFW_RELEASE)
        {
            speed_max = 0.1f;
        }
    }
}