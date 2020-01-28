#include <iostream>

#include <GL/glew.h>
#include <glm/ext.hpp>
#include <SDL_events.h>

#include <mastercraft/game/Game.hpp>


namespace mastercraft::game {
    
    Game::Game() :
        running(true) {
        this->windowManager = std::make_unique<WindowManager>("Mastercraft");
        this->shaderManager = std::make_unique<ShaderManager>();
        this->configManager = std::make_unique<ConfigManager>();
        this->inputManager = std::make_unique<InputManager>();
        this->chunkManager = std::make_unique<ChunkManager>();
        this->camera = std::make_unique<Camera>();
    }
    
    
    Game *game::Game::getInstance() {
        static Game game;
        return &game;
    }
    
    
    void Game::init() {
        GLenum glewInitError = glewInit();
        if (GLEW_OK != glewInitError) {
            std::cerr << glewGetErrorString(glewInitError) << std::endl;
            exit(EXIT_FAILURE);
        }
    
        SDL_SetRelativeMouseMode(SDL_TRUE);
        
        this->configManager->setOpenGlVersion(glGetString(GL_VERSION));
        this->configManager->setGlewVersion(glewGetString(GLEW_VERSION));
        this->configManager->setFaceCulling(true);
        glCullFace(GL_BACK);
        glEnable(GL_DEPTH_TEST);
    
        util::Image *atlas = util::Image::loadPNG("../assets/textures/atlas2.png", 192, 32);
        this->shaderManager->cubeShader = std::make_unique<shader::ShaderTexture>(
            "../shader/3D.vs.glsl", "../shader/3D.fs.glsl", atlas
        );
        this->shaderManager->cubeShader->addUniform("uMV", shader::UNIFORM_MATRIX_4F);
        this->shaderManager->cubeShader->addUniform("uMVP", shader::UNIFORM_MATRIX_4F);
        this->shaderManager->cubeShader->addUniform("uNormal", shader::UNIFORM_MATRIX_4F);
        this->shaderManager->cubeShader->addUniform("uChunkPosition", shader::UNIFORM_3_F);
        
        this->chunkManager->updateDrawDistance(this->configManager->getDrawDistance());
        
        SDL_DisplayMode display = this->windowManager->getDisplayMode();
        this->camera->setProjectionMatrix(this->configManager->getFov(), display.w, display.h);
    }
    
    
    void Game::cleanup() {
    }
    
    
    bool Game::pushState(state::State *state) {
        return false;
    }
    
    
    bool Game::popState() {
        return false;
    }
    
    
    void Game::update() {
        SDL_Event event;
        
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_MOUSEMOTION:
                    this->inputManager->handleMouseMotion(event.motion);
                    break;
                
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                    this->inputManager->handleMouseButton(event.button);
                    break;
                
                case SDL_MOUSEWHEEL:
                    this->inputManager->handleMouseWheel(event.wheel);
                    break;
                    
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                    this->inputManager->handleKeyboard(event.key);
                    break;
                
                case SDL_WINDOWEVENT:
                    this->windowManager->handleWindowEvent(event.window);
                    break;
                
                case SDL_QUIT:
                    this->stop();
                    break;
            }
        }
        
        this->inputManager->handleHeldMouseButton();
        this->inputManager->handleHeldKey();
        
        this->chunkManager->update();
    }
    
    
    void Game::render() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glm::mat4 globalMVMatrix = this->camera->getViewMatrix();
        
        this->shaderManager->cubeShader->use();
        this->shaderManager->cubeShader->loadUniform("uMV", glm::value_ptr(globalMVMatrix));
        this->shaderManager->cubeShader
            ->loadUniform("uMVP", glm::value_ptr(this->camera->getProjMatrix() * globalMVMatrix));
        this->shaderManager->cubeShader
            ->loadUniform("uNormal", glm::value_ptr(glm::transpose(glm::inverse(globalMVMatrix))));
        this->shaderManager->cubeShader->bindTexture();
        this->chunkManager->render();
        this->shaderManager->cubeShader->unbindTexture();
        
        this->windowManager->refresh();
    }
    
    
    bool Game::isRunning() {
        return this->running;
    }
    
    
    void Game::stop() {
        this->running = false;
    }
}
