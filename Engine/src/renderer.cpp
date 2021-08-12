#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "renderer.h"

#include <iostream>

using namespace Engine;

Renderer::Renderer(){

}

Renderer::~Renderer(){

}

bool Renderer::InitializeGlew(){
    glewExperimental = GL_TRUE;
    glewInit();
    if (glewInit() != GLEW_OK) {
        std::cout << "Error in GLEW INIT" << std::endl;
        std::cout << glewGetErrorString(glewInit()) << std::endl;
        return false;
    }
    return true;
}

void Renderer::SwapBuffers(GLFWwindow* window){
    glfwSwapBuffers(window);
}
