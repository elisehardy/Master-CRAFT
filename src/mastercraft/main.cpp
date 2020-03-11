#include <mastercraft/game/Game.hpp>
#include <chrono>


using namespace mastercraft;


int main(int argc, char **argv) {
    std::chrono::steady_clock::time_point cmptStart, limiterStart, now;
    double duration;
    GLuint fps = 0;
    
    game::Game *game = game::Game::getInstance();
    game->init();
    game->camera->init2();
    game->magie->init();
    cmptStart = std::chrono::steady_clock::now();
    limiterStart = cmptStart;
    while (game->isRunning()) {
        
        game->update();

        if (game->configManager->getFramerate() > 0) { // Capped framerate
            now = std::chrono::steady_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(now - limiterStart).count();
            if (duration >= game->configManager->getFramerateInv()) {
                game->render();
                limiterStart = now;
                fps++;
            }
        }
        else { // Uncapped framerate
            game->render();
            fps++;
        }
        
        // Computing FPS
        now = std::chrono::steady_clock::now();
        duration = std::chrono::duration_cast<std::chrono::seconds>(now - cmptStart).count();
        if (duration >= 1.) {
            game->stats.fps = static_cast<GLuint>(fps);
            fps = 0;
            cmptStart = now;
        }



        for(auto &entity: game->chunkManager->entities){
            if(entity->getType() == 1){
                if(entity->isTouch(game->camera->getSphereDual())){
                    std::cout << " ARGG " << std::endl;

                    game->score->life2--;
                    break;

                }
            }
            if (game->camera->isTouch(entity->getSphereDual())) {
                std::cout << " AIE " << std::endl;

                game->score->removeLife(entity->getType());

                break;
            } else {
                std::cout << " RATE2 " << std::endl;

            }
        }
    }





    game->cleanup();
    
    return EXIT_SUCCESS;
}

