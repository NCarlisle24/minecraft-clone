#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <utils/helper.hpp>

#define MAX_TEXTURE_UNITS 32
#define NO_TEXTURE_UNIT -1

typedef enum {
    NORMAL,
    FLIP
} Orientation;

GLenum getColorFormat(const char* fileName);
void setTextureParameters();
void setActiveTextureUnit(const int &unit);
int getActiveTextureUnit();
void setTextureVerticalOrientation(const Orientation &orientation);

class Texture2D {
    public:
        unsigned int id;
        int8_t textureUnit;
        Texture2D(const char* filePath, const GLenum &internalFormat = GL_RGB);
        ~Texture2D();
};

#endif