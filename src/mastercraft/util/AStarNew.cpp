
#include <mastercraft/util/AStarNew.hpp>
#include <utility>

using namespace mastercraft::util;

bool cell::compare(double self, double other) {
    return (std::abs(self - other) < 0.0001);

}


bool cell::isValid(int x, int y){
    return (x >= 0) && (y >= 0) && (x < ROW) && (y < COL);
}

bool cell::isUnBlocked(cube::SuperChunk *chunk, int x, int y, int posZ)
{
    // Returns true if the cell is not blocked else false

    if (chunk->get(x, posZ+1, y) == cube::CubeType::AIR){
        return true;
    }
    if(chunk->get(x,posZ+2, y) == cube::CubeType::AIR){
        return true;
    }
    else
        return false;
}

bool cell::isDestination(int x, int y, triplet<int, int, int> dest)
{
    if (x == dest.first && y == dest.second){
        return true;
    }
    else {
        return false;
    }
}

double cell::calculateHValue(int x, int y, triplet<int, int, int> dest)
{
    /*return ((double)sqrt ((row-dest.first)*(row-dest.first)
                          + (col-dest.second)*(col-dest.second)));*/
    return abs(x - dest.first) + abs(y - dest.second);
}

void cell::tracePath(cell cellDetails[][COL], triplet<int, int, int> dest)
{
    printf ("\nThe Path is ");
    int row = dest.first;
    int col = dest.second;
    int height = dest.third;


    std::stack<triplet<int, int, int>> Path;

    while (!(cellDetails[row][col].parent_i == row
             && cellDetails[row][col].parent_j == col ))
    {
        Path.push (triplet<int, int, int>(row, col, height));
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        int temp_hei = cellDetails[row][col].parent_h;
        row = temp_row;
        col = temp_col;
        height = temp_hei;
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
    // If the source is out of range
    if (cell::isValid (src.first, src.second) == false)
    {
        printf ("Source is invalid\n");
        return;
    }

    // If the destination is out of range
    if (cell::isValid (dest.first, dest.second) == false)
    {
        printf ("Destination is invalid\n");
        return;
    }

    // Either the source or the destination is blocked
    if (cell::isUnBlocked(chunk, src.first, src.second, src.third) == false ||
        cell::isUnBlocked(chunk, dest.first, dest.second, dest.third) == false)
    {
        printf ("Source or the destination is blocked\n");
        return;
    }

    // If the destination cell is the same as source cell
    if (cell::isDestination(src.first, src.second, dest) == true)
    {
        printf ("We are already at the destination\n");
        return;
    }

    // Create a closed list and initialise it to false which means
    // that no cell has been included yet
    // This closed list is implemented as a boolean 2D array
    bool closedList[ROW][COL];
    std::memset(closedList, false, sizeof (closedList));

    // Declare a 2D array of structure to hold the details
    //of that cell
    cell cellDetails[ROW][COL];

    int i, j, k;

    for (i=0; i<ROW; i++)
    {
        for (j=0; j<COL; j++)
        {
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
            cellDetails[i][j].parent_h = -1;
        }
    }

    // Initialising the parameters of the starting node
    i = src.first, j = src.second, k = src.third;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;
    cellDetails[i][j].parent_h = k;

    /*
     Create an open list having information as-
     <f, <i, j>>
     where f = g + h,
     and i, j are the row and column index of that cell
     Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
     This open list is implenented as a set of pair of pair.*/
    std::set<ptriplet> openList;

    // Put the starting cell on the open list and set its
    // 'f' as 0
    openList.insert(ptriplet (0.0, triplet<int, int, int>(i, j, k)));

    // We set this boolean value as false as initially
    // the destination is not reached.
    bool foundDest = false;

    while (!openList.empty())
    {
        ptriplet p = *openList.begin();

        // Remove this vertex from the open list
        openList.erase(openList.begin());

        // Add this vertex to the closed list
        i = p.second.first;
        j = p.second.second;
        k = p.second.third;
        closedList[i][j] = true;

        /*
         Generating all the 8 successor of this cell

             N.W   N   N.E
               \   |   /
                \  |  /
             W----Cell----E
                  / | \
                /   |  \
             S.W    S   S.E

         Cell-->Popped Cell (i, j)
         N -->  North       (i-1, j)
         S -->  South       (i+1, j)
         E -->  East        (i, j+1)
         W -->  West           (i, j-1)
         N.E--> North-East  (i-1, j+1)
         N.W--> North-West  (i-1, j-1)
         S.E--> South-East  (i+1, j+1)
         S.W--> South-West  (i+1, j-1)*/

        // To store the 'g', 'h' and 'f' of the 8 successors
        double gNew, hNew, fNew;

        //----------- 1st Successor (North) ------------

        // Only process this cell if this is a valid one
        if (cell::isValid(i-1, j) == true)
        {
            // If the destination cell is the same as the
            // current successor
            if (cell::isDestination(i-1, j, dest) == true)
            {
                // Set the Parent of the destination cell
                cellDetails[i-1][j].parent_i = i;
                cellDetails[i-1][j].parent_j = j;
                cellDetails[i-1][j].parent_h = k;
                printf ("The destination cell is found\n");
                cell::tracePath (cellDetails, dest);
                foundDest = true;
                return;
            }
                // If the successor is already on the closed
                // list or if it is blocked, then ignore it.
                // Else do the following
            else if (closedList[i-1][j] == false &&
                     cell::isUnBlocked(chunk, i-1, j, k) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = cell::calculateHValue (i-1, j, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is better,
                // using 'f' cost as the measure.
                if (cell::compare(cellDetails[i-1][j].f , FLT_MAX) ||
                    cellDetails[i-1][j].f > fNew)
                {
                    openList.insert( ptriplet(fNew,
                                               triplet<int, int, int>(i-1, j, game->chunkManager->heightSimplex(
                                                       i-1 , j , game::ConfigManager::GEN_MIN_HEIGHT, game::ConfigManager::GEN_MAX_HEIGHT
                                               ))));

                    // Update the details of this cell
                    cellDetails[i-1][j].f = fNew;
                    cellDetails[i-1][j].g = gNew;
                    cellDetails[i-1][j].h = hNew;
                    cellDetails[i-1][j].parent_i = i;
                    cellDetails[i-1][j].parent_j = j;
                    cellDetails[i-1][j].parent_h = k;
                }
            }
        }

        //----------- 2nd Successor (South) ------------

        // Only process this cell if this is a valid one
        if (cell::isValid(i+1, j) == true)
        {
            // If the destination cell is the same as the
            // current successor
            if (cell::isDestination(i+1, j, dest) == true)
            {
                // Set the Parent of the destination cell
                cellDetails[i+1][j].parent_i = i;
                cellDetails[i+1][j].parent_j = j;
                cellDetails[i+1][j].parent_h = k;
                printf("The destination cell is found\n");
                cell::tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }
                // If the successor is already on the closed
                // list or if it is blocked, then ignore it.
                // Else do the following
            else if (closedList[i+1][j] == false &&
                     cell::isUnBlocked(chunk, i+1, j, k) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = cell::calculateHValue(i+1, j, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is better,
                // using 'f' cost as the measure.
                if (cell::compare(cellDetails[i+1][j].f, FLT_MAX) ||
                    cellDetails[i+1][j].f > fNew)
                {
                    openList.insert( ptriplet (fNew, triplet<int, int ,int> (i+1, j, game->chunkManager->heightSimplex(
                            i+1 , j , game::ConfigManager::GEN_MIN_HEIGHT, game::ConfigManager::GEN_MAX_HEIGHT
                    ))));
                    // Update the details of this cell
                    cellDetails[i+1][j].f = fNew;
                    cellDetails[i+1][j].g = gNew;
                    cellDetails[i+1][j].h = hNew;
                    cellDetails[i+1][j].parent_i = i;
                    cellDetails[i+1][j].parent_j = j;
                    cellDetails[i+1][j].parent_h = k;

                }
            }
        }

        //----------- 3rd Successor (East) ------------

        // Only process this cell if this is a valid one
        if (cell::isValid (i, j+1) == true)
        {
            // If the destination cell is the same as the
            // current successor
            if (cell::isDestination(i, j+1, dest) == true)
            {
                // Set the Parent of the destination cell
                cellDetails[i][j+1].parent_i = i;
                cellDetails[i][j+1].parent_j = j;
                cellDetails[i][j+1].parent_h = k;
                printf("The destination cell is found\n");
                cell::tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }

                // If the successor is already on the closed
                // list or if it is blocked, then ignore it.
                // Else do the following
            else if (closedList[i][j+1] == false &&
                     cell::isUnBlocked (chunk, i, j+1, k) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = cell::calculateHValue (i, j+1, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is better,
                // using 'f' cost as the measure.
                if (cell::compare(cellDetails[i][j+1].f , FLT_MAX) ||
                    cellDetails[i][j+1].f > fNew)
                {
                    openList.insert( ptriplet(fNew,
                                               triplet<int, int, int> (i, j+1, game->chunkManager->heightSimplex(
                                                       i , j+1 , game::ConfigManager::GEN_MIN_HEIGHT, game::ConfigManager::GEN_MAX_HEIGHT
                                               ))));

                    // Update the details of this cell
                    cellDetails[i][j+1].f = fNew;
                    cellDetails[i][j+1].g = gNew;
                    cellDetails[i][j+1].h = hNew;
                    cellDetails[i][j+1].parent_i = i;
                    cellDetails[i][j+1].parent_j = j;
                    cellDetails[i][j+1].parent_h = k;

                }
            }
        }

        //----------- 4th Successor (West) ------------

        // Only process this cell if this is a valid one
        if (cell::isValid(i, j-1) == true)
        {
            // If the destination cell is the same as the
            // current successor
            if (cell::isDestination(i, j-1, dest) == true)
            {
                // Set the Parent of the destination cell
                cellDetails[i][j-1].parent_i = i;
                cellDetails[i][j-1].parent_j = j;
                cellDetails[i][j-1].parent_h = k;
                printf("The destination cell is found\n");
                cell::tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }

                // If the successor is already on the closed
                // list or if it is blocked, then ignore it.
                // Else do the following
            else if (closedList[i][j-1] == false &&
                     cell::isUnBlocked(chunk, i, j-1, k) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = cell::calculateHValue(i, j-1, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is better,
                // using 'f' cost as the measure.
                if (cell::compare(cellDetails[i][j-1].f , FLT_MAX) ||
                    cellDetails[i][j-1].f > fNew)
                {
                    openList.insert( ptriplet (fNew,
                                                triplet<int, int, int>(i, j-1 ,game->chunkManager->heightSimplex(
                                                        i , j-1 , game::ConfigManager::GEN_MIN_HEIGHT, game::ConfigManager::GEN_MAX_HEIGHT
                                                ))));

                    // Update the details of this cell
                    cellDetails[i][j-1].f = fNew;
                    cellDetails[i][j-1].g = gNew;
                    cellDetails[i][j-1].h = hNew;
                    cellDetails[i][j-1].parent_i = i;
                    cellDetails[i][j-1].parent_j = j;
                    cellDetails[i][j-1].parent_h = k;

                }
            }
        }

        //----------- 5th Successor (North-East) ------------

        // Only process this cell if this is a valid one
        if (cell::isValid(i-1, j+1) == true)
        {
            // If the destination cell is the same as the
            // current successor
            if (cell::isDestination(i-1, j+1, dest) == true)
            {
                // Set the Parent of the destination cell
                cellDetails[i-1][j+1].parent_i = i;
                cellDetails[i-1][j+1].parent_j = j;
                cellDetails[i-1][j+1].parent_h = k;
                printf ("The destination cell is found\n");
                cell::tracePath (cellDetails, dest);
                foundDest = true;
                return;
            }

                // If the successor is already on the closed
                // list or if it is blocked, then ignore it.
                // Else do the following
            else if (closedList[i-1][j+1] == false &&
                     cell::isUnBlocked(chunk, i-1, j+1, k) == true)
            {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = cell::calculateHValue(i-1, j+1, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is better,
                // using 'f' cost as the measure.
                if (cell::compare(cellDetails[i-1][j+1].f , FLT_MAX) ||
                    cellDetails[i-1][j+1].f > fNew)
                {
                    openList.insert( ptriplet (fNew,
                                                triplet<int, int, int>(i-1, j+1,game->chunkManager->heightSimplex(
                                                        i-1 , j+1 , game::ConfigManager::GEN_MIN_HEIGHT, game::ConfigManager::GEN_MAX_HEIGHT
                                                ))));

                    // Update the details of this cell
                    cellDetails[i-1][j+1].f = fNew;
                    cellDetails[i-1][j+1].g = gNew;
                    cellDetails[i-1][j+1].h = hNew;
                    cellDetails[i-1][j+1].parent_i = i;
                    cellDetails[i-1][j+1].parent_j = j;
                    cellDetails[i-1][j+1].parent_h = k;

                }
            }
        }

        //----------- 6th Successor (North-West) ------------

        // Only process this cell if this is a valid one
        if (cell::isValid (i-1, j-1) == true)
        {
            // If the destination cell is the same as the
            // current successor
            if (cell::isDestination (i-1, j-1, dest) == true)
            {
                // Set the Parent of the destination cell
                cellDetails[i-1][j-1].parent_i = i;
                cellDetails[i-1][j-1].parent_j = j;
                cellDetails[i-1][j-1].parent_h = k;
                printf ("The destination cell is found\n");
                cell::tracePath (cellDetails, dest);
                foundDest = true;
                return;
            }

                // If the successor is already on the closed
                // list or if it is blocked, then ignore it.
                // Else do the following
            else if (closedList[i-1][j-1] == false &&
                     cell::isUnBlocked(chunk, i-1, j-1, k) == true)
            {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = cell::calculateHValue(i-1, j-1, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is better,
                // using 'f' cost as the measure.
                if (cell::compare(cellDetails[i-1][j-1].f , FLT_MAX) ||
                    cellDetails[i-1][j-1].f > fNew)
                {
                    openList.insert( ptriplet (fNew, triplet<int, int, int> (i-1, j-1, game->chunkManager->heightSimplex(
                            i-1 , j-1 , game::ConfigManager::GEN_MIN_HEIGHT, game::ConfigManager::GEN_MAX_HEIGHT
                    ))));
                    // Update the details of this cell
                    cellDetails[i-1][j-1].f = fNew;
                    cellDetails[i-1][j-1].g = gNew;
                    cellDetails[i-1][j-1].h = hNew;
                    cellDetails[i-1][j-1].parent_i = i;
                    cellDetails[i-1][j-1].parent_j = j;
                    cellDetails[i-1][j-1].parent_h = k;

                }
            }
        }

        //----------- 7th Successor (South-East) ------------

        // Only process this cell if this is a valid one
        if (cell::isValid(i+1, j+1) == true)
        {
            // If the destination cell is the same as the
            // current successor
            if (cell::isDestination(i+1, j+1, dest) == true)
            {
                // Set the Parent of the destination cell
                cellDetails[i+1][j+1].parent_i = i;
                cellDetails[i+1][j+1].parent_j = j;
                cellDetails[i+1][j+1].parent_h = k;

                printf ("The destination cell is found\n");
                cell::tracePath (cellDetails, dest);
                foundDest = true;
                return;
            }

                // If the successor is already on the closed
                // list or if it is blocked, then ignore it.
                // Else do the following
            else if (closedList[i+1][j+1] == false &&
                     cell::isUnBlocked(chunk, i+1, j+1, k) == true)
            {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = cell::calculateHValue(i+1, j+1, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is better,
                // using 'f' cost as the measure.
                if (cell::compare(cellDetails[i+1][j+1].f , FLT_MAX) ||
                    cellDetails[i+1][j+1].f > fNew)
                {
                    openList.insert(ptriplet(fNew,
                                              triplet<int, int, int> (i+1, j+1, game->chunkManager->heightSimplex(
                                                      i+1 , j+1 , game::ConfigManager::GEN_MIN_HEIGHT, game::ConfigManager::GEN_MAX_HEIGHT
                                              ))));

                    // Update the details of this cell
                    cellDetails[i+1][j+1].f = fNew;
                    cellDetails[i+1][j+1].g = gNew;
                    cellDetails[i+1][j+1].h = hNew;
                    cellDetails[i+1][j+1].parent_i = i;
                    cellDetails[i+1][j+1].parent_j = j;
                    cellDetails[i+1][j+1].parent_h = k;

                }
            }
        }

        //----------- 8th Successor (South-West) ------------

        // Only process this cell if this is a valid one
        if (cell::isValid (i+1, j-1) == true)
        {
            // If the destination cell is the same as the
            // current successor
            if (cell::isDestination(i+1, j-1, dest) == true)
            {
                // Set the Parent of the destination cell
                cellDetails[i+1][j-1].parent_i = i;
                cellDetails[i+1][j-1].parent_j = j;
                cellDetails[i+1][j-1].parent_h = k;

                printf("The destination cell is found\n");
                cell::tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }

                // If the successor is already on the closed
                // list or if it is blocked, then ignore it.
                // Else do the following
            else if (closedList[i+1][j-1] == false &&
                     cell::isUnBlocked(chunk, i+1, j-1, k) == true)
            {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = cell::calculateHValue(i+1, j-1, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is better,
                // using 'f' cost as the measure.
                if (cell::compare(cellDetails[i+1][j-1].f , FLT_MAX) ||
                    cellDetails[i+1][j-1].f > fNew)
                {
                    openList.insert(ptriplet(fNew,
                                              triplet<int, int,int>(i+1, j-1, game->chunkManager->heightSimplex(
                                                      i+1 , j-1 , game::ConfigManager::GEN_MIN_HEIGHT, game::ConfigManager::GEN_MAX_HEIGHT
                                              ))));

                    // Update the details of this cell
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

    // When the destination cell is not found and the open
    // list is empty, then we conclude that we failed to
    // reach the destiantion cell. This may happen when the
    // there is no way to destination cell (due to blockages)
    if (foundDest == false)
        printf("Failed to find the Destination Cell\n");

    return;
}

