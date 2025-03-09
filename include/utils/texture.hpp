#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <utils/setup.hpp>

typedef enum {
    NORMAL,
    FLIP
} Orientation;

GLenum getColorFormat(const char* fileName);
void setTextureParameters();
void setActiveTextureUnit(const int &unit);
void setTextureVerticalOrientation(const Orientation &orientation);

class Texture2D {
    public:
        unsigned int id;
        Texture2D(const char* filePath, const GLenum &internalFormat = GL_RGB);
        ~Texture2D();
};

#endif