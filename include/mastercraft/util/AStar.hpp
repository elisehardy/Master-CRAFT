

#ifndef MASTERCRAFT_ASTAR_HPP
#define MASTERCRAFT_ASTAR_HPP


#include <mastercraft/util/Point.hpp>
#include <map>

namespace mastercraft::util{
    class AStar {
    private:
    public:
        AStar();
        std::vector<Point16> findNeighbors(Point16 position);
        bool checkBlockFree(std::vector<Point16> obstacle, Point16 position);
        bool  isObstacle(Point16 check, Point16 position);
        Point16 removePrority(std::map<Point16, int > map);
        int CalculateEuristic(Point16 p1, Point16 p2);
        std::vector<Point16 > findPath(Point16 destination, Point16 position, std::vector<Point16> obstacles);






        };
}

#endif //MASTERCRAFT_ASTAR_HPP
