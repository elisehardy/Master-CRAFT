#include <mastercraft/game/Game.hpp>
#include <chrono>


using namespace mastercraft;


int main(int argc, char **argv) {
    std::chrono::steady_clock::time_point start;
    GLint64 elapsed;
    
    game::Game *game = game::Game::getInstance();
    
    game->init();
    
    while (game->isRunning()) {
        start = std::chrono::steady_clock::now();
        
        game->update();
        game->render();
        
        elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::steady_clock::now() - start
        ).count();
        
        game->stats.fps = static_cast<GLuint>(10e9 / elapsed);
    }
    
    game->cleanup();
    
    return EXIT_SUCCESS;
}

