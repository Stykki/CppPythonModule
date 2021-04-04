#include <iostream>
#include <Windows.h>
#include <string>
#include <random>
#include <algorithm>
#include <vector>
#include "prims.cpp"

using namespace std;

class RecursiveBacktrack: public Maze
{
    protected:
        int N = 1;
        int S = 2;
        int W = 4;
        int E = 8;
        //                         0    N  S  3   W  5  6  7  E
        int MOVE_X_DIRECTION[9] = {0 ,  0, 0, 0, -1, 0, 0, 0, 1};
        int MOVE_Y_DIRECTION[9] = {0 , -1, 1, 0,  0, 0, 0, 0, 0};
        int OPPOSITE_DIRECTION[9] = {0, S, N, 0,  E, 0, 0, 0, W};
 
        int currX;
        int currY;

        void carvePassagesFrom(int x, int y);

        bool isPosValid(int x, int y);


    public:

        RecursiveBacktrack(int w, int h);
        void run();
        void setDelay(int del);
        int * getMaze();
};

RecursiveBacktrack::RecursiveBacktrack(int w, int h)
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
 
}


void RecursiveBacktrack::setDelay(int del)
{
    Maze::setDelay(del);
    DELAY = del;
}


bool RecursiveBacktrack::isPosValid(int x, int y)
{
    if ((x >= 0) && (y >= 0) && (x < width) && (y < height))
    {
        if (mazeGrid[getIndex(y,x)] == 0)
        {
            return 1;
        }
    }
    return 0;
}

void RecursiveBacktrack::carvePassagesFrom(int x, int y)
{
    vector<int> dir = { N,S,E,W };

    random_shuffle(dir.begin(), dir.end());

    for (int i = 0; i< 4; i++)
    {
        int newX = x + MOVE_X_DIRECTION[dir[i]];
        int newY = y + MOVE_Y_DIRECTION[dir[i]];
        if (isPosValid(newX, newY))
        {
            mazeGrid[getIndex(y, x)] |= dir[i];     // make way in direction


            mazeGrid[getIndex(newY, newX)] |= OPPOSITE_DIRECTION[dir[i]];   // make way in opposite direction
            pathGrid[getIndex(y, x)] = 1;
            pathGrid[getIndex(newY, newX)] = 1;

            if ( DISPLAY )
            {
                printGrid();
                Sleep(DELAY);
            }


            carvePassagesFrom(newX, newY);      // recursively keep going until dead end is met

            pathGrid[getIndex(y, x)] = 0;
            pathGrid[getIndex(newY, newX)] = 0;
            if ( DISPLAY )
            {
                printGrid();
                Sleep(DELAY);
            }
        }

    }
}

void RecursiveBacktrack::run()
{
    carvePassagesFrom(0,0);
}

int* RecursiveBacktrack::getMaze()
{
    return mazeGrid;
}


