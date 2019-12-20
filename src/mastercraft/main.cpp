#include <iostream>

#include <glimac/SDLWindowManager.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/common.hpp>
#include <glimac/Image.hpp>
#include <GL/glew.h>

#include <mastercraft/world/CubeModel.hpp>
#include <mastercraft/util/Program.hpp>
#include <mastercraft/world/TrackballCamera.hpp>
#include <mastercraft/world/FreeflyCamera.hpp>


using namespace mastercraft;
using namespace glimac;
using namespace glm;



struct CubeProgram {
    mastercraft::util::Program m_Program;
    
    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTexture;
    //GLint uKd;
    //GLint uKs;
    GLint uShininess;
    GLint uLightDir_vs;
    GLint uLightIntensity;


    CubeProgram(const FilePath &applicationPath, const std::string &vs, const std::string &fs) :
            m_Program(mastercraft::util::Program::loadProgram(applicationPath.dirPath() + vs,
                                  applicationPath.dirPath() + fs
            )) {
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");
        //uKd =  glGetUniformLocation(m_Program.getGLId(), "uKd");
        //uKs = glGetUniformLocation(m_Program.getGLId(), "uKs");
        uShininess = glGetUniformLocation(m_Program.getGLId(), "uShininess");
        uLightDir_vs = glGetUniformLocation(m_Program.getGLId(), "uLightDir_vs");
        uLightIntensity = glGetUniformLocation(m_Program.getGLId(), "uLightIntensity");
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
    CubeProgram cubeProgram(applicationPath, "../shader/3D.vs.glsl", "../shader/Light3D.fs.glsl");
    GLuint vbo, vao, ibo, dirt;
    world::CubeModel &cube = world::CubeModel::get();
    
    mat4 projMatrix = perspective(radians(70.f), 800.f / 800.f, 0.1f, 100.f);
    
    std::unique_ptr<Image> dirtTex = loadImage("../assets/textures/dirt.jpg");
    
    // Texture
    glGenTextures(1, &dirt);
    glBindTexture(GL_TEXTURE_2D, dirt);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, dirtTex->getWidth(), dirtTex->getHeight(), 0, GL_RGBA, GL_FLOAT,
                 dirtTex->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glEnable(GL_DEPTH_TEST);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);
    glGenVertexArrays(1, &vao);
    cube.load(vbo, vao, ibo);
    
    glBindVertexArray(0);
    
    // Application Loop:
    //world::TrackballCamera tbcam = world::TrackballCamera();
    world::FreeflyCamera tbcam = world::FreeflyCamera();
    glm::ivec2 lastMousePos;
    bool done = false;


    ////////////////////////////////////////////
    //boucle de rendu
    ///////////////////////////////////////////
    while (!done) {
        
        // Event loop:
        SDL_Event e;

        while (windowManager.pollEvent(e)) {
            SDL_GetRelativeMouseState(&lastMousePos.x, &lastMousePos.y);

            if (e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }

        else if(windowManager.isMouseButtonPressed(SDL_BUTTON_RIGHT)) {
            std::cout << "rrrrrrrrrrrrrr" <<std::endl;
            std::cout << lastMousePos.x << std::endl;
            if(lastMousePos.x > 0) {
                tbcam.rotateLeft(-1.);
            }
            else if(lastMousePos.x < 0) {
                tbcam.rotateLeft(1.);
            }
            if(lastMousePos.y > 0) {
                tbcam.rotateUp(-1.);
            }
            else if(lastMousePos.y < 0) {
                tbcam.rotateUp(1.);
            }
        }
    }
    // Keyboard
    if(windowManager.isKeyPressed(SDLK_z) || windowManager.isKeyPressed(SDLK_UP)) {
        tbcam.moveFront(0.3);
    }
    else if(windowManager.isKeyPressed(SDLK_s) || windowManager.isKeyPressed(SDLK_DOWN)) {
        tbcam.moveFront(-0.3);
    }
    if(windowManager.isKeyPressed(SDLK_q) || windowManager.isKeyPressed(SDLK_LEFT)) {
        tbcam.moveLeft(0.3);
    }
    else if(windowManager.isKeyPressed(SDLK_d) || windowManager.isKeyPressed(SDLK_RIGHT)) {
        tbcam.moveLeft(-0.3);
    }

    /*SDL_GetRelativeMouseState(&lastMousePos.x, &lastMousePos.y);
        if (windowManager.isMouseButtonPressed(SDL_BUTTON_LEFT)) {
            tbcam.rotateLeft(lastMousePos.x);
            tbcam.rotateUp(lastMousePos.y);
        }
        */
        // Cleaning
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Transformations
        tbcam.computeDirectionVectors();
        glm::mat4 globalMVMatrix = tbcam.getViewMatrix();
        glm::mat4 cubeMVMatrix = glm::rotate(globalMVMatrix, 0.f, glm::vec3(0, 1, 0));
        cubeMVMatrix = glm::rotate(cubeMVMatrix, 0.f, glm::vec3(1, 0, 0));

        //lumiere
        glUniform1f(cubeProgram.uShininess, 32.0);
        glm::vec4 LightDir = tbcam.getViewMatrix()*glm::vec4(-1.0, -1.0, -1.0, 0.0);
        glUniform3f(cubeProgram.uLightDir_vs, LightDir.x, LightDir.y, LightDir.z);
        glUniform3f(cubeProgram.uLightIntensity, 2.0, 2.0, 2.0);

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
