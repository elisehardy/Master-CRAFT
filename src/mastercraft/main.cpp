#include <mastercraft/game/Game.hpp>

#include <mastercraft/util/AStarNew.hpp>
#include <mastercraft/game/ConfigManager.hpp>


using namespace mastercraft;
using namespace std;


int main(int argc, char **argv) {
    game::Game *game = game::Game::getInstance();


    game->init();
    
    while (game->isRunning()) {
        game->update();
        game->render();
    }
    
    game->cleanup();


    cube::SuperChunk *chunk = game->chunkManager->loadOrCreate(0, 0, 0);


    // Source is the left-most bottom-most corner

    util::triplet<int, int, int> src = util::triplet<int, int, int>(0, 0, 36);

    // Destination is the left-most top-most corner
    util::triplet<int ,int,int> dest = util::triplet<int, int, int>(2, 4, 39);

    util::cell::aStarSearch(game, chunk, src, dest);
    return EXIT_SUCCESS;
}


















