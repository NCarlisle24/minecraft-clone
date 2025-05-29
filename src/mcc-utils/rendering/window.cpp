#include <mcc-utils/rendering/window.hpp>

#pragma GCC diagnostic ignored "-Wunused-parameter"
static void defaultFrameBufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

Window::Window(const int &width, const int &height, const char* title) {
    glfwWindow = NULL;
    gladIsInitialized = false;

    glfwWindow = glfwCreateWindow(width, height, title, NULL, NULL);

    if (glfwWindow == NULL) {
        std::cerr << "Error: Failed to create GLFWwindow." << std::endl;
        return;
    }

    glfwSetFramebufferSizeCallback(glfwWindow, defaultFrameBufferSizeCallback);

    glfwMakeContextCurrent(glfwWindow);

    initializeGLAD();
}

Window::~Window() {
    if (glfwWindow != NULL) {
        glfwDestroyWindow(glfwWindow);
    }
}

int Window::setAsContext() {
    if (glfwWindow == NULL) {
        std::cerr << "Error: Window that doesn't exist cannot be set as context." << std::endl;
        return ERROR;
    }

    glfwMakeContextCurrent(glfwWindow);

    return SUCCESS;
}

int Window::initializeGLAD() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Error: GLAD failed to initialize." << std::endl;
        return ERROR;
    }

    gladIsInitialized = true;

    return SUCCESS;
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(glfwWindow);
}

void Window::swapBuffers() {
    glfwSwapBuffers(glfwWindow);
}

void Window::setUserPointer(void* const &pointer) {
    glfwSetWindowUserPointer(glfwWindow, pointer);
}
void* Window::getUserPointer() {
    return glfwGetWindowUserPointer(glfwWindow);
}

bool Window::isPressed(const int &key) {
    return (glfwGetKey(glfwWindow, key) == GLFW_PRESS);
}

void Window::unsetAsContext() {
    glfwMakeContextCurrent(NULL);
}