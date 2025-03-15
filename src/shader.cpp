#include <utils/shader.hpp>

unsigned int createShader(const char* fileName, const GLenum &shaderType) {
    int success;
    char infoLog[INFO_LOG_LENGTH];

    unsigned int shader = glCreateShader(shaderType);
    if (shader == GL_INVALID_ENUM) {
        std::cerr << "Error: Invalid shader type for '" << fileName << "'." << std::endl;
        return GL_INVALID_ENUM;
    }

    std::string sourceString = readFile(fileName);
    const char* source = sourceString.c_str();

    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, INFO_LOG_LENGTH, NULL, infoLog);
        std::cerr << "Error: Shader compilation failed for '" << fileName
                  << "'." << std::endl << infoLog;
    }

    return shader;
}

Shader::Shader(const char* vertShaderName, const char* fragShaderName) {
    unsigned int vertShader = createShader(vertShaderName, GL_VERTEX_SHADER);
    unsigned int fragShader = createShader(fragShaderName, GL_FRAGMENT_SHADER);

    int success;
    char infoLog[INFO_LOG_LENGTH];

    id = glCreateProgram();

    glAttachShader(id, vertShader);
    glAttachShader(id, fragShader);
    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id, INFO_LOG_LENGTH, NULL, infoLog);
        std::cerr << "Error: Shader program link failed for '" << vertShaderName
                  << "' and '" << fragShaderName << "'." << std::endl
                  << infoLog << std::endl;
    }

    glDeleteProgram(vertShader);
    glDeleteProgram(fragShader);
}

Shader::~Shader() {
    glDeleteProgram(id);
}

void Shader::use() {
    glUseProgram(id);
}


void Shader::setUniform1f(const char* name, const float &val) {
    glUniform1f(glGetUniformLocation(id, name), val);
}

void Shader::setUniform2f(const char* name, const float &val1, const float &val2) {
    glUniform2f(glGetUniformLocation(id, name), val1, val2);
}

void Shader::setUniform3f(const char* name, const float &val1, const float &val2, const float& val3) {
    glUniform3f(glGetUniformLocation(id, name), val1, val2, val3);
}

void Shader::setUniform4f(const char* name, const float &val1, const float &val2, const float &val3, const float &val4) {
    glUniform4f(glGetUniformLocation(id, name), val1, val2, val3, val4);
}

void Shader::setUniform1i(const char* name, const int &val) {
    glUniform1i(glGetUniformLocation(id, name), val);
}

void Shader::setUniform2i(const char* name, const int &val1, const int &val2) {
    glUniform2i(glGetUniformLocation(id, name), val1, val2);
}

void Shader::setUniform3i(const char* name, const int &val1, const int &val2, const int &val3) {
    glUniform3i(glGetUniformLocation(id, name), val1, val2, val3);
}

void Shader::setUniform4i(const char* name, const int &val1, const int &val2, const int &val3, const int &val4) {
    glUniform4i(glGetUniformLocation(id, name), val1, val2, val3, val4);
}

void Shader::setUniform1ui(const char* name, const unsigned int &val) {
    glUniform1i(glGetUniformLocation(id, name), val);
}

void Shader::setUniform2ui(const char* name, const unsigned int &val1, const unsigned int &val2) {
    glUniform2ui(glGetUniformLocation(id, name), val1, val2);
}

void Shader::setUniform3ui(const char* name, const unsigned int &val1, const unsigned int &val2,
                           const unsigned int &val3) {
    glUniform3ui(glGetUniformLocation(id, name), val1, val2, val3);
}

void Shader::setUniform4ui(const char* name, const unsigned int &val1, const unsigned int &val2,
                           const unsigned int &val3, const unsigned int &val4) {
    glUniform4ui(glGetUniformLocation(id, name), val1, val2, val3, val4);
}

void Shader::setUniformMat2(const char* name, const glm::mat2 &mat) {
    glUniformMatrix2fv(glGetUniformLocation(id, name), 1, GL_FALSE, glm::value_ptr(mat));
}
void Shader::setUniformMat3(const char* name, const glm::mat3 &mat) {
    glUniformMatrix3fv(glGetUniformLocation(id, name), 1, GL_FALSE, glm::value_ptr(mat));
}
void Shader::setUniformMat4(const char* name, const glm::mat4 &mat) {
    glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::unuse() {
    glUseProgram(0);
}