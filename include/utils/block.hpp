#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <utils/setup.hpp>

typedef struct {
    float x, y, z;
    float u, v;
    unsigned int faceDirection;
} Vertex;

extern const Vertex blockVertices[24];
extern const unsigned int blockIndices[36];

typedef enum {
    POS_X,
    NEG_X,
    POS_Y,
    NEG_Y,
    POS_Z,
    NEG_Z
} FaceDirection;

typedef struct {
    unsigned int id;
    glm::vec3 position;
} Block;

#endif