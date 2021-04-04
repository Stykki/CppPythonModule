#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include "aldusBroder.cpp"
#include <string>

class SideWinder: public Maze
{
    protected:
        int N = 1;
        int S = 2;
        int W = 4;
        int E = 8;
        int weight;
        int remaining;
        //                         0    N  S  3   W  5  6  7  E
        int MOVE_X_DIRECTION[9] = {0 ,  0, 0, 0, -1, 0, 0, 0, 1};
        int MOVE_Y_DIRECTION[9] = {0 , -1, 1, 0,  0, 0, 0, 0, 0};
        int OPPOSITE_DIRECTION[9] = {0, S, N, 0,  E, 0, 0, 0, W};
        
    public:
        SideWinder(int w, int h, int we);
        void run(bool display);
        int * getMaze();
};

SideWinder::SideWinder(int w, int h, int we = 2)
{
    int NSWE[4] = {N,S,W,E};
    Maze::setDirections(NSWE);
    width = w;
    height = h;
    weight = we;
    mazeGrid = new int[width * height];
    pathGrid = new bool[width * height];
    for (int i = 0; i < width*height; i++)
    {
        mazeGrid[i] = 0;
        pathGrid[i] = 0;
    }
}

void SideWinder::run(bool display)
{
    for (int y = 0; y < height; y++)
    {
        int runStart = 0;
        for (int x = 0; x < width; x++)
        {

            if ((y > 0) && ((x+1 == width) || ((rand() % weight) == 0)))
            {
                int cell = runStart + rand() % (x - runStart + 1);
                mazeGrid[getIndex(y, cell)] |= N;
                mazeGrid[getIndex(y-1, cell)] |= S;

                if (display)
                {
                    pathGrid[getIndex(y, cell)] = true;
                    pathGrid[getIndex(y-1, cell)] = true;
                    printGrid();
                    Sleep(10);
                    pathGrid[getIndex(y, cell)] = false;
                    pathGrid[getIndex(y-1, cell)] = false;
                }

                runStart = x+1;
            }
            else if (x+1 < width)
            {
                mazeGrid[getIndex(y, x)] |= E;
                mazeGrid[getIndex(y, x+1)] |= W;

                if (display)
                {
                    pathGrid[getIndex(y, x)] = true;
                    pathGrid[getIndex(y, x+1)] = true;
                    printGrid();
                    Sleep(10);
                    pathGrid[getIndex(y, x)] = false;
                    pathGrid[getIndex(y, x+1)] = false;
                }
            }
        }
    }
    if (display)
    {
        printGrid();
    }
}

int* SideWinder::getMaze()
{
    return mazeGrid;
}

