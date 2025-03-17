#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <utils/helper.hpp>
#include <utils/camera.hpp>
#include <utils/shader.hpp>
#include <utils/window.hpp>
#include <utils/block.hpp>
#include <utils/texture.hpp>
#include <entities.hpp>

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

        void render(Window* const &window, Entity* const &entity, Shader* const &shader);
};

#endif