#include <iostream>

#include <GL/glew.h>
#include <glm/ext.hpp>
#include <SDL_events.h>

#include <mastercraft/game/Game.hpp>


namespace mastercraft::game {
    
    Game::Game() :
        running(true) {
        
    }
    
    
    Game *game::Game::getInstance() {
        static Game game;
        return &game;
    }
    
    
    void Game::init() {
        this->windowManager = std::make_unique<WindowManager>("Mastercraft");
        
        GLenum glewInitError = glewInit();
        if (GLEW_OK != glewInitError) {
            throw std::runtime_error(reinterpret_cast<const char *>(glewGetErrorString(glewInitError)));
        }
    
        util::Image *atlas = util::Image::loadPNG("../assets/block/atlas.png", 192, 256);
        
        this->configManager = std::make_unique<ConfigManager>();
        this->inputManager = std::make_unique<InputManager>();
        this->camera = std::make_unique<Camera>();
        this->chunkManager = std::make_unique<ChunkManager>(atlas, this->configManager->getDistanceView());
        this->sun = std::make_unique<entity::Sun>(0, 300, 0);
        
        this->chunkManager->init();
        this->configManager->init();
        this->camera->init();
        
        this->lastTick = std::chrono::steady_clock::now();
    }
    
    
    void Game::cleanup() {
    }

    
    bool Game::tick() {
        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        double duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - this->lastTick).count();
        
        if (duration > 1. / this->configManager->getTickRate() * 1000) {
            this->lastTick = std::chrono::steady_clock::now();
            return true;
        }
        
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
    
    
        if (this->tick()) {
            this->chunkManager->update();
        }
        this->sun->update();
    }
    
    
    void Game::render() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
        glDisable(GL_DEPTH_TEST);
        this->sun->render();
        glEnable(GL_DEPTH_TEST);
        
        this->chunkManager->render();
        
        this->windowManager->refresh();
    }
    
    
    bool Game::isRunning() {
        return this->running;
    }
    
    
    void Game::stop() {
        this->running = false;
    }
}
