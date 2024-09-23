#define GLFW_INCLUDE_NONE

#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <fstream>
#include <sstream>
#include <string>

int main() {
    
    std::ifstream file;
    std::string line;

    file.open("./shaders/vertex.txt");
    while(std::getline(file, line)) {
        std::cout << line << std::endl;
    }

    /// Create a window pointer
    GLFWwindow *window;

    /// Initialize the window
    if(!glfwInit()) {
        std::cout << "GLFW could'nt start" << std::endl;
        return -1;
    }


    // Create the window
    window = glfwCreateWindow(640, 480, "My Window", nullptr, nullptr);

    // Set that window as the current context window
    glfwMakeContextCurrent(window);

    // Tell glad to run our system and get all the function definitions
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        return -1;
    }

    // Set color for when we clear the screen
    glClearColor(0.25f, 0.5f, 0.75f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        
        // So events dont pile up (inputs)
        glfwPollEvents();

        // Actually clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap buffers
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
