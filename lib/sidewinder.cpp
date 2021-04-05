#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include "aldusBroder.cpp"
#include <string>

class SideWinder: public Maze
{
    protected:
        int N = 1;      //-----------//
        int S = 2;      // Direction //
        int W = 4;      //  values   //
        int E = 8;      //-----------//
        int weight;
        int remaining;
        //                         0    N  S  3   W  5  6  7  E
        int MOVE_X_DIRECTION[9] = {0 ,  0, 0, 0, -1, 0, 0, 0, 1};
        int MOVE_Y_DIRECTION[9] = {0 , -1, 1, 0,  0, 0, 0, 0, 0};
        int OPPOSITE_DIRECTION[9] = {0, S, N, 0,  E, 0, 0, 0, W};
        
    public:
        SideWinder(int w, int h, int we);
        void run();
        int * getMaze();
};

SideWinder::SideWinder(int w, int h, int we = 2)
{
    int NSWE[4] = {N,S,W,E};
    Maze::setDirections(NSWE);
    width = w;
    height = h;
    weight = we;    // weight for calculating a random stop to the current run
    mazeGrid = new int[width * height];
    pathGrid = new bool[width * height];    // used for displaying where in the grid we are at every iteration
    for (int i = 0; i < width*height; i++)
    {
        mazeGrid[i] = 0;
        pathGrid[i] = 0;
    }
}

void SideWinder::run()
{
    for (int y = 0; y < height; y++)
    {
        int runStart = 0;
        for (int x = 0; x < width; x++)
        {
            
            if ((y > 0) && ((x+1 == width) || ((rand() % weight) == 0)))
//  dont stop at first line,   stop if at end or got 0 from random calculation
            {
                int cell = runStart + rand() % (x - runStart + 1);  // get new cell 
                mazeGrid[getIndex(y, cell)] |= N;       // make way north
                mazeGrid[getIndex(y-1, cell)] |= S;     // make way south

                if (DISPLAY)
                {
                    pathGrid[getIndex(y, cell)] = true;
                    pathGrid[getIndex(y-1, cell)] = true;
                    printGrid();
                    Sleep(DELAY);
                    pathGrid[getIndex(y, cell)] = false;
                    pathGrid[getIndex(y-1, cell)] = false;
                }

                runStart = x+1;
            }
            else if (x+1 < width)   // dont make way east if at end
            {
                mazeGrid[getIndex(y, x)] |= E;  // make way east
                mazeGrid[getIndex(y, x+1)] |= W;    // make way west

                if (DISPLAY)
                {
                    pathGrid[getIndex(y, x)] = true;
                    pathGrid[getIndex(y, x+1)] = true;
                    printGrid();
                    Sleep(DELAY);
                    pathGrid[getIndex(y, x)] = false;
                    pathGrid[getIndex(y, x+1)] = false;
                }
            }
        }
    }
    if (DISPLAY)
    {
        printGrid();
    }
}

int* SideWinder::getMaze()
{
    return mazeGrid;
}

