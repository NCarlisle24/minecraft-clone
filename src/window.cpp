#include <utils/window.hpp>

void defaultFrameBufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

Window::Window(const int &width, const int &height, const char* title) {
    glfwWindow = NULL;
    gladIsInitialized = false;

    if (!glfwIsInitialized) {
        std::cout << "Error: Window cannot be created with GLFW uninitialized." << std::endl;
        return;
    }

    glfwWindow = glfwCreateWindow(width, height, title, NULL, NULL);

    if (glfwWindow == NULL) {
        std::cout << "Error: Failed to create GLFWwindow." << std::endl;
        return;
    }

    setFramebufferSizeCallback(defaultFrameBufferSizeCallback);

    GLFWwindow* previousContext = glfwGetCurrentContext();
    glfwMakeContextCurrent(glfwWindow);

    initializeGLAD();
    enableCapabilities();

    glfwMakeContextCurrent(previousContext);
}

Window::~Window() {
    if (glfwWindow != NULL) {
        glfwDestroyWindow(glfwWindow);
    }
}

int Window::setAsContext() {
    if (glfwWindow == NULL) {
        std::cout << "Error: Window that doesn't exist cannot be set as context." << std::endl;
        return ERROR;
    }

    glfwMakeContextCurrent(glfwWindow);

    return SUCCESS;
}

int Window::initializeGLAD() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Error: GLAD failed to initialize." << std::endl;
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

bool Window::isPressed(const int &key) {
    return (glfwGetKey(glfwWindow, key) == GLFW_PRESS);
}

void Window::setFramebufferSizeCallback(void (&callback)(GLFWwindow*, int, int)) {
    glfwSetFramebufferSizeCallback(glfwWindow, *callback);
}

void Window::getFramebufferSize(int* const &width, int* const &height) {
    glfwGetFramebufferSize(glfwWindow, width, height);
}

void Window::enableCapabilities() {
    glEnable(GL_DEPTH_TEST);
}


void Window::toggleWireframeMode() {
    int polygonMode;
    glGetIntegerv(GL_POLYGON_MODE, &polygonMode);

    if (polygonMode == GL_FILL) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void Window::unsetAsContext() {
    glfwMakeContextCurrent(NULL);
}