#ifndef SETUP_HPP
#define SETUP_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdbool.h>
#include <string>
#include <cstring>
#include <fstream>
#include <unistd.h>
#include <algorithm>

#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define SUCCESS 0
#define ERROR -1

#define DEFAULT_SCR_WIDTH 800
#define DEFAULT_SCR_HEIGHT 600

extern bool glfwIsInitialized;

extern const glm::mat4 identityMat4;

extern const glm::vec3 zeroVec3;
extern const glm::vec3 upVec3;
extern const glm::vec3 downVec3;
extern const glm::vec3 rightVec3;
extern const glm::vec3 leftVec3;
extern const glm::vec3 inVec3;
extern const glm::vec3 outVec3;

static void glfwErrorCallback(int error, const char* msg);
int setupGLFW();

std::string readFile(const char* fileName);
char* getFileExtension(const char* fileName);
bool fileExists(const char* filePath);
void printMatrix(const glm::mat4 &mat);

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

        static void unsetAsContext();
        static void toggleWireframeMode();
    
    private:
        int initializeGLAD();
        static void enableCapabilities();
};

#endif