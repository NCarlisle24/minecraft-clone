#version 330 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 TexCoord;
layout (location = 2) in uint FaceDirection;

out vec2 inTexCoord;

uniform mat4 view;
uniform mat4 projection;
uniform vec3 cameraPosition;

uniform samplerBuffer blockPositionTexture;

void main() {
    vec3 blockPosition = texelFetch(blockPositionTexture, gl_InstanceID).rgb;
    vec3 worldPosition = Position + blockPosition;
    gl_Position = projection * view * vec4(worldPosition, 1.0f);

    inTexCoord = TexCoord;
}