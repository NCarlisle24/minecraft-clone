#ifndef SETUP_HPP
#define SETUP_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdbool.h>
#include <string>
#include <cstring>
#include <cmath>
#include <fstream>
#include <unistd.h>
#include <algorithm>

#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define SUCCESS 0
#define ERROR -1

extern bool glfwIsInitialized;

extern const glm::mat4 identityMat4;

extern const glm::vec3 zeroVec3; // (0.0f, 0.0f, 0.0f)
extern const glm::vec3 upVec3; // (0.0f, 1.0f, 0.0f)
extern const glm::vec3 downVec3; // (0.0f, -1.0f, 0.0f)
extern const glm::vec3 rightVec3; // (1.0f, 0.0f, 0.0f)
extern const glm::vec3 leftVec3; // (-1.0f, 0.0f, 0.0f)
extern const glm::vec3 inVec3; // (0.0f, 0.0f, -1.0f)
extern const glm::vec3 outVec3; // (0.0f, 0.0f, 1.0f)

static void glfwErrorCallback(int error, const char* msg);
int setupGLFW();

std::string readFile(const char* fileName);
char* getFileExtension(const char* fileName);
bool fileExists(const char* filePath);
void printMatrix(const glm::mat4 &mat);

#endif