#include <iostream>

#include <glm/glm.hpp>
#include <SDL.h>

#include <mastercraft/game/WindowManager.hpp>
#include <mastercraft/game/Game.hpp>


namespace mastercraft::game {
    
    WindowManager::WindowManager(const char *title, uint32_t flags) {
        if (0 != SDL_Init(SDL_INIT_VIDEO)) {
            throw std::runtime_error(SDL_GetError());
        }
        
        this->window = SDL_CreateWindow(
            title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0,
            SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP
        );
        if (this->window == nullptr) {
            throw std::runtime_error(SDL_GetError());
        }
        
        this->context = SDL_GL_CreateContext(this->window);
        if (this->context == nullptr) {
            throw std::runtime_error(SDL_GetError());
        }
    }
    
    
    WindowManager::~WindowManager() {
        SDL_GL_DeleteContext(this->context);
        SDL_DestroyWindow(this->window);
    }
    
    
    void WindowManager::handleWindowEvent(const SDL_WindowEvent &event) {
        Game *game;
        
        if (event.windowID != SDL_GetWindowID(this->window)) {
            return;
        }
        
        switch (event.type) {
            case SDL_WINDOWEVENT_RESIZED:
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                game = Game::getInstance();
                game->camera->setProjectionMatrix(game->configManager->getFov(), event.data1, event.data2);
                break;
            
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                SDL_SetRelativeMouseMode(SDL_TRUE);
                break;
            
            case SDL_WINDOWEVENT_FOCUS_LOST:
                SDL_SetRelativeMouseMode(SDL_FALSE);
                break;
            
            case SDL_WINDOWEVENT_CLOSE:
                Game::getInstance()->stop();
                break;
        }
    }
    
    
    void WindowManager::refresh() {
        SDL_GL_SwapWindow(this->window);
    }
    
    
    SDL_DisplayMode WindowManager::getDisplayMode() const {
        SDL_DisplayMode mode;
        
        if (SDL_GetDesktopDisplayMode(0, &mode)) {
            throw std::runtime_error(SDL_GetError());
        }
        
        return mode;
    }
}
