#include <glm/gtx/hash.hpp>
#include <mastercraft/util/AStarNew.hpp>
#include <mastercraft/game/Game.hpp>
#include <utility>
#include <unordered_set>
#include <hwloc.h>

using namespace mastercraft::util;

bool cell::compare(double self, double other) {
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
        return false;
    }
}

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
        row = cellDetails[row][col].parent_i;
        col = cellDetails[row][col].parent_j;
        height = cellDetails[row][col].parent_h;
    }

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

    cell cellDetails[ROW][COL];

    int i, j, k;

    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
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
        closedList[i][j] = true;

        double gNew, hNew, fNew;

        //top
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
                }
            }
        }

        //bottom
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

                }
            }
        }

        //right
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

                }
            }
        }

        //left
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

                }
            }
        }

        //top right
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

                }
            }
        }

        //top left
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

                }
            }
        }

        //bottom right
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

                }
            }
        }

        //bottom left
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

                }
            }
        }
    }

    if (foundDest == false)
        printf("Failed to find the Destination Cell\n");

    return std::stack<glm::dvec4>();
}
