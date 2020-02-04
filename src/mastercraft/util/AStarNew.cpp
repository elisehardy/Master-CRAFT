<<<<<<< HEAD
#include <glm/gtx/hash.hpp>
#include <mastercraft/util/AStarNew.hpp>
#include <mastercraft/game/Game.hpp>
#include <utility>
#include <unordered_set>
#include <hwloc.h>
=======

#include <mastercraft/util/AStarNew.hpp>
#include <utility>
>>>>>>> b133593bc9f327543a60456083f197dded6d4a87

using namespace mastercraft::util;

bool cell::compare(double self, double other) {
<<<<<<< HEAD
    std::cout << other << " " << self << std::endl;
    return (std::abs(self - other) < 1);
}

bool cell::sameChunk(glm::vec3 pos1, glm::vec3 pos2) {
    game::Game *game = game::Game::getInstance();
    return game->chunkManager->getSuperChunkCoordinates(pos1)
           == game->chunkManager->getSuperChunkCoordinates(pos2);
}

bool cell::isUnBlocked(int x, int y, int posZ) {
    game::Game *game = game::Game::getInstance();

    if (game->chunkManager->get(x, posZ + 1, y) == cube::CubeType::AIR) {
        return true;
    }
    if (game->chunkManager->get(x, posZ + 2, y) == cube::CubeType::AIR) {
        return true;
    } else {
=======
    return (std::abs(self - other) < 0.0001);
}

bool cell::isIntoWorld(int x, int y){
    return (x >= 0) && (y >= 0) && (x < ROW) && (y < COL);
}

bool cell::isUnBlocked(cube::SuperChunk *chunk, int x, int y, int posZ){
    if (chunk->get(x, posZ+1, y) == cube::CubeType::AIR){
        return true;
    }
    if(chunk->get(x,posZ+2, y) == cube::CubeType::AIR){
        return true;
    }
    else {
>>>>>>> b133593bc9f327543a60456083f197dded6d4a87
        return false;
    }
}

<<<<<<< HEAD
bool cell::isDestination(int x, int z, glm::vec3 dest) {
    return (abs(x - dest.x) < 1 && abs(z - dest.z) < 1);
}

double cell::CalculateHeuristic(int x, int y, glm::vec3 dest) {
    return abs(x - dest.x) + abs(y - dest.y);
}

std::stack<glm::dvec4> cell::tracePath(cell cellDetails[][COL], glm::vec3 dest) {
    printf("\nThe Path is ");
    int row = dest.x;
    int col = dest.z;
    int height = dest.y;

    std::stack<glm::dvec4> Path;

    while (!(cellDetails[row][col].parent_i == row
             && cellDetails[row][col].parent_j == col)) {
        Path.push(glm::dvec4(row, height, col, 0));
=======
bool cell::isDestination(int x, int y, triplet<int, int, int> dest){
    return (x == dest.first && y == dest.second);
}

double cell::CalculateHeuristic(int x, int y, triplet<int, int, int> dest){
    return abs(x - dest.first) + abs(y - dest.second);
}

void cell::tracePath(cell cellDetails[][COL], triplet<int, int, int> dest){
    printf ("\nThe Path is ");
    int row = dest.first;
    int col = dest.second;
    int height = dest.third;

    std::stack<triplet<int, int, int>> Path;

    while (!(cellDetails[row][col].parent_i == row
             && cellDetails[row][col].parent_j == col ))
    {
        Path.push (triplet<int, int, int>(row, col, height));
>>>>>>> b133593bc9f327543a60456083f197dded6d4a87
        row = cellDetails[row][col].parent_i;
        col = cellDetails[row][col].parent_j;
        height = cellDetails[row][col].parent_h;
    }

<<<<<<< HEAD
    Path.push(glm::dvec4(row, height, col, 0));
    return Path;
    /*  while (!Path.empty())
      {
          triplet<int,int,int> p = Path.top();
          Path.pop();
          printf("-> (%d,%d,%d) ",p.first,p.second, p.third);
      }

      return;*/
}


std::stack<glm::dvec4> cell::aStarSearch(glm::vec3 src, glm::vec3 dest) {
    game::Game *game = game::Game::getInstance();
    if (!(cell::sameChunk(src, src))) {
        printf("Source is invalid\n");
        return std::stack<glm::dvec4>();
    }
    if (!(cell::sameChunk(dest, src))) {
        printf("Destination is invalid\n");
        return std::stack<glm::dvec4>();
    }

    if (!(cell::isUnBlocked(src.x, src.z, src.y)) ||
        !(cell::isUnBlocked(dest.x, dest.z, dest.y))) {
        printf("Source or the destination is blocked\n");
        return std::stack<glm::dvec4>();
    }

    if (cell::isDestination(src.x, src.z, dest)) {
        printf("We are already at the destination\n");
        return std::stack<glm::dvec4>();
    }

    //auto v = game->chunkManager->getSuperChunkCoordinates(src)
   bool closedList[ROW][COL];
    std::memset(closedList, false, sizeof(closedList));
=======
    Path.push (triplet<int, int, int>(row, col, height));
    while (!Path.empty())
    {
        triplet<int,int,int> p = Path.top();
        Path.pop();
        printf("-> (%d,%d,%d) ",p.first,p.second, p.third);
    }

    return;
}


void cell::aStarSearch(game::Game *game,cube::SuperChunk*chunk, triplet<int, int, int> src, triplet<int, int, int> dest)
{
    if (!(cell::isIntoWorld (src.first, src.second))){
        printf ("Source is invalid\n");
        return;
    }

    if (!(cell::isIntoWorld (dest.first, dest.second))){
        printf ("Destination is invalid\n");
        return;
    }

    if (!(cell::isUnBlocked(chunk, src.first, src.second, src.third)) ||
        !(cell::isUnBlocked(chunk, dest.first, dest.second, dest.third))){
        printf ("Source or the destination is blocked\n");
        return;
    }

    if (cell::isDestination(src.first, src.second, dest)){
        printf ("We are already at the destination\n");
        return;
    }

    bool closedList[ROW][COL];
    std::memset(closedList, false, sizeof (closedList));
>>>>>>> b133593bc9f327543a60456083f197dded6d4a87

    cell cellDetails[ROW][COL];

    int i, j, k;

<<<<<<< HEAD
    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
=======
    for (i=0; i<ROW; i++){
        for (j=0; j<COL; j++){
>>>>>>> b133593bc9f327543a60456083f197dded6d4a87
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
            cellDetails[i][j].parent_h = -1;
        }
    }

<<<<<<< HEAD
    i = src.x, j = src.z, k = src.y;
=======
    i = src.first, j = src.second, k = src.third;
>>>>>>> b133593bc9f327543a60456083f197dded6d4a87
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;
    cellDetails[i][j].parent_h = k;

<<<<<<< HEAD
    std::unordered_set<glm::dvec4> openList;
    openList.insert(glm::dvec4(i, k, j, 0.0));
    bool foundDest = false;
    int max = 0;
    while (!openList.empty()&& max < 500) {
        max++;
        glm::dvec4 p = *openList.begin();

        openList.erase(openList.begin());

        i = p.x;
        j = p.z;
        k = p.y;
=======
    std::set<ptriplet> openList;
    openList.insert(ptriplet (0.0, triplet<int, int, int>(i, j, k)));
    bool foundDest = false;

    while (!openList.empty())
    {
        ptriplet p = *openList.begin();

        openList.erase(openList.begin());

        i = p.second.first;
        j = p.second.second;
        k = p.second.third;
>>>>>>> b133593bc9f327543a60456083f197dded6d4a87
        closedList[i][j] = true;

        double gNew, hNew, fNew;

        //top
<<<<<<< HEAD
        std::cout << "top" << i-1 << " " << k << " " << j << std::endl;
        if (cell::sameChunk({i - 1, k, j}, src)) {
            std::cout << "top"  << std::endl;

            if (cell::isDestination(i - 1, j, dest)) {
                cellDetails[i - 1][j].parent_i = i;
                cellDetails[i - 1][j].parent_j = j;
                cellDetails[i - 1][j].parent_h = k;
                printf("The destination cell is found\n");
                auto path = cell::tracePath(cellDetails, dest);
                return path;
            } else if (!(closedList[i - 1][j]) &&
                       cell::isUnBlocked(i - 1, j, k)) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = cell::CalculateHeuristic(i - 1, j, dest);
                fNew = gNew + hNew;
                if (cell::compare(cellDetails[i - 1][j].f, FLT_MAX) ||
                    cellDetails[i - 1][j].f > fNew) {
                    openList.insert(glm::dvec4(i - 1,
                                               float(game->chunkManager->heightSimplex(
                                                       i - 1, j,
                                                       game::ConfigManager::GEN_MIN_HEIGHT,
                                                       game::ConfigManager::GEN_MAX_HEIGHT)),
                                              j, fNew));

                    cellDetails[i - 1][j].f = fNew;
                    cellDetails[i - 1][j].g = gNew;
                    cellDetails[i - 1][j].h = hNew;
                    cellDetails[i - 1][j].parent_i = i;
                    cellDetails[i - 1][j].parent_j = j;
                    cellDetails[i - 1][j].parent_h = k;
=======

        if (cell::isIntoWorld(i-1, j)){

            if (cell::isDestination(i-1, j, dest)){
                cellDetails[i-1][j].parent_i = i;
                cellDetails[i-1][j].parent_j = j;
                cellDetails[i-1][j].parent_h = k;
                printf ("The destination cell is found\n");
                cell::tracePath (cellDetails, dest);
                return;
            }
            else if (!(closedList[i-1][j]) &&
                     cell::isUnBlocked(chunk, i-1, j, k)){
                gNew = cellDetails[i][j].g + 1.0;
                hNew = cell::CalculateHeuristic (i-1, j, dest);
                fNew = gNew + hNew;
                if (cell::compare(cellDetails[i-1][j].f , FLT_MAX) ||
                    cellDetails[i-1][j].f > fNew){
                    openList.insert( ptriplet(fNew,triplet<int, int, int>(i-1, j, game->chunkManager->heightSimplex(
                                                       i-1 , j , game::ConfigManager::GEN_MIN_HEIGHT, game::ConfigManager::GEN_MAX_HEIGHT))));

                    cellDetails[i-1][j].f = fNew;
                    cellDetails[i-1][j].g = gNew;
                    cellDetails[i-1][j].h = hNew;
                    cellDetails[i-1][j].parent_i = i;
                    cellDetails[i-1][j].parent_j = j;
                    cellDetails[i-1][j].parent_h = k;
>>>>>>> b133593bc9f327543a60456083f197dded6d4a87
                }
            }
        }

        //bottom
<<<<<<< HEAD
        std::cout << "bottom" << i+1 << " " << k << " " << j << std::endl;

        if (cell::sameChunk({i + 1, k, j}, src)) {
            std::cout << "bottom" << std::endl;

            if (cell::isDestination(i + 1, j, dest)) {
                cellDetails[i + 1][j].parent_i = i;
                cellDetails[i + 1][j].parent_j = j;
                cellDetails[i + 1][j].parent_h = k;
                printf("The destination cell is found\n");
                auto path = cell::tracePath(cellDetails, dest);
                return path;
            } else if (!(closedList[i + 1][j]) &&
                       cell::isUnBlocked(i + 1, j, k)) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = cell::CalculateHeuristic(i + 1, j, dest);
                fNew = gNew + hNew;

                if (cell::compare(cellDetails[i + 1][j].f, FLT_MAX) ||
                    cellDetails[i + 1][j].f > fNew) {
                    openList.insert(glm::dvec4(i + 1,
                                               float(game->chunkManager->heightSimplex(
                                                       i + 1, j,
                                                       game::ConfigManager::GEN_MIN_HEIGHT,
                                                       game::ConfigManager::GEN_MAX_HEIGHT
                                               )), j, fNew));
                    cellDetails[i + 1][j].f = fNew;
                    cellDetails[i + 1][j].g = gNew;
                    cellDetails[i + 1][j].h = hNew;
                    cellDetails[i + 1][j].parent_i = i;
                    cellDetails[i + 1][j].parent_j = j;
                    cellDetails[i + 1][j].parent_h = k;
=======

        if (cell::isIntoWorld(i+1, j)){
            if (cell::isDestination(i+1, j, dest)){
                cellDetails[i+1][j].parent_i = i;
                cellDetails[i+1][j].parent_j = j;
                cellDetails[i+1][j].parent_h = k;
                printf("The destination cell is found\n");
                cell::tracePath(cellDetails, dest);
                return;
            }
            else if (!(closedList[i+1][j]) &&
                     cell::isUnBlocked(chunk, i+1, j, k)){
                gNew = cellDetails[i][j].g + 1.0;
                hNew = cell::CalculateHeuristic(i+1, j, dest);
                fNew = gNew + hNew;

                if (cell::compare(cellDetails[i+1][j].f, FLT_MAX) ||
                    cellDetails[i+1][j].f > fNew){
                    openList.insert( ptriplet (fNew, triplet<int, int ,int> (i+1, j, game->chunkManager->heightSimplex(
                            i+1 , j , game::ConfigManager::GEN_MIN_HEIGHT, game::ConfigManager::GEN_MAX_HEIGHT
                    ))));
                    cellDetails[i+1][j].f = fNew;
                    cellDetails[i+1][j].g = gNew;
                    cellDetails[i+1][j].h = hNew;
                    cellDetails[i+1][j].parent_i = i;
                    cellDetails[i+1][j].parent_j = j;
                    cellDetails[i+1][j].parent_h = k;
>>>>>>> b133593bc9f327543a60456083f197dded6d4a87

                }
            }
        }

        //right
<<<<<<< HEAD
        std::cout << "right" << i << " " << k << " " << j+1 << std::endl;

        if (cell::sameChunk({i, k, j + 1}, src)) {
            std::cout << "right"  << std::endl;

            if (cell::isDestination(i, j + 1, dest)) {
                cellDetails[i][j + 1].parent_i = i;
                cellDetails[i][j + 1].parent_j = j;
                cellDetails[i][j + 1].parent_h = k;
                printf("The destination cell is found\n");
                auto path = cell::tracePath(cellDetails, dest);
                return path;
            } else if (!(closedList[i][j + 1]) &&
                       cell::isUnBlocked(i, j + 1, k)) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = cell::CalculateHeuristic(i, j + 1, dest);
                fNew = gNew + hNew;

                if (cell::compare(cellDetails[i][j + 1].f, FLT_MAX) ||
                    cellDetails[i][j + 1].f > fNew) {
                    openList.insert(glm::dvec4(i,
                                               float(game->chunkManager->heightSimplex(
                                                       i, j + 1,
                                                       game::ConfigManager::GEN_MIN_HEIGHT,
                                                       game::ConfigManager::GEN_MAX_HEIGHT)), j+1,
                                               fNew));

                    cellDetails[i][j + 1].f = fNew;
                    cellDetails[i][j + 1].g = gNew;
                    cellDetails[i][j + 1].h = hNew;
                    cellDetails[i][j + 1].parent_i = i;
                    cellDetails[i][j + 1].parent_j = j;
                    cellDetails[i][j + 1].parent_h = k;
=======

        if (cell::isIntoWorld (i, j+1)){

            if (cell::isDestination(i, j+1, dest)){
                cellDetails[i][j+1].parent_i = i;
                cellDetails[i][j+1].parent_j = j;
                cellDetails[i][j+1].parent_h = k;
                printf("The destination cell is found\n");
                cell::tracePath(cellDetails, dest);
                return;
            }
            else if (!(closedList[i][j+1]) &&
                     cell::isUnBlocked (chunk, i, j+1, k)){
                gNew = cellDetails[i][j].g + 1.0;
                hNew = cell::CalculateHeuristic (i, j+1, dest);
                fNew = gNew + hNew;

                if (cell::compare(cellDetails[i][j+1].f , FLT_MAX) ||
                    cellDetails[i][j+1].f > fNew){
                    openList.insert( ptriplet(fNew,triplet<int, int, int> (i, j+1, game->chunkManager->heightSimplex(
                                                       i , j+1 , game::ConfigManager::GEN_MIN_HEIGHT, game::ConfigManager::GEN_MAX_HEIGHT))));

                    cellDetails[i][j+1].f = fNew;
                    cellDetails[i][j+1].g = gNew;
                    cellDetails[i][j+1].h = hNew;
                    cellDetails[i][j+1].parent_i = i;
                    cellDetails[i][j+1].parent_j = j;
                    cellDetails[i][j+1].parent_h = k;
>>>>>>> b133593bc9f327543a60456083f197dded6d4a87

                }
            }
        }

        //left
<<<<<<< HEAD
        std::cout << "left" << i << " " << k << " " << j-1 << std::endl;

        if (cell::sameChunk({i, k, j - 1}, src)) {
            std::cout << "left" <<  std::endl;

            if (cell::isDestination(i, j - 1, dest)) {
                cellDetails[i][j - 1].parent_i = i;
                cellDetails[i][j - 1].parent_j = j;
                cellDetails[i][j - 1].parent_h = k;
                printf("The destination cell is found\n");
                auto path = cell::tracePath(cellDetails, dest);
                return path;
            } else if (!(closedList[i][j - 1]) &&
                       cell::isUnBlocked(i, j - 1, k)) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = cell::CalculateHeuristic(i, j - 1, dest);
                fNew = gNew + hNew;

                if (cell::compare(cellDetails[i][j - 1].f, FLT_MAX) ||
                    cellDetails[i][j - 1].f > fNew) {
                    openList.insert(glm::dvec4(i,
                                               float(game->chunkManager->heightSimplex(
                                                       i, j - 1,
                                                       game::ConfigManager::GEN_MIN_HEIGHT,
                                                       game::ConfigManager::GEN_MAX_HEIGHT)),
                                               j-1,fNew));

                    cellDetails[i][j - 1].f = fNew;
                    cellDetails[i][j - 1].g = gNew;
                    cellDetails[i][j - 1].h = hNew;
                    cellDetails[i][j - 1].parent_i = i;
                    cellDetails[i][j - 1].parent_j = j;
                    cellDetails[i][j - 1].parent_h = k;
=======

        if (cell::isIntoWorld(i, j-1)){

            if (cell::isDestination(i, j-1, dest)){
                cellDetails[i][j-1].parent_i = i;
                cellDetails[i][j-1].parent_j = j;
                cellDetails[i][j-1].parent_h = k;
                printf("The destination cell is found\n");
                cell::tracePath(cellDetails, dest);
                return;
            }
            else if (!(closedList[i][j-1]) &&
                     cell::isUnBlocked(chunk, i, j-1, k)){
                gNew = cellDetails[i][j].g + 1.0;
                hNew = cell::CalculateHeuristic(i, j-1, dest);
                fNew = gNew + hNew;

                if (cell::compare(cellDetails[i][j-1].f , FLT_MAX) ||
                    cellDetails[i][j-1].f > fNew){
                    openList.insert( ptriplet (fNew,triplet<int, int, int>(i, j-1 ,game->chunkManager->heightSimplex(
                                                        i , j-1 , game::ConfigManager::GEN_MIN_HEIGHT, game::ConfigManager::GEN_MAX_HEIGHT))));

                    cellDetails[i][j-1].f = fNew;
                    cellDetails[i][j-1].g = gNew;
                    cellDetails[i][j-1].h = hNew;
                    cellDetails[i][j-1].parent_i = i;
                    cellDetails[i][j-1].parent_j = j;
                    cellDetails[i][j-1].parent_h = k;
>>>>>>> b133593bc9f327543a60456083f197dded6d4a87

                }
            }
        }

        //top right
<<<<<<< HEAD
        std::cout << "top right" << i-1 << " " << k << " " << j+1 << std::endl;

        if (cell::sameChunk({i - 1, k, j + 1}, src)) {
            std::cout << "top right" << std::endl;

            if (cell::isDestination(i - 1, j + 1, dest)) {
                cellDetails[i - 1][j + 1].parent_i = i;
                cellDetails[i - 1][j + 1].parent_j = j;
                cellDetails[i - 1][j + 1].parent_h = k;
                printf("The destination cell is found\n");
                auto path = cell::tracePath(cellDetails, dest);
                return path;
            } else if (!(closedList[i - 1][j + 1]) &&
                       cell::isUnBlocked(i - 1, j + 1, k)) {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = cell::CalculateHeuristic(i - 1, j + 1, dest);
                fNew = gNew + hNew;


                if (cell::compare(cellDetails[i - 1][j + 1].f, FLT_MAX) ||
                    cellDetails[i - 1][j + 1].f > fNew) {
                    openList.insert(glm::dvec4(i - 1,
                                               float(game->chunkManager->heightSimplex(
                                                       i - 1, j + 1,
                                                       game::ConfigManager::GEN_MIN_HEIGHT,
                                                       game::ConfigManager::GEN_MAX_HEIGHT)),
                                              j+1, fNew));

                    cellDetails[i - 1][j + 1].f = fNew;
                    cellDetails[i - 1][j + 1].g = gNew;
                    cellDetails[i - 1][j + 1].h = hNew;
                    cellDetails[i - 1][j + 1].parent_i = i;
                    cellDetails[i - 1][j + 1].parent_j = j;
                    cellDetails[i - 1][j + 1].parent_h = k;
=======

        if (cell::isIntoWorld(i-1, j+1)){

            if (cell::isDestination(i-1, j+1, dest)){
                cellDetails[i-1][j+1].parent_i = i;
                cellDetails[i-1][j+1].parent_j = j;
                cellDetails[i-1][j+1].parent_h = k;
                printf ("The destination cell is found\n");
                cell::tracePath (cellDetails, dest);
                return;
            }


            else if (!(closedList[i-1][j+1]) &&
                     cell::isUnBlocked(chunk, i-1, j+1, k)){
                gNew = cellDetails[i][j].g + 1.414;
                hNew = cell::CalculateHeuristic(i-1, j+1, dest);
                fNew = gNew + hNew;


                if (cell::compare(cellDetails[i-1][j+1].f , FLT_MAX) ||
                    cellDetails[i-1][j+1].f > fNew){
                    openList.insert( ptriplet (fNew,triplet<int, int, int>(i-1, j+1,game->chunkManager->heightSimplex(
                                                        i-1 , j+1 , game::ConfigManager::GEN_MIN_HEIGHT, game::ConfigManager::GEN_MAX_HEIGHT))));

                    cellDetails[i-1][j+1].f = fNew;
                    cellDetails[i-1][j+1].g = gNew;
                    cellDetails[i-1][j+1].h = hNew;
                    cellDetails[i-1][j+1].parent_i = i;
                    cellDetails[i-1][j+1].parent_j = j;
                    cellDetails[i-1][j+1].parent_h = k;
>>>>>>> b133593bc9f327543a60456083f197dded6d4a87

                }
            }
        }

        //top left
<<<<<<< HEAD
        std::cout << "top left" << i-1 << " " << k << " " << j-1 << std::endl;

        if (cell::sameChunk({i - 1, k, j - 1}, src)) {
            std::cout << "top left" << std::endl;

            if (cell::isDestination(i - 1, j - 1, dest)) {
                cellDetails[i - 1][j - 1].parent_i = i;
                cellDetails[i - 1][j - 1].parent_j = j;
                cellDetails[i - 1][j - 1].parent_h = k;
                printf("The destination cell is found\n");
                auto path = cell::tracePath(cellDetails, dest);
                return path;
            } else if (!(closedList[i - 1][j - 1]) &&
                       cell::isUnBlocked(i - 1, j - 1, k)) {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = cell::CalculateHeuristic(i - 1, j - 1, dest);
                fNew = gNew + hNew;

                if (cell::compare(cellDetails[i - 1][j - 1].f, FLT_MAX) ||
                    cellDetails[i - 1][j - 1].f > fNew) {
                    openList.insert(glm::dvec4(i - 1,
                                               float(game->chunkManager->heightSimplex(
                                                       i - 1, j - 1,
                                                       game::ConfigManager::GEN_MIN_HEIGHT,
                                                       game::ConfigManager::GEN_MAX_HEIGHT)),
                                               j-1,fNew));

                    cellDetails[i - 1][j - 1].f = fNew;
                    cellDetails[i - 1][j - 1].g = gNew;
                    cellDetails[i - 1][j - 1].h = hNew;
                    cellDetails[i - 1][j - 1].parent_i = i;
                    cellDetails[i - 1][j - 1].parent_j = j;
                    cellDetails[i - 1][j - 1].parent_h = k;
=======

        if (cell::isIntoWorld (i-1, j-1)){

            if (cell::isDestination (i-1, j-1, dest)){
                cellDetails[i-1][j-1].parent_i = i;
                cellDetails[i-1][j-1].parent_j = j;
                cellDetails[i-1][j-1].parent_h = k;
                printf ("The destination cell is found\n");
                cell::tracePath (cellDetails, dest);
                return;
            }
            else if (!(closedList[i-1][j-1]) &&
                     cell::isUnBlocked(chunk, i-1, j-1, k)){
                gNew = cellDetails[i][j].g + 1.414;
                hNew = cell::CalculateHeuristic(i-1, j-1, dest);
                fNew = gNew + hNew;

                if (cell::compare(cellDetails[i-1][j-1].f , FLT_MAX) ||
                    cellDetails[i-1][j-1].f > fNew){
                    openList.insert( ptriplet (fNew, triplet<int, int, int> (i-1, j-1, game->chunkManager->heightSimplex(
                            i-1 , j-1 , game::ConfigManager::GEN_MIN_HEIGHT, game::ConfigManager::GEN_MAX_HEIGHT))));

                    cellDetails[i-1][j-1].f = fNew;
                    cellDetails[i-1][j-1].g = gNew;
                    cellDetails[i-1][j-1].h = hNew;
                    cellDetails[i-1][j-1].parent_i = i;
                    cellDetails[i-1][j-1].parent_j = j;
                    cellDetails[i-1][j-1].parent_h = k;
>>>>>>> b133593bc9f327543a60456083f197dded6d4a87

                }
            }
        }

        //bottom right
<<<<<<< HEAD
        std::cout << "bottom roght" << i+1 << " " << k << " " << j+1 << std::endl;

        if (cell::sameChunk({i + 1, k, j + 1}, src)) {
            std::cout << "bottom roght"  << std::endl;

            if (cell::isDestination(i + 1, j + 1, dest)) {
                cellDetails[i + 1][j + 1].parent_i = i;
                cellDetails[i + 1][j + 1].parent_j = j;
                cellDetails[i + 1][j + 1].parent_h = k;

                printf("The destination cell is found\n");
                auto path = cell::tracePath(cellDetails, dest);
                return path;
            } else if (!(closedList[i + 1][j + 1]) &&
                       cell::isUnBlocked(i + 1, j + 1, k)) {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = cell::CalculateHeuristic(i + 1, j + 1, dest);
                fNew = gNew + hNew;

                if (cell::compare(cellDetails[i + 1][j + 1].f, FLT_MAX) ||
                    cellDetails[i + 1][j + 1].f > fNew) {
                    openList.insert(glm::dvec4(i + 1,
                                               float(game->chunkManager->heightSimplex(
                                                       i + 1, j + 1,
                                                       game::ConfigManager::GEN_MIN_HEIGHT,
                                                       game::ConfigManager::GEN_MAX_HEIGHT)),
                                              j+1, fNew));

                    cellDetails[i + 1][j + 1].f = fNew;
                    cellDetails[i + 1][j + 1].g = gNew;
                    cellDetails[i + 1][j + 1].h = hNew;
                    cellDetails[i + 1][j + 1].parent_i = i;
                    cellDetails[i + 1][j + 1].parent_j = j;
                    cellDetails[i + 1][j + 1].parent_h = k;
=======

        if (cell::isIntoWorld(i+1, j+1)){

            if (cell::isDestination(i+1, j+1, dest)){
                cellDetails[i+1][j+1].parent_i = i;
                cellDetails[i+1][j+1].parent_j = j;
                cellDetails[i+1][j+1].parent_h = k;

                printf ("The destination cell is found\n");
                cell::tracePath (cellDetails, dest);
                return;
            }
            else if (!(closedList[i+1][j+1]) &&
                     cell::isUnBlocked(chunk, i+1, j+1, k)){
                gNew = cellDetails[i][j].g + 1.414;
                hNew = cell::CalculateHeuristic(i+1, j+1, dest);
                fNew = gNew + hNew;

                if (cell::compare(cellDetails[i+1][j+1].f , FLT_MAX) ||
                    cellDetails[i+1][j+1].f > fNew){
                    openList.insert(ptriplet(fNew,triplet<int, int, int> (i+1, j+1, game->chunkManager->heightSimplex(
                                                      i+1 , j+1 , game::ConfigManager::GEN_MIN_HEIGHT, game::ConfigManager::GEN_MAX_HEIGHT))));

                    cellDetails[i+1][j+1].f = fNew;
                    cellDetails[i+1][j+1].g = gNew;
                    cellDetails[i+1][j+1].h = hNew;
                    cellDetails[i+1][j+1].parent_i = i;
                    cellDetails[i+1][j+1].parent_j = j;
                    cellDetails[i+1][j+1].parent_h = k;
>>>>>>> b133593bc9f327543a60456083f197dded6d4a87

                }
            }
        }

        //bottom left
<<<<<<< HEAD
        std::cout << "bottom left" << i+1 << " " << k << " " << j-1 << std::endl;

        if (cell::sameChunk({i + 1, k, j - 1}, src)) {
            std::cout << "bottom left"  << std::endl;

            if (cell::isDestination(i + 1, j - 1, dest)) {
                cellDetails[i + 1][j - 1].parent_i = i;
                cellDetails[i + 1][j - 1].parent_j = j;
                cellDetails[i + 1][j - 1].parent_h = k;

                printf("The destination cell is found\n");
                auto path = cell::tracePath(cellDetails, dest);
                return path;
            } else if (!(closedList[i + 1][j - 1]) &&
                       cell::isUnBlocked(i + 1, j - 1, k)) {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = cell::CalculateHeuristic(i + 1, j - 1, dest);
                fNew = gNew + hNew;

                if (cell::compare(cellDetails[i + 1][j - 1].f, FLT_MAX) ||
                    cellDetails[i + 1][j - 1].f > fNew) {
                    openList.insert(glm::dvec4(i + 1,
                                               float(game->chunkManager->heightSimplex(
                                                       i + 1, j - 1,
                                                       game::ConfigManager::GEN_MIN_HEIGHT,
                                                       game::ConfigManager::GEN_MAX_HEIGHT)),
                                              j-1, fNew));

                    cellDetails[i + 1][j - 1].f = fNew;
                    cellDetails[i + 1][j - 1].g = gNew;
                    cellDetails[i + 1][j - 1].h = hNew;
                    cellDetails[i + 1][j - 1].parent_i = i;
                    cellDetails[i + 1][j - 1].parent_j = j;
                    cellDetails[i + 1][j - 1].parent_h = k;
=======

        if (cell::isIntoWorld (i+1, j-1)){

            if (cell::isDestination(i+1, j-1, dest)){
                cellDetails[i+1][j-1].parent_i = i;
                cellDetails[i+1][j-1].parent_j = j;
                cellDetails[i+1][j-1].parent_h = k;

                printf("The destination cell is found\n");
                cell::tracePath(cellDetails, dest);
                return;
            }
            else if (!(closedList[i+1][j-1]) &&
                     cell::isUnBlocked(chunk, i+1, j-1, k)){
                gNew = cellDetails[i][j].g + 1.414;
                hNew = cell::CalculateHeuristic(i+1, j-1, dest);
                fNew = gNew + hNew;

                if (cell::compare(cellDetails[i+1][j-1].f , FLT_MAX) ||
                    cellDetails[i+1][j-1].f > fNew){
                    openList.insert(ptriplet(fNew,triplet<int, int,int>(i+1, j-1, game->chunkManager->heightSimplex(
                                                      i+1 , j-1 , game::ConfigManager::GEN_MIN_HEIGHT, game::ConfigManager::GEN_MAX_HEIGHT))));

                    cellDetails[i+1][j-1].f = fNew;
                    cellDetails[i+1][j-1].g = gNew;
                    cellDetails[i+1][j-1].h = hNew;
                    cellDetails[i+1][j-1].parent_i = i;
                    cellDetails[i+1][j-1].parent_j = j;
                    cellDetails[i+1][j-1].parent_h = k;
>>>>>>> b133593bc9f327543a60456083f197dded6d4a87

                }
            }
        }
    }

    if (foundDest == false)
        printf("Failed to find the Destination Cell\n");

<<<<<<< HEAD
    return std::stack<glm::dvec4>();
}
=======
    return;
}

>>>>>>> b133593bc9f327543a60456083f197dded6d4a87
