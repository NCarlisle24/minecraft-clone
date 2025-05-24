#version 330 core

out vec4 FragColor;

in vec2 inTexCoord;

uniform sampler2D textureAtlas;

void main() {
    vec4 texColor = texture(textureAtlas, inTexCoord);

    if (texColor.a < 0.1)
        discard;

    FragColor = texColor;
}