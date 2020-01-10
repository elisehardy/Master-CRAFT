#include <iostream>

//#include <glimac/SDLWindowManager.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/common.hpp>
#include <GL/glew.h>


#include <mastercraft/world/CubeModel.hpp>
#include <mastercraft/shader/ShaderTexture.hpp>
#include <mastercraft/world/FreeflyCamera.hpp>
#include <mastercraft/world/PerlinNoise.hpp>
#include <mastercraft/world/PPM.h>
#include <mastercraft/util/SDLWindowManager.hpp>

using namespace mastercraft;


//struct CubeProgram {
//    mastercraft::util::Program m_Program;
//
//    GLint uMVPMatrix;
//    GLint uMVMatrix;
//    GLint uNormalMatrix;
//    GLint uTexture;
//    //GLint uKd;
//    //GLint uKs;
//    GLint uShininess;
//    GLint uLightDir_vs;
//    GLint uLightIntensity;
//
//
//    CubeProgram(const FilePath &applicationPath, const std::string &vs, const std::string &fs) :
//            m_Program(mastercraft::util::Program::loadProgram(applicationPath.dirPath() + vs,
//                                  applicationPath.dirPath() + fs
//            )) {
//        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
//        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
//        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
//        uTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");
//        //uKd =  glGetUniformLocation(m_Program.getGLId(), "uKd");
//        //uKs = glGetUniformLocation(m_Program.getGLId(), "uKs");
//        uShininess = glGetUniformLocation(m_Program.getGLId(), "uShininess");
//        uLightDir_vs = glGetUniformLocation(m_Program.getGLId(), "uLightDir_vs");
//        uLightIntensity = glGetUniformLocation(m_Program.getGLId(), "uLightIntensity");
//    }
//};


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


    util::SDLWindowManager windowManager( "Mastercraft");
    initGlew();

    auto window_size  = SDL_GetVideoInfo();


    glimac::FilePath applicationPath(argv[0]);
    shader::ShaderTexture cubeProgram("../shader/3D.vs.glsl", "../shader/light3D.fs.glsl", "../assets/textures/dirt.jpg");
    world::CubeModel &cube = world::CubeModel::get();
    GLuint vbo, vao, ibo;
    
    glm::mat4 projMatrix = glm::perspective(glm::radians(70.f), float(window_size->current_w) / float(window_size->current_h), 0.1f, 100.f);
    
    glEnable(GL_DEPTH_TEST);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);
    glGenVertexArrays(1, &vao);
    cube.load(vbo, vao, ibo);
    
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
            
            else if (windowManager.isMouseButtonPressed(SDL_BUTTON_RIGHT)) {
                if (lastMousePos.x > 0) {
                    tbcam.rotateLeft(-1.);
                }
                else if (lastMousePos.x < 0) {
                    tbcam.rotateLeft(1.);
                }
                if (lastMousePos.y > 0) {
                    tbcam.rotateUp(-1.);
                }
                else if (lastMousePos.y < 0) {
                    tbcam.rotateUp(1.);
                }
            }
        }
        
        // Keyboard
        if (windowManager.isKeyPressed(SDLK_z) || windowManager.isKeyPressed(SDLK_UP)) {
            tbcam.moveFront(0.3);
        }
        else if (windowManager.isKeyPressed(SDLK_s) || windowManager.isKeyPressed(SDLK_DOWN)) {
            tbcam.moveFront(-0.3);
        }
        if (windowManager.isKeyPressed(SDLK_q) || windowManager.isKeyPressed(SDLK_LEFT)) {
            tbcam.moveLeft(0.3);
        }
        else if (windowManager.isKeyPressed(SDLK_d) || windowManager.isKeyPressed(SDLK_RIGHT)) {
            tbcam.moveLeft(-0.3);
        }
        
        // Cleaning
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Transformations
        tbcam.computeDirectionVectors();
        glm::mat4 globalMVMatrix = tbcam.getViewMatrix();
        glm::mat4 cubeMVMatrix = glm::rotate(globalMVMatrix, 0.f, glm::vec3(0, 1, 0));
        
        cubeMVMatrix = glm::rotate(cubeMVMatrix, 0.f, glm::vec3(1, 0, 0));
        
        // Lumiere
        //        glUniform1f(cubeProgram.uShininess, 32.0);
        //        glm::vec4 LightDir = tbcam.getViewMatrix() * glm::vec4(-1.0, -1.0, -1.0, 0.0);
        //        glUniform3f(cubeProgram.uLightDir_vs, LightDir.x, LightDir.y, LightDir.z);
        //        glUniform3f(cubeProgram.uLightIntensity, 2.0, 2.0, 2.0);
        
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


    //perlinNoise test
    unsigned int width = 600, height = 450;
    PPM image_perlin(width, height);

    PerlinNoise noise(456);
    unsigned int kk = 0;
    // Visit every pixel of the image and assign a color generated with Perlin noise
    for(unsigned int i = 0; i < height; ++i) {     // y
        for(unsigned int j = 0; j < width; ++j) {  // x
            double x = (double)j/((double)width);
            double y = (double)i/((double)height);

            // Typical Perlin noise
            double n = noise.noise(10 * x, 10 * y, 0.8);

            // Map the values to the [0, 255] interval, for simplicity we use
            // tones of grey
            image_perlin.r[kk] = floor(255 * n);
            image_perlin.g[kk] = floor(255 * n);
            image_perlin.b[kk] = floor(255 * n);
            kk++;
        }
    }

    // Save the image in a binary PPM file
    image_perlin.write("PerlinNoiseTest.ppm");

    return EXIT_SUCCESS;
}
