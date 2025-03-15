#include <utils/texture.hpp>

GLenum getColorFormat(const char* fileName) {
    char* extension = getFileExtension(fileName);

    if (extension == NULL) return ERROR;

    if (strcmp(extension, "png") == 0) {
        free(extension);
        return GL_RGBA;
    } else if (strcmp(extension, "jpg") == 0) {
        free(extension);
        return GL_RGB;
    } else {
        std::cout << "Warning: Unknown color format for '" << fileName << "'; assuming RGB." << std::endl;
        free(extension);
        return GL_RGB;
    }
}

void setActiveTextureUnit(const int &unit) {
    int maxTextureUnits;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureUnits);

    if (unit < 0 || unit > maxTextureUnits) {
        std::cerr << "Error: Invalid texture unit " << unit << ". Valid texture units range from 0 to " << 
                      maxTextureUnits << "." << std::endl;
    }

    glActiveTexture(GL_TEXTURE0 + unit);
}

int getActiveTextureUnit() {
    int tempTextureUnit;
    glGetIntegerv(GL_ACTIVE_TEXTURE, &tempTextureUnit);

    return tempTextureUnit;
}

void setTextureParameters() {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void setTextureVerticalOrientation(const Orientation &orientation) {
    if (orientation == NORMAL) {
        stbi_set_flip_vertically_on_load(false);
    } else {
        stbi_set_flip_vertically_on_load(true);
    }
}

Texture2D::Texture2D(const char* filePath, const GLenum &internalFormat) {
    if (!fileExists(filePath)) {
        std::cerr << "Error: File '" << filePath << "' not found." << std::endl;
        return;
    }

    GLenum fileFormat = getColorFormat(filePath);

    if (fileFormat == ERROR) {
        std::cerr << "Error: Invalid texture file '" << filePath << "'." << std::endl;
        return;
    }

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    setTextureParameters();

    int width, height, nrChannels;
    unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);

    if (!data) {
        std::cerr << "Error: Failed to load texture data from '" << filePath << "'." << std::endl;
        return;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, fileFormat, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    textureUnit = getActiveTextureUnit() - GL_TEXTURE0;

    stbi_image_free(data);
}

Texture2D::~Texture2D() {
    glDeleteTextures(1, &id);
}