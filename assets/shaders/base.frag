#version 330 core

out vec4 FragColor;

in vec2 fragTexCoord;
flat in uint fragFaceDirection;

uniform sampler2D textureAtlas;

// typedef enum {
//     POS_X,
//     NEG_X,
//     POS_Y,
//     NEG_Y,
//     POS_Z,
//     NEG_Z,
//     NO_DIRECTION
// } AxisDirection;

const uint FACE_DIRECTION_POS_X = 0u;
const uint FACE_DIRECTION_NEG_X = 1u;
const uint FACE_DIRECTION_POS_Y = 2u;
const uint FACE_DIRECTION_NEG_Y = 3u;
const uint FACE_DIRECTION_POS_Z = 4u;
const uint FACE_DIRECTION_NEG_Z = 5u;
const uint FACE_DIRECTION_NONE = 6u;


vec3 getDirectionalShading() {
    if (fragFaceDirection == FACE_DIRECTION_POS_Y) return vec3(1.0); // top
    if (fragFaceDirection == FACE_DIRECTION_NEG_Y) return vec3(0.3); // bottom
    if (fragFaceDirection == FACE_DIRECTION_POS_X) return vec3(0.7); // pos x
    if (fragFaceDirection == FACE_DIRECTION_NEG_X) return vec3(0.6); // neg x
    if (fragFaceDirection == FACE_DIRECTION_POS_Z) return vec3(0.8); // pos z
    if (fragFaceDirection == FACE_DIRECTION_NEG_Z) return vec3(0.5); // neg z
    return vec3(1.0); // no direction
}

void main() {
    vec4 texColor = texture(textureAtlas, fragTexCoord) * vec4(getDirectionalShading(), 1.0);

    if (texColor.a < 0.1)
        discard;

    FragColor = texColor;
}