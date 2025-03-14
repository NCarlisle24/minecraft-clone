#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <utils/setup.hpp>
#include <utils/camera.hpp>
#include <utils/shader.hpp>
#include <utils/window.hpp>
#include <utils/block.hpp>
#include <utils/texture.hpp>

#define BUFFER_SIZE 5e8 // 500 MB

class Renderer {
    public:
        unsigned int VAO; // vertex array object
        unsigned int VBO; // vertex buffer object
        unsigned int EBO; // element buffer object
        unsigned int blockPositionsTexture; // texture buffer object (alternative to SSBOs)

        Renderer();
        ~Renderer();

        void render(Window* const &window, Camera* const &camera, Shader* const &shader);
};

#endif