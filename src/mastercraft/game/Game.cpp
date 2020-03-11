#include <iostream>

#include <GL/glew.h>
#include <SDL2/SDL_events.h>

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
        
        util::Image *atlas = util::Image::loadPNG("../assets/block/atlas.png", 3072, 16384);
        
        this->configManager = std::make_unique<ConfigManager>();
        this->inputManager = std::make_unique<InputManager>();
        this->camera = std::make_unique<Camera>();
        this->debug = std::make_unique<Debug>();
        this->score = std::make_unique<Score>();

        this->chunkManager = std::make_unique<ChunkManager>(atlas);
        this->skybox = std::make_unique<entity::Skybox>();
        this->sun = std::make_unique<entity::Sun>();
        this->magie = std::make_unique<entity::Magie2>();

        this->chunkManager->init();
        this->configManager->init();
        this->camera->init();
        this->magie->init();
        this->lastTick = std::chrono::steady_clock::now();
        this->tickCycle = 0;
        this->day = true;
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    
    
    void Game::cleanup() {
    }
    
    
    bool Game::tick() {
        static constexpr double TICK_PER_MS = 1. / ConfigManager::TICK_PER_SEC * 1000.;
        
        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        double duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - this->lastTick).count();
        
        if (duration >= TICK_PER_MS) {
            this->lastTick = now;
            this->tickCycle = (this->tickCycle + 1) % ConfigManager::TICK_CYCLE;
            this->tickSecond = (this->tickSecond + 1) % ConfigManager::TICK_PER_SEC;
            if (this->tickCycle == ConfigManager::DUSK_END || this->tickCycle == ConfigManager::DAWN_END) {
                this->day = !this->day;
            }
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
        this->magie->update();
    }
    
    
    void Game::render() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glDisable(GL_DEPTH_TEST);
        this->skybox->render();
        glEnable(GL_DEPTH_TEST);
        this->sun->render();
        glClear(GL_DEPTH_BUFFER_BIT);

        this->chunkManager->render();
        this->magie->render();
        if (this->configManager->getDebug()) {
            this->debug->render();
        }
        if(this->configManager->getScore()){
            this->score->render();
        }

        this->windowManager->refresh();
    }
    
    
    void Game::switchDay() {
        this->day = !this->day;
    }
    
    
    bool Game::isDay() {
        return this->day;
    }
    
    
    void Game::stop() {
        this->running = false;
    }
    
    
    bool Game::isRunning() {
        return this->running;
    }
}
