#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace MGN {
    class SetupGLFW {
        public:
            static void initialize();
            static void configure();
            static void centerWindow(GLFWwindow* window);
            static GLFWwindow* createWindow(unsigned int width, unsigned int height, const char* title);
    };
}