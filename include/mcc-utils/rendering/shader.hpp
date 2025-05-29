#ifndef SHADER_HPP
#define SHADER_HPP

#include <mcc-utils/helper.hpp>

#define INFO_LOG_LENGTH 512

unsigned int createShader(const char* fileName, const GLenum &shaderType);

class Shader {
    public:
        unsigned int id;
        Shader(const char* vertShaderName, const char* fragShaderName);
        ~Shader();
        void use();

        void setUniform1i(const char* name, const int &val);
        void setUniform2i(const char* name, const int &val1, const int &val2);
        void setUniform3i(const char* name, const int &val1, const int &val2,
                          const int &val3);
        void setUniform4i(const char* name, const int &val1, const int &val2,
                          const int &val3, const int &val4);

        void setUniform1f(const char* name, const float &val);
        void setUniform2f(const char* name, const float &val1, const float &val2);
        void setUniform3f(const char* name, const float &val1, const float &val2,
                          const float &val3);
        void setUniform4f(const char* name, const float &val1, const float &val2,
                          const float &val3, const float &val4);
        
        void setUniform1ui(const char* name, const unsigned int &val);
        void setUniform2ui(const char* name, const unsigned int &val1, const unsigned int &val2);
        void setUniform3ui(const char* name, const unsigned int &val1, const unsigned int &val2,
                           const unsigned int &val3);
        void setUniform4ui(const char* name, const unsigned int &val1, const unsigned int &val2,
                           const unsigned int &val3, const unsigned int &val4);
        
        void setUniformMat2(const char* name, const glm::mat2 &mat);
        void setUniformMat3(const char* name, const glm::mat3 &mat);
        void setUniformMat4(const char* name, const glm::mat4 &mat);

        static void unuse();
};

#endif