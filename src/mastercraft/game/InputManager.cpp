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
    
        if (InputManager::isKeyPressed(SDL_SCANCODE_F1)) {
            game->configManager->switchFaceCulling();
        }
        if (InputManager::isKeyPressed(SDL_SCANCODE_F2)) {
            game->configManager->switchOcclusionCulling();
            game->chunkManager->clearChunks();
        }
        if (InputManager::isKeyPressed(SDL_SCANCODE_F3)) {
            game->configManager->cycleFramerate();
        }
        if (InputManager::isKeyPressed(SDL_SCANCODE_F4)) {
            game->configManager->decDistanceView();
        }
        if (InputManager::isKeyPressed(SDL_SCANCODE_F5)) {
            game->configManager->incDistanceView();
        }
        if (InputManager::isKeyPressed(SDL_SCANCODE_F10)) {
            game->configManager->switchDebug();
        }
        
        if (InputManager::isKeyPressed(SDL_SCANCODE_E)) {
            if (game->isDay()) {
                game->tickCycle = ConfigManager::TICK_DAY_END;
            } else {
                game->tickCycle = ConfigManager::TICK_DAY_START;
            }
            game->switchDay();
        }
    }
    
    
    void InputManager::handleHeldMouseButton() {
    }
    
    
    void InputManager::handleHeldKey() {
    }
}
