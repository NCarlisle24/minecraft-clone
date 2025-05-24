#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <mcc-utils/helper.hpp>

#define CHUNK_SIZE 32
#define WORLD_HEIGHT 256

#define BLOCK_VERTICES_LENGTH 24
#define BLOCK_INDICES_LENGTH 36

typedef uint8_t BlockID;
typedef enum {
    POS_X,
    NEG_X,
    POS_Y,
    NEG_Y,
    POS_Z,
    NEG_Z,
    NO_DIRECTION
} AxisDirection;
typedef struct {
    float x, y, z;
    float u, v;
    AxisDirection faceDirection;
} BlockVertex;

typedef struct {
    uint8_t id;
    AxisDirection horizontalOrientation;
    AxisDirection verticalOrientation;
} Block;

typedef struct {
    Block blockData[CHUNK_SIZE * CHUNK_SIZE * WORLD_HEIGHT];
} Chunk;

extern const BlockVertex blockVertices[BLOCK_VERTICES_LENGTH];
extern const unsigned int blockIndices[BLOCK_INDICES_LENGTH];

#endif