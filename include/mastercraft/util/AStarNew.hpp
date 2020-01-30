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


    template<typename First, typename Second, typename Third>
    struct triplet {
        First first;
        Second second;
        Third third;

        triplet(int x, int y, int z) : first(x), second(y), third(z) {}

        bool operator<(triplet<int, int, int> t) const {
            return this->first < t.first || (!(this->first < t.first) && this->second < t.second);
        }


    };


    typedef std::pair<double, glm::vec3> ptriplet;


    struct cell {
        int parent_i, parent_j, parent_h;
        double f, g, h;

        static bool isIntoWorld(int x, int y);

        static bool isUnBlocked(int x, int y, int posZ);

        static bool isDestination(int x, int y, glm::vec3 dest);

        //manhattan heuristic
        static double CalculateHeuristic(int x, int y, glm::vec3 dest);

        static std::stack<glm::vec3>
        tracePath(cell cellDetails[][COL], glm::vec3 dest);

        static std::stack<glm::vec3>
        aStarSearch(glm::vec3 src,
                    glm::vec3 dest);

        static bool compare(double self, double other);

        static triplet<int, int, int> convertIvec3IntoTriplet(glm::vec3 &v);
        static glm::vec3 convertTripletIntoIvec3(triplet<int, int, int> &t);

    };
}

#endif //MASTERCRAFT_ASTARNEW_HPP
