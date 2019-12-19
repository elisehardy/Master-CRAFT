#include <iostream>

#include <glimac/SDLWindowManager.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/common.hpp>
#include <glimac/Image.hpp>
#include <GL/glew.h>

#include <mastercraft/world/CubeModel.hpp>
#include <mastercraft/util/Program.hpp>
#include <mastercraft/world/TrackballCamera.hpp>


using namespace mastercraft;
using namespace glimac;
using namespace glm;



struct CubeProgram {
    mastercraft::util::Program m_Program;
    
    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTexture;
    
    
    CubeProgram(const FilePath &applicationPath, const std::string &vs, const std::string &fs) :
            m_Program(mastercraft::util::Program::loadProgram(applicationPath.dirPath() + vs,
                                  applicationPath.dirPath() + fs
            )) {
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");
    }
};



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
    SDLWindowManager windowManager(800, 800, "Mastercraft");
    initGlew();
    
    FilePath applicationPath(argv[0]);
    CubeProgram cubeProgram(applicationPath, "../shader/3D.vs.glsl", "../shader/3D.fs.glsl");
    
    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_TEXTURE = 2;
    
    GLuint vbo, vao, ibo, dirt;
    
    world::CubeModel &cube = world::CubeModel::get();
    
    mat4 projMatrix;
    projMatrix = perspective(radians(70.f), 800.f / 800.f, 0.1f, 100.f);
    
    std::unique_ptr<Image> dirtTex = loadImage("../assets/textures/dirt.jpg");
    
    // Texture
    glGenTextures(1, &dirt);
    glBindTexture(GL_TEXTURE_2D, dirt);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, dirtTex->getWidth(), dirtTex->getHeight(), 0, GL_RGBA, GL_FLOAT,
                 dirtTex->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // VBO
    glEnable(GL_DEPTH_TEST);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, cube.size(), &cube, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    // IBO
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube.indexes), cube.indexes, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    
    // VAO
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(vec3),
                          (const GLvoid *) (offsetof(world::CubeModel, vertices)));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(vec3),
                          (const GLvoid *) (offsetof(world::CubeModel, normals)));
    glVertexAttribPointer(VERTEX_ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof(vec2),
                          (const GLvoid *) (offsetof(world::CubeModel, textures)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(0);
    
    // Application Loop:
    world::TrackballCamera tbcam = world::TrackballCamera();
    glm::ivec2 lastMousePos;
    bool done = false;
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
        cubeMVMatrix = glm::rotate(cubeMVMatrix, 0.f, glm::vec3(1, 0, 0));
        glUniformMatrix4fv(cubeProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(cubeMVMatrix));
        glUniformMatrix4fv(cubeProgram.uNormalMatrix, 1, GL_FALSE,
                           glm::value_ptr(glm::transpose(glm::inverse(cubeMVMatrix))));
        glUniformMatrix4fv(cubeProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * cubeMVMatrix));
    
        cubeProgram.m_Program.use();
        glUniform1i(cubeProgram.uTexture, 0);
        glBindVertexArray(vao);
        glBindTexture(GL_TEXTURE_2D, dirt);
        
        glDrawElements(GL_TRIANGLES, cube.indexesCount(), GL_UNSIGNED_INT, nullptr);
        
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindVertexArray(0);
        
        // Update the display
        windowManager.swapBuffers();
    }
    
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    
    return EXIT_SUCCESS;
}
