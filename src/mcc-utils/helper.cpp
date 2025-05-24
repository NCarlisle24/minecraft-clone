#include <mcc-utils/helper.hpp>

const glm::mat4 identityMat4(1.0f);

const glm::vec3 zeroVec3(0.0f, 0.0f, 0.0f);
const glm::vec3 upVec3(0.0f, 1.0f, 0.0f);
const glm::vec3 downVec3(0.0f, -1.0f, 0.0f);
const glm::vec3 rightVec3(1.0f, 0.0f, 0.0f);
const glm::vec3 leftVec3(-1.0f, 0.0f, 0.0f);
const glm::vec3 inVec3(0.0f, 0.0f, -1.0f);
const glm::vec3 outVec3(0.0f, 0.0f, 1.0f);

std::string readFile(const char* fileName) {
    std::string result;
    std::string currentLine;

    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cerr << "File '" << fileName << "' not found." << std::endl;
        return NULL;
    }

    while (std::getline(file, currentLine)) {
        result += currentLine;
        result.push_back('\n');
    }

    return result;
}

bool fileExists(const char* filePath) {
    if (access(filePath, F_OK) == 0) {
        return true;
    }

    return false;
}

char* getFileExtension(const char* fileName) {
    int fileNameLength = strlen(fileName);
    int extensionLength = 0;
    char* extension;

    for (int i = fileNameLength - 1; i >= 0; i--) {
        if (fileName[i] == '.') {
            break;
        } else if (fileName[i] == '/') {
            return NULL;
        }

        extensionLength++;
    }

    if (extensionLength == 0 || extensionLength == fileNameLength) {
        return NULL;
    }

    extension = (char*)malloc(extensionLength * (sizeof(char) + 1));

    for (int i = fileNameLength - extensionLength; i < fileNameLength; i++) {
        extension[i - (fileNameLength - extensionLength)] = fileName[i];
    }

    extension[extensionLength] = '\0';

    return extension;
}

void printMatrix(const glm::mat4 &mat) {
    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            std::cout << mat[row][col] << " ";
        }

        std::cout << std::endl;
    }
}