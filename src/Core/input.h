#pragma once

#include <glfw/glfw3.h>

namespace Tenasi::Core
{
    enum class Action
    {
        MoveFront,
        MoveBack,
        MoveLeft,
        MoveRight,
        Jump,
        Sprint
    };

    class Input
    {
    public:    
        Input();
        Input(GLFWwindow* window);


        
    private:
        
    };
}