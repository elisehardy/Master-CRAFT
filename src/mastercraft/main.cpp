#include <iostream>

#include <GL/glew.h>
#include <glimac/FilePath.hpp>
#include <glimac/common.hpp>

#include <mastercraft/shader/ShaderTexture.hpp>
#include <mastercraft/util/SDLWindowManager.hpp>
#include <mastercraft/world/SuperChunk.hpp>
#include <mastercraft/util/TrackballCamera.hpp>


using namespace mastercraft;


static void initGlew() {
    GLenum glewInitError = glewInit();
    if (GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        exit(EXIT_FAILURE);
    }
    
    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;
}


int main(int argc, char **argv) {
    util::SDLWindowManager window = util::SDLWindowManager("Mastercraft");
    initGlew();
    
    shader::ShaderTexture cubeShader(
        "../shader/3D.vs.glsl", "../shader/3D.fs.glsl", "../assets/textures/dirt.jpg"
    );
    cubeShader.addUniform("uMV", shader::UNIFORM_MATRIX_4F);
    cubeShader.addUniform("uMVP", shader::UNIFORM_MATRIX_4F);
    cubeShader.addUniform("uNormal", shader::UNIFORM_MATRIX_4F);
    cubeShader.addUniform("uChunkPosition", shader::UNIFORM_3_F);
    
    world::SuperChunk chunk = world::SuperChunk(0, 0, 0);
    for (GLuint x = 0; x < world::SuperChunk::X; x++) {
        for (GLuint y = 0; y < world::SuperChunk::Y; y++) {
            for (GLuint z = 0; z < world::SuperChunk::Z; z++) {
                chunk.set(x, y, z, world::CubeType::DIRT);
            }
        }
    }
    
    glm::mat4 projMatrix = glm::perspective(
        glm::radians(70.f), float(window.getWidth()) / float(window.getHeight()), 0.1f, 100.f
    );
    
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    util::TrackballCamera tbcam = util::TrackballCamera();
    glm::ivec2 lastMousePos;
    bool done = false;
    SDL_Event e;
    while (!done) {
        while (window.pollEvent(e)) {
            SDL_GetRelativeMouseState(&lastMousePos.x, &lastMousePos.y);
            
            if (e.type == SDL_QUIT) {
                done = true;
            }
                
                // Mouse
            else if (window.isMouseButtonPressed(SDL_BUTTON_RIGHT)) {
                tbcam.rotateLeft(lastMousePos.x);
                tbcam.rotateUp(lastMousePos.y);
            }
        }
        
        // Keyboard
        if (window.isKeyPressed(SDL_SCANCODE_ESCAPE)) {
            done = true;
        }
        if (window.isKeyPressed(SDL_SCANCODE_W) || window.isKeyPressed(SDL_SCANCODE_UP)) {
            tbcam.moveFront(0.3);
        }
        if (window.isKeyPressed(SDL_SCANCODE_S) || window.isKeyPressed(SDL_SCANCODE_DOWN)) {
            tbcam.moveFront(-0.3);
        }
        if (window.isKeyPressed(SDL_SCANCODE_A) || window.isKeyPressed(SDL_SCANCODE_LEFT)) {
            tbcam.moveRight(-0.3);
        }
        if (window.isKeyPressed(SDL_SCANCODE_D) || window.isKeyPressed(SDL_SCANCODE_RIGHT)) {
            tbcam.moveRight(0.3);
        }
        if (window.isKeyPressed(SDL_SCANCODE_LCTRL)) {
            tbcam.moveUp(-0.3);
        }
        if (window.isKeyPressed(SDL_SCANCODE_SPACE)) {
            tbcam.moveUp(0.3);
        }
        
        chunk.update();
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //        tbcam.computeDirectionVectors();
        glm::mat4 globalMVMatrix = tbcam.getViewMatrix();
        cubeShader.use();
        cubeShader.loadUniform("uMV", glm::value_ptr(globalMVMatrix));
        cubeShader.loadUniform("uMVP", glm::value_ptr(projMatrix * globalMVMatrix));
        cubeShader.loadUniform("uNormal", glm::value_ptr(glm::transpose(glm::inverse(globalMVMatrix))));
        cubeShader.bindTexture();
        chunk.draw(cubeShader);
        cubeShader.unbindTexture();
        
        // Update the display
        window.refresh();
    }
    
    return EXIT_SUCCESS;
}
