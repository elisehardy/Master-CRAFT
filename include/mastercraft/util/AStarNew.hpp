<<<<<<< HEAD
=======
//
// Created by ehardy on 1/28/20.
//

>>>>>>> b133593bc9f327543a60456083f197dded6d4a87
#ifndef MASTERCRAFT_ASTARNEW_HPP
#define MASTERCRAFT_ASTARNEW_HPP

#include <iostream>
#include <stack>
#include <cstring>
#include <set>
#include <mastercraft/cube/SuperChunk.hpp>
<<<<<<< HEAD

#define ROW 10
#define COL 10

namespace mastercraft::util {




=======
#include <mastercraft/game/Game.hpp>

namespace mastercraft::util {

#define ROW 10
#define COL 10

    template<typename First, typename Second, typename Third>
    struct triplet {
        First first;
        Second second;
        Third third;

        triplet(int x, int y, int z): first(x), second(y), third(z){}
        bool operator<(triplet<int,int, int> t) const {
            return this->first < t.first || (!(this->first < t.first) && this->second < t.second);
        }
    };
    typedef std::pair<double, triplet<int, int, int>> ptriplet;
>>>>>>> b133593bc9f327543a60456083f197dded6d4a87


    struct cell {
        int parent_i, parent_j, parent_h;
        double f, g, h;

<<<<<<< HEAD
        static bool sameChunk(glm::vec3 pos1, glm::vec3 pos2);

        static bool isUnBlocked(int x, int y, int posZ);

        static bool isDestination(int x, int y, glm::vec3 dest);

        //manhattan heuristic
        static double CalculateHeuristic(int x, int y, glm::vec3 dest);

        static std::stack<glm::dvec4>
        tracePath(cell cellDetails[][COL], glm::vec3 dest);

        static std::stack<glm::dvec4> aStarSearch(glm::vec3 src, glm::vec3 dest);

        static bool compare(double self, double other);


=======
        static bool isIntoWorld(int x, int y);

        static bool isUnBlocked(cube::SuperChunk *chunk, int x, int y, int posZ);

        static bool isDestination(int x, int y, triplet<int, int, int> dest);

        //manhattan heuristic
        static double CalculateHeuristic(int x, int y, triplet<int, int, int> dest);

        static void tracePath(cell cellDetails[][COL], triplet<int, int, int> dest);

        static void aStarSearch(game::Game *game,cube::SuperChunk *chunk, triplet<int, int, int> src,
                                triplet<int, int, int> dest);

        static bool compare(double self, double other);

>>>>>>> b133593bc9f327543a60456083f197dded6d4a87
    };
}

#endif //MASTERCRAFT_ASTARNEW_HPP
