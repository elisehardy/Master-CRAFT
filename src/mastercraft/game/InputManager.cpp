#include <mastercraft/game/InputManager.hpp>
#include <mastercraft/game/Game.hpp>
#include <iostream>


namespace mastercraft::game {
    
    InputManager::InputManager() {
    }
    
    
    bool InputManager::isKeyPressed(SDL_Scancode key) {
        return SDL_GetKeyboardState(nullptr)[key];
    }
    
    
    void InputManager::handleMouseMotion(const SDL_MouseMotionEvent &event) {
        Game *game = Game::getInstance();
        game->camera->rotateUp(-event.yrel);
        game->camera->rotateLeft(-event.xrel);
    }
    
    
    void InputManager::handleMouseButton(const SDL_MouseButtonEvent &event) {
    }
    
    
    void InputManager::handleMouseWheel(const SDL_MouseWheelEvent &event) {
    }
    
    
    void InputManager::handleKeyboard(const SDL_KeyboardEvent &event) {
        Game *game = Game::getInstance();
        
        if (InputManager::isKeyPressed(SDL_SCANCODE_ESCAPE)) {
              game->stop();
        }
        
        if (InputManager::isKeyPressed(SDL_SCANCODE_W) || InputManager::isKeyPressed(SDL_SCANCODE_UP)) {
            game->camera->moveForward(0.6f);
        }
        if (InputManager::isKeyPressed(SDL_SCANCODE_S) || InputManager::isKeyPressed(SDL_SCANCODE_DOWN)) {
            game->camera->moveForward(-0.6f);
        }
        if (InputManager::isKeyPressed(SDL_SCANCODE_A) || InputManager::isKeyPressed(SDL_SCANCODE_LEFT)) {
            game->camera->moveLeft(0.6f);
        }
        if (InputManager::isKeyPressed(SDL_SCANCODE_D) || InputManager::isKeyPressed(SDL_SCANCODE_RIGHT)) {
            game->camera->moveLeft(-0.6f);
        }
        if (InputManager::isKeyPressed(SDL_SCANCODE_LCTRL)) {
            game->camera->moveUp(-0.6f);
        }
        if (InputManager::isKeyPressed(SDL_SCANCODE_SPACE)) {
            game->camera->moveUp(0.6f);
        }
        
        
        if (InputManager::isKeyPressed(SDL_SCANCODE_E)) {
            game->configManager->switchDay();
        }
    }
    
    
    void InputManager::handleHeldMouseButton() {
    }
    
    
    void InputManager::handleHeldKey() {
    }
}
