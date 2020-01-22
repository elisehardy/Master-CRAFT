

#include <mastercraft/util/AStar.hpp>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace mastercraft::util;

std::vector<Point16> AStar::findNeighbors(Point16 position){
    std::vector<Point16> neighbors;
    neighbors.push_back(Point16(position.x-1, position.y));
    neighbors.push_back(Point16(position.x+1, position.y));
    neighbors.push_back(Point16(position.x-1, position.y-1));
    neighbors.push_back(Point16(position.x-1, position.y+1));
    neighbors.push_back(Point16(position.x+1, position.y-1));
    neighbors.push_back(Point16(position.x+1, position.y+1));
    neighbors.push_back(Point16(position.x, position.y+1));
    neighbors.push_back(Point16(position.x, position.y-1));

    return neighbors;
}

bool AStar::checkBlockFree(std::vector<Point16> obstacle, Point16 position){
    for (auto ob: obstacle) {
        if (isObstacle(ob, position)){
            return false;
        }
    }
    return true;
}

bool  AStar::isObstacle(Point16 check, Point16 position){
    return check==position;
}

Point16 AStar::removePrority(std::map<Point16, int > map){
    return Point16(0,0);
}

//manhattan distance
int AStar::CalculateEuristic(Point16 p1, Point16 p2){
    return abs(p1.x - p2.x) - abs(p1.y - p2.y);
}

std::vector<Point16 > AStar::findPath(Point16 destination, Point16 position, std::vector<Point16> obstacles){
    //check if destination is free
    if(!checkBlockFree(obstacles, destination)){
        return std::vector<Point16>();
    }
    std::map<Point16, int> prorityPositions;
    std::map<Point16, Point16> sources;
    std::map<Point16, int> cost;
    prorityPositions.insert(std::pair<Point16, int>(position, 0));
    sources.insert(std::pair<Point16, Point16>(position, Point16(0,0)));
    cost.insert(std::pair<Point16, int>(position, 0));
    Point16 current;
    while(!prorityPositions.empty()){
        //check if destination is too far
        if(prorityPositions.size() > 100){
            break;
        }
        current = removePrority(prorityPositions);
        if(current == destination){
            //path found generate path
            break;
        }
        std::vector<Point16>  neighbors = findNeighbors(current);
        for(auto p : neighbors){
            if(!checkBlockFree(obstacles, p)){
                continue;
            }
            int newCost = cost.find(current)->second +1;
            if(cost.find(p) != cost.end() || newCost < cost.find(p)->second){
                cost.insert(std::pair<Point16, int>(p, newCost));
                prorityPositions.insert(std::pair<Point16, int>(p, newCost+CalculateEuristic(destination, p)));
                sources.insert(std::pair<Point16, Point16>(p, current));

            }
        }

    }

    if(!(current == destination)){
        return std::vector<Point16 >();
    }
    current = destination;
    std::vector<Point16> path;
    while(!(current == position)){
        path.push_back(current);
        current = sources.find(current)->second;
    }
    path.push_back(current);
    std::reverse(path.begin(),path.end());
    return path;
}
