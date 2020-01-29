#include <mastercraft/game/Game.hpp>
#include <mastercraft/entity/Slime.hpp>


using namespace mastercraft;

int main(int argc, char **argv) {
    game::Game *game = game::Game::getInstance();
    game->init();
    
    while (game->isRunning()) {
        game->update();
        game->render();
    }
    
    game->cleanup();
    
    return EXIT_SUCCESS;
}

