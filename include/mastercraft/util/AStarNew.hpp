//
// Created by ehardy on 1/28/20.
//

#ifndef MASTERCRAFT_ASTARNEW_HPP
#define MASTERCRAFT_ASTARNEW_HPP

#include <iostream>
#include <stack>
#include <cstring>
#include <set>
#include <mastercraft/cube/SuperChunk.hpp>
#include <mastercraft/game/Game.hpp>

namespace mastercraft::util {

#define ROW 9
#define COL 10

// Creating a shortcut for int, int pair type
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
// Creating a shortcut for pair<int, pair<int, int>> type
    typedef std::pair<double, triplet<int, int, int>> ptriplet;


// A structure to hold the neccesary parameters
    struct cell {
        // Row and Column index of its parent
        // Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
        int parent_i, parent_j, parent_h;
        // f = g + h
        double f, g, h;

        static bool isValid(int x, int y);

// A Utility Function to check whether the given cell is
// blocked or not
        static bool isUnBlocked(cube::SuperChunk *chunk, int x, int y, int posZ);

// A Utility Function to check whether destination cell has
// been reached or not
        static bool isDestination(int x, int y, triplet<int, int, int> dest);

// A Utility Function to calculate the 'h' heuristics.
        static double calculateHValue(int x, int y, triplet<int, int, int> dest);

// A Utility Function to trace the path from the source
// to destination
        static void tracePath(cell cellDetails[][COL], triplet<int, int, int> dest);

// A Function to find the shortest path between
// a given source cell to a destination cell according
// to A* Search Algorithm
        static void aStarSearch(game::Game *game,cube::SuperChunk *chunk, triplet<int, int, int> src,
                                triplet<int, int, int> dest);


        static bool compare(double self, double other);

    };
}

#endif //MASTERCRAFT_ASTARNEW_HPP
