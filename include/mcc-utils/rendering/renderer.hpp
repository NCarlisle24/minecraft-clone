#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <mcc-utils/helper.hpp>
#include <mcc-utils/rendering/camera.hpp>
#include <mcc-utils/rendering/shader.hpp>
#include <mcc-utils/rendering/window.hpp>
#include <mcc-utils/world/block.hpp>
#include <mcc-utils/rendering/texture.hpp>

#define BUFFER_SIZE 5e8 // 500 MB

void toggleWireframeMode();
class Renderer {
    public:
        unsigned int VAO = 0; // vertex array object
        unsigned int VBO = 0; // vertex buffer object
        unsigned int EBO = 0; // element buffer object
        unsigned int blockPositionsTexture = 0; // texture buffer object (alternative to SSBOs)

        Renderer();
        ~Renderer();

        void render(Window* const &window, Camera* const &camera, Shader* const &shader);
};

#endif