#version 330 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 TexCoord;
layout (location = 2) in uint FaceDirection;

out vec2 inTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 cameraPosition;

void main() {
    vec4 worldPosition = model * vec4(Position, 1.0);
    gl_Position = projection * view * worldPosition;

    inTexCoord = TexCoord;
}