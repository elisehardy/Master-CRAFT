#include <iostream>

#include <glimac/SDLWindowManager.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/common.hpp>
#include <glimac/Image.hpp>
#include <GL/glew.h>

#include <mastercraft/world/CubeModel.hpp>
#include <mastercraft/world/TrackballCamera.hpp>
#include <mastercraft/shader/ShaderTexture.hpp>


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
    glimac::SDLWindowManager windowManager(800, 800, "Mastercraft");
    initGlew();
    
    glimac::FilePath applicationPath(argv[0]);
    shader::ShaderTexture cubeProgram("../shader/3D.vs.glsl", "../shader/3D.fs.glsl", "../assets/textures/dirt.jpg");
    world::CubeModel &cube = world::CubeModel::get();
    GLuint vbo, vao, ibo;
    
    glm::mat4 projMatrix = glm::perspective(glm::radians(70.f), 800.f / 800.f, 0.1f, 100.f);
    
    glEnable(GL_DEPTH_TEST);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);
    glGenVertexArrays(1, &vao);
    cube.load(vbo, vao, ibo);
    
    // Application Loop:
    bool done = false;
    glm::ivec2 lastMousePos;
    world::TrackballCamera tbcam = world::TrackballCamera();
    while (!done) {
        
        // Event loop:
        SDL_Event e;
        while (windowManager.pollEvent(e)) {
            if (e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }
        
        SDL_GetRelativeMouseState(&lastMousePos.x, &lastMousePos.y);
        if (windowManager.isMouseButtonPressed(SDL_BUTTON_LEFT)) {
            tbcam.rotateLeft(lastMousePos.x);
            tbcam.rotateUp(lastMousePos.y);
        }
        
        // Cleaning
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Transformations
        glm::mat4 globalMVMatrix = tbcam.getViewMatrix();
        glm::mat4 cubeMVMatrix = glm::rotate(globalMVMatrix, 0.f, glm::vec3(0, 1, 0));
        
        cubeProgram.use();
        cubeProgram.loadMatrices(cubeMVMatrix, projMatrix * cubeMVMatrix, glm::transpose(glm::inverse(cubeMVMatrix)));
        
        glBindVertexArray(vao);
        cubeProgram.bindTexture();
        glDrawElements(GL_TRIANGLES, cube.indexesCount(), GL_UNSIGNED_INT, nullptr);
        cubeProgram.unbindTexture();
        glBindVertexArray(0);
        
        // Update the display
        windowManager.swapBuffers();
    }
    
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    
    return EXIT_SUCCESS;
}
