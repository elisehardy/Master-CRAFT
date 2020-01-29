
#include <mastercraft/util/AStarNew.hpp>
#include <utility>

using namespace mastercraft::util;

bool cell::compare(double self, double other) {
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
        return false;
    }
}

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
        row = cellDetails[row][col].parent_i;
        col = cellDetails[row][col].parent_j;
        height = cellDetails[row][col].parent_h;
    }

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

    i = src.first, j = src.second, k = src.third;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;
    cellDetails[i][j].parent_h = k;

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
        closedList[i][j] = true;

        double gNew, hNew, fNew;

        //top

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

                }
            }
        }
    }

    if (foundDest == false)
        printf("Failed to find the Destination Cell\n");

    return;
}

