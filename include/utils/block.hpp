#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <utils/helper.hpp>

#define CHUNK_SIZE 32
#define BLOCK_VERTICES_LENGTH 24
#define BLOCK_INDICES_LENGTH 36
typedef enum {
    POS_X,
    NEG_X,
    POS_Y,
    NEG_Y,
    POS_Z,
    NEG_Z
} FaceDirection;
typedef struct {
    float x, y, z;
    float u, v;
    FaceDirection faceDirection;
} BlockVertex;

extern const BlockVertex blockVertices[BLOCK_VERTICES_LENGTH];
extern const unsigned int blockIndices[BLOCK_INDICES_LENGTH];

typedef struct {
    unsigned int id;
    glm::vec3 position;
} Block;

#endif