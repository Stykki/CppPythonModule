#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include "recursiveBacktracking.cpp"
#include <string>

class AldusBroder: public Maze
{
    protected:
        int N = 1;      //-----------//
        int S = 2;      // Direction //
        int W = 4;      //  values   //
        int E = 8;      //-----------//
        int remaining;
        //                         0    N  S  3   W  5  6  7  E
        int MOVE_X_DIRECTION[9] = {0 ,  0, 0, 0, -1, 0, 0, 0, 1};
        int MOVE_Y_DIRECTION[9] = {0 , -1, 1, 0,  0, 0, 0, 0, 0};
        int OPPOSITE_DIRECTION[9] = {0, S, N, 0,  E, 0, 0, 0, W};
        bool isPosValid(int x, int y);

    public:
        AldusBroder(int w, int h);
        void run();
        int * getMaze();

};

AldusBroder::AldusBroder(int w, int h)
{
    int NSWE[4] = {N,S,W,E};
    Maze::setDirections(NSWE);
    width = w;
    height = h;

    mazeGrid = new int[width * height];
    pathGrid = new bool[width * height];    // used for displaying where in the grid we are at every iteration
    for (int i = 0; i < width*height; i++)
    {
        mazeGrid[i] = 0;
        pathGrid[i] = 0;
    }
    remaining = width * height - 1;     // cells left untouched
}

void AldusBroder::run()
{
    // start at random coordinate in grid
    int x = rand() % width;
    int y = rand() % height;
    
    if (DISPLAY)
    {
        printGrid();
    }

    while (remaining > 0)   // while there are cells that have not been touched
    {
        vector<int> dir = { N,S,E,W };
        random_shuffle(dir.begin(), dir.end());     // shuffle directions
        for (int i = 0; i < 4; i++)     // iterate through directions (random direction at front each time)
        {
            int newX = x + MOVE_X_DIRECTION[dir[i]];
            int newY = y + MOVE_Y_DIRECTION[dir[i]];

            if (isPosValid(newX, newY))
            {
                if (mazeGrid[getIndex(newY, newX)] == 0)    // if position in grid is untouched
                {

                    mazeGrid[getIndex(y, x)] |= dir[i];     // make way in direction
                    mazeGrid[getIndex(newY, newX)] |= OPPOSITE_DIRECTION[dir[i]];   // make way in opposite direction
                    remaining--;
                    if (DISPLAY)
                    {
                        pathGrid[getIndex(y, x)] = 1;
                        pathGrid[getIndex(newY, newX)] = 1;
                        printGrid();
                        pathGrid[getIndex(y, x)] = 0;
                        pathGrid[getIndex(newY, newX)] = 0;
                        Sleep(DELAY);
                    }
                }

                x = newX;
                y = newY;
                break;
            }
        }
    }
    if (DISPLAY)
    {
        printGrid();
    }
}

bool AldusBroder::isPosValid(int x, int y)
{
    /*
    * checks wither the provided x and y coordinates are within bounds of the grid
    */
    if ((x >= 0) && (y >= 0) && (x < width) && (y < height))
    {
        return 1;
    }
    return 0;
}

int * AldusBroder::getMaze()
{
    return mazeGrid;
}


