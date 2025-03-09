#version 330 core

out vec4 FragColor;

in vec2 inTexCoord;

uniform sampler2D wallTexture;
uniform sampler2D smileTexture;

void main() {
    FragColor = mix(texture(wallTexture, inTexCoord), texture(smileTexture, inTexCoord), 0.2f);
}