#ifndef MASTERCRAFT_ASTARNEW_HPP
#define MASTERCRAFT_ASTARNEW_HPP

#include <iostream>
#include <stack>
#include <cstring>
#include <set>
#include <mastercraft/cube/SuperChunk.hpp>

#define ROW 10
#define COL 10

namespace mastercraft::util {






    struct cell {
        int parent_i, parent_j, parent_h;
        double f, g, h;

        static bool sameChunk(glm::vec3 pos1, glm::vec3 pos2);

        static bool isUnBlocked(int x, int y, int posZ);

        static bool isDestination(int x, int y, glm::vec3 dest);

        //manhattan heuristic
        static double CalculateHeuristic(int x, int y, glm::vec3 dest);

        static std::stack<glm::dvec4>
        tracePath(cell cellDetails[][COL], glm::vec3 dest);

        static std::stack<glm::dvec4> aStarSearch(glm::vec3 src, glm::vec3 dest);

        static bool compare(double self, double other);


    };
}

#endif //MASTERCRAFT_ASTARNEW_HPP
