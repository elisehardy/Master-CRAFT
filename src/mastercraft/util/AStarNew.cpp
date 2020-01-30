#include <mastercraft/util/AStarNew.hpp>
#include <mastercraft/game/Game.hpp>
#include <utility>

using namespace mastercraft::util;

bool cell::compare(double self, double other) {
    return (std::abs(self - other) < 0.0001);
}

bool cell::isIntoWorld(int x, int y){
    return (x >= 0) && (y >= 0) && (x < ROW) && (y < COL);
}

bool cell::isUnBlocked(int x, int y, int posZ){
    game::Game *game = game::Game::getInstance();

    if (game->chunkManager->get(x, posZ+1, y) == cube::CubeType::AIR){
        return true;
    }
    if(game->chunkManager->get(x,posZ+2, y) == cube::CubeType::AIR){
        return true;
    }
    else {
        return false;
    }
}

bool cell::isDestination(int x, int y, glm::vec3 dest){
    return (abs(x - dest.x)<0.0001 && abs(y - dest.z))<0.0001;
}

double cell::CalculateHeuristic(int x, int y, glm::vec3 dest){
    return abs(x - dest.x) + abs(y - dest.y);
}

std::stack<glm::vec3> cell::tracePath(cell cellDetails[][COL], glm::vec3 dest){
    printf ("\nThe Path is ");
    int row = dest.x;
    int col = dest.z;
    int height = dest.y;

    std::stack<glm::vec3> Path;

    while (!(cellDetails[row][col].parent_i == row
             && cellDetails[row][col].parent_j == col ))
    {
        Path.push (glm::vec3(row, height, col));
        row = cellDetails[row][col].parent_i;
        col = cellDetails[row][col].parent_j;
        height = cellDetails[row][col].parent_h;
    }

    Path.push (glm::vec3(row, height, col));
    return Path;
  /*  while (!Path.empty())
    {
        triplet<int,int,int> p = Path.top();
        Path.pop();
        printf("-> (%d,%d,%d) ",p.first,p.second, p.third);
    }

    return;*/
}


