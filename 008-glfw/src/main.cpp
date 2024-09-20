// Third-party
#include "include/GLFW/glfw3.h"

int main() {
    if (!glfwInit())
    {
        // Init failed
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "Test title", NULL, NULL);
    if (!window) {
        // Win failed
    }
    glfwSwapInterval(1);

    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}
