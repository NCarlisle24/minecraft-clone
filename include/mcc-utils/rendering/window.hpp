#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <mcc-utils/helper.hpp>

#define DEFAULT_SCR_WIDTH 1000
#define DEFAULT_SCR_HEIGHT 800

#define DEFAULT_WINDOW_TITLE "MCC Window"

class Window {
    public:
        GLFWwindow* glfwWindow;
        bool gladIsInitialized;
        bool firstMouseFocus = true;

        Window(const int &width = DEFAULT_SCR_WIDTH, const int &height = DEFAULT_SCR_HEIGHT,
               const char* title = DEFAULT_WINDOW_TITLE);
        ~Window();
        
        int setAsContext();
        bool shouldClose();
        bool isPressed(const int &key);
        void swapBuffers();

        void setUserPointer(void* const &pointer);
        void* getUserPointer();

        static void unsetAsContext();

    private:
        int initializeGLAD();
};

#endif