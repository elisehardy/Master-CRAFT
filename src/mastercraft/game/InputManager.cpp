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
            if(!game->configManager->getCheat()) {
                game->camera->init2();
            }


        }
        if (InputManager::isKeyPressed(SDL_SCANCODE_S) || InputManager::isKeyPressed(SDL_SCANCODE_DOWN)) {
            game->camera->moveForward(-0.6f);
            game->magie->moveForward(-0.6f);
            if(!game->configManager->getCheat()) {
                game->camera->init2();
            }

        }
        if (InputManager::isKeyPressed(SDL_SCANCODE_A) || InputManager::isKeyPressed(SDL_SCANCODE_LEFT)) {
            game->camera->moveLeft(0.6f);
            game->magie->moveLeft(0.6f);
            if(!game->configManager->getCheat()) {
                game->camera->init2();
            }
        }
        if (InputManager::isKeyPressed(SDL_SCANCODE_D) || InputManager::isKeyPressed(SDL_SCANCODE_RIGHT)) {
            game->camera->moveLeft(-0.6f);
            game->magie->moveLeft(-0.6f);
            if(!game->configManager->getCheat()) {
                game->camera->init2();
            }
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

        if (InputManager::isKeyPressed(SDL_SCANCODE_B)) {
            if(game->score->getMonster_kill() > 10) {


                int ind = 0;
                std::vector<int> toDelete;
                auto pos = game->camera->getPosition();
                auto sphere = game->camera->getSphereDual();
                auto D = scale(0.5);
                sphere = D * sphere * D.inv();
                sphere.roundZero(1.0e-10);
                auto pz = pos.z*5 - pos.z;
                auto py = pos.y*5-pos.y;
                auto px = pos.x*5-pos.x;
                auto T = translation(c3ga::Mvec<double>(c3ga::e3<double>()*-pz+c3ga::e2<double>()*-py+c3ga::e1<double>()*-px));
                sphere = T * sphere * T.inv();
                sphere.roundZero(1.0e-10);
                double rayon;
                c3ga::Mvec<double> center;
                radiusAndCenterFromDualSphere(sphere, rayon, center);
                for (auto &entity: game->chunkManager->entities) {
                    auto ent = entity->getPosition();
                    ent.x +=0.6f;
                    ent.z+=0.6f;
                    ent.y+=1;
                    if (game->magie->isTouch2(entity->getSphereDual(), sphere)|| game->camera->isCercle(ent, rayon)) {
                            game->score->addMonsterKill(entity->getType());
                            game->score->removeMonsterKill();
                            toDelete.push_back(ind);


                            break;
                        }

                    ind++;

                }

                int i = 0;
                for (const auto &index: toDelete) {
                    game->chunkManager->entities.erase(
                            game->chunkManager->entities.begin() + index - i++);
                }
            }
        }

        if (InputManager::isKeyPressed(SDL_SCANCODE_T)) {
            int ind=0;
            std::vector<int> toDelete;

            for(auto &entity: game->chunkManager->entities){
                auto sphere = game->magie->getSphereDual();

                for(int i=0;i<10;i++) {
                    auto T = translation(c3ga::Mvec<double>(c3ga::e3<double>()*(-0.6f*i)));
                    sphere = T*sphere*T.inv();
                    if (game->magie->isTouch2(entity->getSphereDual(), sphere)) {

                        game->score->addMonsterKill(entity->getType());
                        toDelete.push_back(ind);


                        break;
                    }
                }
                ind++;

            }


          /*  for(auto &entity: game->chunkManager->entities){
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

            }*/
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
