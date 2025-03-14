#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <utils/setup.hpp>

#define DEFAULT_SCR_WIDTH 800
#define DEFAULT_SCR_HEIGHT 600

void defaultFrameBufferSizeCallback(GLFWwindow* window, int width, int height);

class Window {
    public:
        GLFWwindow* glfwWindow;
        bool gladIsInitialized;

        Window(const int &width = DEFAULT_SCR_WIDTH, const int &height = DEFAULT_SCR_HEIGHT,
               const char* title = "(default title)");
        ~Window();
        
        int setAsContext();
        bool shouldClose();
        bool isPressed(const int &key);
        void swapBuffers();

        void setFramebufferSizeCallback(void (&callback)(GLFWwindow*, int, int));

        void getFramebufferSize(int* const &width, int* const &height);

        static void unsetAsContext();
        static void toggleWireframeMode();

    private:
        int initializeGLAD();
        static void enableCapabilities();
};

#endif