std::stack<glm::vec3> cell::aStarSearch(glm::vec3 src, glm::vec3 dest)
{
    game::Game *game = game::Game::getInstance();
    if (!(cell::isIntoWorld (src.x, src.z))){
        printf ("Source is invalid\n");
        return std::stack<glm::vec3>();
    }

    if (!(cell::isIntoWorld (dest.x, dest.z))){
        printf ("Destination is invalid\n");
        return std::stack<glm::vec3>();
    }

    if (!(cell::isUnBlocked(src.x, src.y, src.z)) ||
        !(cell::isUnBlocked(dest.x, dest.y, dest.z))){
        printf ("Source or the destination is blocked\n");
        return std::stack<glm::vec3>();
    }

    if (cell::isDestination(src.x, src.z, dest)){
        printf ("We are already at the destination\n");
        return std::stack<glm::vec3>();
    }

    bool closedList[ROW][COL];
    std::memset(closedList, false, sizeof (closedList));

    cell cellDetails[ROW][COL];

    int i, j, k;

    for (i=0; i<ROW; i++){
        for (j=0; j<COL; j++){
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
            cellDetails[i][j].parent_h = -1;
        }
    }

    i = src.x, j = src.z, k = src.y;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;
    cellDetails[i][j].parent_h = k;

    std::set<ptriplet> openList;
    openList.insert(ptriplet (0.0, glm::vec3(i, k, j)));
    bool foundDest = false;

    while (!openList.empty())
    {
        ptriplet p = *openList.begin();

        openList.erase(openList.begin());

        i = p.second.x;
        j = p.second.z;
        k = p.second.y;
        closedList[i][j] = true;

        double gNew, hNew, fNew;

        //top

        if (cell::isIntoWorld(i-1, j)){

            if (cell::isDestination(i-1, j, dest)){
                cellDetails[i-1][j].parent_i = i;
                cellDetails[i-1][j].parent_j = j;
                cellDetails[i-1][j].parent_h = k;
                printf ("The destination cell is found\n");
                auto path = cell::tracePath (cellDetails, dest);
                return path;
            }
            else if (!(closedList[i-1][j]) &&
                     cell::isUnBlocked(i-1, j, k)){
                gNew = cellDetails[i][j].g + 1.0;
                hNew = cell::CalculateHeuristic (i-1, j, dest);
                fNew = gNew + hNew;
                if (cell::compare(cellDetails[i-1][j].f , FLT_MAX) ||
                    cellDetails[i-1][j].f > fNew){
                    openList.insert( ptriplet(fNew,glm::vec3(i-1, j, float(game->chunkManager->heightSimplex(
                                                       i-1 , j , game::ConfigManager::GEN_MIN_HEIGHT, game::ConfigManager::GEN_MAX_HEIGHT)))));

                    cellDetails[i-1][j].f = fNew;
                    cellDetails[i-1][j].g = gNew;
                    cellDetails[i-1][j].h = hNew;
                    cellDetails[i-1][j].parent_i = i;
                    cellDetails[i-1][j].parent_j = j;
                    cellDetails[i-1][j].parent_h = k;
                }
            }
        }

        //bottom

        if (cell::isIntoWorld(i+1, j)){
            if (cell::isDestination(i+1, j, dest)){
                cellDetails[i+1][j].parent_i = i;
                cellDetails[i+1][j].parent_j = j;
                cellDetails[i+1][j].parent_h = k;
                printf("The destination cell is found\n");
                auto path = cell::tracePath(cellDetails, dest);
                return path;
            }
            else if (!(closedList[i+1][j]) &&
                     cell::isUnBlocked(i+1, j, k)){
                gNew = cellDetails[i][j].g + 1.0;
                hNew = cell::CalculateHeuristic(i+1, j, dest);
                fNew = gNew + hNew;

                if (cell::compare(cellDetails[i+1][j].f, FLT_MAX) ||
                    cellDetails[i+1][j].f > fNew){
                    openList.insert( ptriplet (fNew, glm::vec3 (i+1, j, float(game->chunkManager->heightSimplex(
                            i+1 , j , game::ConfigManager::GEN_MIN_HEIGHT, game::ConfigManager::GEN_MAX_HEIGHT
                    )))));
                    cellDetails[i+1][j].f = fNew;
                    cellDetails[i+1][j].g = gNew;
                    cellDetails[i+1][j].h = hNew;
                    cellDetails[i+1][j].parent_i = i;
                    cellDetails[i+1][j].parent_j = j;
                    cellDetails[i+1][j].parent_h = k;

                }
            }
        }

        //right

        if (cell::isIntoWorld (i, j+1)){

            if (cell::isDestination(i, j+1, dest)){
                cellDetails[i][j+1].parent_i = i;
                cellDetails[i][j+1].parent_j = j;
                cellDetails[i][j+1].parent_h = k;
                printf("The destination cell is found\n");
                auto path = cell::tracePath(cellDetails, dest);
                return path;
            }
            else if (!(closedList[i][j+1]) &&
                     cell::isUnBlocked (i, j+1, k)){
                gNew = cellDetails[i][j].g + 1.0;
                hNew = cell::CalculateHeuristic (i, j+1, dest);
                fNew = gNew + hNew;

                if (cell::compare(cellDetails[i][j+1].f , FLT_MAX) ||
                    cellDetails[i][j+1].f > fNew){
                    openList.insert( ptriplet(fNew,glm::vec3 (i, j+1, float(game->chunkManager->heightSimplex(
                                                       i , j+1 , game::ConfigManager::GEN_MIN_HEIGHT, game::ConfigManager::GEN_MAX_HEIGHT)))));

                    cellDetails[i][j+1].f = fNew;
                    cellDetails[i][j+1].g = gNew;
                    cellDetails[i][j+1].h = hNew;
                    cellDetails[i][j+1].parent_i = i;
                    cellDetails[i][j+1].parent_j = j;
                    cellDetails[i][j+1].parent_h = k;

                }
            }
        }

        //left

        if (cell::isIntoWorld(i, j-1)){

            if (cell::isDestination(i, j-1, dest)){
                cellDetails[i][j-1].parent_i = i;
                cellDetails[i][j-1].parent_j = j;
                cellDetails[i][j-1].parent_h = k;
                printf("The destination cell is found\n");
                auto path = cell::tracePath(cellDetails, dest);
                return path;
            }
            else if (!(closedList[i][j-1]) &&
                     cell::isUnBlocked(i, j-1, k)){
                gNew = cellDetails[i][j].g + 1.0;
                hNew = cell::CalculateHeuristic(i, j-1, dest);
                fNew = gNew + hNew;

                if (cell::compare(cellDetails[i][j-1].f , FLT_MAX) ||
                    cellDetails[i][j-1].f > fNew){
                    openList.insert( ptriplet (fNew,glm::vec3(i, j-1 ,float(game->chunkManager->heightSimplex(
                                                        i , j-1 , game::ConfigManager::GEN_MIN_HEIGHT, game::ConfigManager::GEN_MAX_HEIGHT)))));

                    cellDetails[i][j-1].f = fNew;
                    cellDetails[i][j-1].g = gNew;
                    cellDetails[i][j-1].h = hNew;
                    cellDetails[i][j-1].parent_i = i;
                    cellDetails[i][j-1].parent_j = j;
                    cellDetails[i][j-1].parent_h = k;

                }
            }
        }

        //top right

        if (cell::isIntoWorld(i-1, j+1)){

            if (cell::isDestination(i-1, j+1, dest)){
                cellDetails[i-1][j+1].parent_i = i;
                cellDetails[i-1][j+1].parent_j = j;
                cellDetails[i-1][j+1].parent_h = k;
                printf ("The destination cell is found\n");
                auto path = cell::tracePath (cellDetails, dest);
                return path;
            }


            else if (!(closedList[i-1][j+1]) &&
                     cell::isUnBlocked(i-1, j+1, k)){
                gNew = cellDetails[i][j].g + 1.414;
                hNew = cell::CalculateHeuristic(i-1, j+1, dest);
                fNew = gNew + hNew;


                if (cell::compare(cellDetails[i-1][j+1].f , FLT_MAX) ||
                    cellDetails[i-1][j+1].f > fNew){
                    openList.insert( ptriplet (fNew,glm::vec3(i-1, j+1,float(game->chunkManager->heightSimplex(
                                                        i-1 , j+1 , game::ConfigManager::GEN_MIN_HEIGHT, game::ConfigManager::GEN_MAX_HEIGHT)))));

                    cellDetails[i-1][j+1].f = fNew;
                    cellDetails[i-1][j+1].g = gNew;
                    cellDetails[i-1][j+1].h = hNew;
                    cellDetails[i-1][j+1].parent_i = i;
                    cellDetails[i-1][j+1].parent_j = j;
                    cellDetails[i-1][j+1].parent_h = k;

                }
            }
        }

        //top left

        if (cell::isIntoWorld (i-1, j-1)){

            if (cell::isDestination (i-1, j-1, dest)){
                cellDetails[i-1][j-1].parent_i = i;
                cellDetails[i-1][j-1].parent_j = j;
                cellDetails[i-1][j-1].parent_h = k;
                printf ("The destination cell is found\n");
                auto path = cell::tracePath (cellDetails, dest);
                return path;
            }
            else if (!(closedList[i-1][j-1]) &&
                     cell::isUnBlocked(i-1, j-1, k)){
                gNew = cellDetails[i][j].g + 1.414;
                hNew = cell::CalculateHeuristic(i-1, j-1, dest);
                fNew = gNew + hNew;

                if (cell::compare(cellDetails[i-1][j-1].f , FLT_MAX) ||
                    cellDetails[i-1][j-1].f > fNew){
                    openList.insert( ptriplet (fNew, glm::vec3 (i-1, j-1, float(game->chunkManager->heightSimplex(
                            i-1 , j-1 , game::ConfigManager::GEN_MIN_HEIGHT, game::ConfigManager::GEN_MAX_HEIGHT)))));

                    cellDetails[i-1][j-1].f = fNew;
                    cellDetails[i-1][j-1].g = gNew;
                    cellDetails[i-1][j-1].h = hNew;
                    cellDetails[i-1][j-1].parent_i = i;
                    cellDetails[i-1][j-1].parent_j = j;
                    cellDetails[i-1][j-1].parent_h = k;

                }
            }
        }

        //bottom right

        if (cell::isIntoWorld(i+1, j+1)){

            if (cell::isDestination(i+1, j+1, dest)){
                cellDetails[i+1][j+1].parent_i = i;
                cellDetails[i+1][j+1].parent_j = j;
                cellDetails[i+1][j+1].parent_h = k;

                printf ("The destination cell is found\n");
                auto path = cell::tracePath (cellDetails, dest);
                return path;
            }
            else if (!(closedList[i+1][j+1]) &&
                     cell::isUnBlocked(i+1, j+1, k)){
                gNew = cellDetails[i][j].g + 1.414;
                hNew = cell::CalculateHeuristic(i+1, j+1, dest);
                fNew = gNew + hNew;

                if (cell::compare(cellDetails[i+1][j+1].f , FLT_MAX) ||
                    cellDetails[i+1][j+1].f > fNew){
                    openList.insert(ptriplet(fNew,glm::vec3 (i+1, j+1, float(game->chunkManager->heightSimplex(
                                                      i+1 , j+1 , game::ConfigManager::GEN_MIN_HEIGHT, game::ConfigManager::GEN_MAX_HEIGHT)))));

                    cellDetails[i+1][j+1].f = fNew;
                    cellDetails[i+1][j+1].g = gNew;
                    cellDetails[i+1][j+1].h = hNew;
                    cellDetails[i+1][j+1].parent_i = i;
                    cellDetails[i+1][j+1].parent_j = j;
                    cellDetails[i+1][j+1].parent_h = k;

                }
            }
        }

        //bottom left

        if (cell::isIntoWorld (i+1, j-1)){

            if (cell::isDestination(i+1, j-1, dest)){
                cellDetails[i+1][j-1].parent_i = i;
                cellDetails[i+1][j-1].parent_j = j;
                cellDetails[i+1][j-1].parent_h = k;

                printf("The destination cell is found\n");
                auto path = cell::tracePath(cellDetails, dest);
                return path;
            }
            else if (!(closedList[i+1][j-1]) &&
                     cell::isUnBlocked(i+1, j-1, k)){
                gNew = cellDetails[i][j].g + 1.414;
                hNew = cell::CalculateHeuristic(i+1, j-1, dest);
                fNew = gNew + hNew;

                if (cell::compare(cellDetails[i+1][j-1].f , FLT_MAX) ||
                    cellDetails[i+1][j-1].f > fNew){
                    openList.insert(ptriplet(fNew,glm::vec3(i+1, j-1, float(game->chunkManager->heightSimplex(
                                                      i+1 , j-1 , game::ConfigManager::GEN_MIN_HEIGHT, game::ConfigManager::GEN_MAX_HEIGHT)))));

                    cellDetails[i+1][j-1].f = fNew;
                    cellDetails[i+1][j-1].g = gNew;
                    cellDetails[i+1][j-1].h = hNew;
                    cellDetails[i+1][j-1].parent_i = i;
                    cellDetails[i+1][j-1].parent_j = j;
                    cellDetails[i+1][j-1].parent_h = k;

                }
            }
        }
    }

    if (foundDest == false)
        printf("Failed to find the Destination Cell\n");

    return std::stack<glm::vec3>();
}
