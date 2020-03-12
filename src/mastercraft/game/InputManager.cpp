#include <mastercraft/game/InputManager.hpp>
#include <mastercraft/game/Game.hpp>
#include <iostream>
#include <c3ga/Mvec.hpp>


namespace mastercraft::game {
    
    InputManager::InputManager() {
    }
    
    
    bool InputManager::isKeyPressed(SDL_Scancode key) {
        return SDL_GetKeyboardState(nullptr)[key];
    }
    
    
    void InputManager::handleMouseMotion(const SDL_MouseMotionEvent &event) {
        Game *game = Game::getInstance();
        //game->camera->rotateUp(-event.yrel);
        game->camera->rotateLeft(-event.xrel);
        game->magie->rotateLeft(-event.xrel);
        //game->magie->rotateUp(-event.yrel);


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
            game->magie->moveForward(0.6f);
            game->camera->init2();



        }
        if (InputManager::isKeyPressed(SDL_SCANCODE_S) || InputManager::isKeyPressed(SDL_SCANCODE_DOWN)) {
            game->camera->moveForward(-0.6f);
            game->magie->moveForward(-0.6f);
            game->camera->init2();


        }
        if (InputManager::isKeyPressed(SDL_SCANCODE_A) || InputManager::isKeyPressed(SDL_SCANCODE_LEFT)) {
            game->camera->moveLeft(0.6f);
            game->magie->moveLeft(0.6f);
            game->camera->init2();

        }
        if (InputManager::isKeyPressed(SDL_SCANCODE_D) || InputManager::isKeyPressed(SDL_SCANCODE_RIGHT)) {
            game->camera->moveLeft(-0.6f);
            game->magie->moveLeft(-0.6f);
            game->camera->init2();

        }
        if (InputManager::isKeyPressed(SDL_SCANCODE_LCTRL)) {
            if(game->configManager->getCheat()) {
                game->camera->moveUp(-0.6f);
                game->magie->moveUp(-0.6f);
            }
        }
        if (InputManager::isKeyPressed(SDL_SCANCODE_SPACE)) {
            if(game->configManager->getCheat()) {
                game->camera->moveUp(0.6f);
                game->magie->moveUp(0.6f);
            }
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
            if(game->configManager->getScore()){
                game->configManager->switchScore();
            }
            game->configManager->switchDebug();
        }
        if(InputManager::isKeyPressed(SDL_SCANCODE_K)){
            if(game->configManager->getDebug()) {
                game->configManager->switchDebug();
            }
            game->configManager->switchScore();
        }
        if(InputManager::isKeyPressed(SDL_SCANCODE_C)){
            game->configManager->switchCheat();

        }
        
        if (InputManager::isKeyPressed(SDL_SCANCODE_E)) {
            if (game->isDay()) {
                game->tickCycle = ConfigManager::DUSK_END;
            } else {
                game->tickCycle = ConfigManager::DAWN_END;
            }
            game->switchDay();
        }
        if (InputManager::isKeyPressed(SDL_SCANCODE_T)) {
            std::cout << "tir" << std::endl;
            int ind=0;
            std::vector<int> toDelete;

            for(auto &entity: game->chunkManager->entities){
                    auto oldPos = game->magie->getPosition();
                    for(int i=0;i<10;i++) {
                        auto newPos = oldPos;
                        game->magie->setPosition(newPos.x, newPos.y, newPos.z-0.6f*i);
                        if (game->magie->isTouch(entity->getSphereDual())) {
                            std::cout << " BUT BUT " << std::endl;

                            game->magie->setPosition(oldPos.x, oldPos.y, oldPos.z);
                            game->score->addMonsterKill(entity->getType());
                            toDelete.push_back(ind);


                            break;
                        } else {
                            std::cout << " RATE " << std::endl;

                        }
                        game->magie->setPosition(oldPos.x, oldPos.y, oldPos.z);
                    }
                    ind++;

            }
            int  i = 0;
            for (const auto &index: toDelete) {
                game->chunkManager->entities.erase(game->chunkManager->entities.begin() + index - i++);
            }



        }

        }
    
    
    void InputManager::handleHeldMouseButton() {
    }
    
    
    void InputManager::handleHeldKey() {
    }
}
