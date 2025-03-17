#ifndef HELPER_HPP
#define HELPER_HPP

#include <ext/glad/glad.h>
#include <ext/GLFW/glfw3.h>

#include <iostream>
#include <stdbool.h>
#include <string>
#include <cstring>
#include <cmath>
#include <fstream>
#include <unistd.h>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <chrono>

#include <ext/stb/stb_image.h>
#include <ext/glm/glm.hpp>
#include <ext/glm/gtc/matrix_transform.hpp>
#include <ext/glm/gtc/type_ptr.hpp>

#define SUCCESS 0
#define ERROR -1

extern const glm::mat4 identityMat4;

extern const glm::vec3 zeroVec3; // (0.0f, 0.0f, 0.0f)
extern const glm::vec3 upVec3; // (0.0f, 1.0f, 0.0f)
extern const glm::vec3 downVec3; // (0.0f, -1.0f, 0.0f)
extern const glm::vec3 rightVec3; // (1.0f, 0.0f, 0.0f)
extern const glm::vec3 leftVec3; // (-1.0f, 0.0f, 0.0f)
extern const glm::vec3 inVec3; // (0.0f, 0.0f, -1.0f)
extern const glm::vec3 outVec3; // (0.0f, 0.0f, 1.0f)

typedef enum {
    DEGREES,
    RADIANS
} AngleType;

std::string readFile(const char* fileName);
char* getFileExtension(const char* fileName);
bool fileExists(const char* filePath);
void printMatrix(const glm::mat4 &mat);

#endif