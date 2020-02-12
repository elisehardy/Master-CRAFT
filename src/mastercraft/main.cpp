#include <mastercraft/game/Game.hpp>
#include <chrono>


using namespace mastercraft;


int main(int argc, char **argv) {
    std::chrono::steady_clock::time_point cmptStart, limiterStart, now;
    double duration;
    GLuint fps = 0;
    
    game::Game *game = game::Game::getInstance();
    game->init();
    
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
            }
            fps++;
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
    }
    
    game->cleanup();
    
    return EXIT_SUCCESS;
}

