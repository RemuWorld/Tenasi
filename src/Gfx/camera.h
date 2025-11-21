#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"

namespace Tenasi::Gfx
{
    class Camera
    {
    public:
        glm::vec3 position;
        glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

        int width;
        int height;

        float speed_init = 0.0f;
        float acceleration = 0.05f;
        double time;

        float sensitivity = 100.0f;

        Camera(int width, int height, glm::vec3 position);

        void Matrix(float FOVdeg, float nearP, float farP, Shader& shader, const char* uniform);
        void Inputs(GLFWwindow* window);
        void updateProjection(int width, int height)
        {
            float aspect = (float)width / height; // Current aspect ratio
            projection = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);
        }

        glm::mat4 getProjection() const { return projection; }

    private:
        glm::mat4 projection = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);

        float speed_max = 0.1f;
    };
}