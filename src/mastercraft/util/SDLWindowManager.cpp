#include <iostream>

#include <mastercraft/util/SDLWindowManager.hpp>


namespace mastercraft::util {
    
    SDLWindowManager::SDLWindowManager(const char *title) {
        if (0 != SDL_Init(SDL_INIT_VIDEO)) {
            std::cerr << SDL_GetError() << std::endl;
            return;
        }
        
        this->window = SDL_CreateWindow(
            "Mastercraft", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0,
            SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP
        );
        if (this->window == nullptr) {
            std::cerr << SDL_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }
        
        this->context = SDL_GL_CreateContext(this->window);
        if (this->context == nullptr) {
            std::cerr << SDL_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    
    
    SDLWindowManager::~SDLWindowManager() {
        SDL_DestroyWindow(this->window);
        SDL_GL_DeleteContext(this->context);
    }
    
    
    bool SDLWindowManager::pollEvent(SDL_Event &e) {
        return SDL_PollEvent(&e);
    }
    
    
    int SDLWindowManager::getWidth() const {
        SDL_DisplayMode mode;
        
        if (SDL_GetDesktopDisplayMode(0, &mode)) {
            std::cerr << SDL_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }
    
        return mode.w;
    }
    
    
    int SDLWindowManager::getHeight() const {
        SDL_DisplayMode mode;
    
        if (SDL_GetDesktopDisplayMode(0, &mode)) {
            std::cerr << SDL_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }
    
        return mode.h;
    }
    
    
    bool SDLWindowManager::isKeyPressed(SDL_Scancode key) const {
        return SDL_GetKeyboardState(nullptr)[key];
    }
    
    
    bool SDLWindowManager::isMouseButtonPressed(uint32_t button) const {
        return SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(button);
    }
    
    
    glm::ivec2 SDLWindowManager::getMousePosition() const {
        glm::ivec2 mousePos;
        SDL_GetMouseState(&mousePos.x, &mousePos.y);
        return mousePos;
    }
    
    
    void SDLWindowManager::refresh() {
        SDL_GL_SwapWindow(this->window);
    }
}
