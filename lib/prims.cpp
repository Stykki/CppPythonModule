#include <iostream>
#include <Windows.h>
#include <random>
#include <vector>
#include <tuple>

#include "kruskals.cpp"

using namespace std;


class Prims: public Maze

{
    protected:
        int N = 1;      //-----------//
        int S = 2;      // Direction //
        int W = 4;      //  values   //
        int E = 8;      //-----------//
        int OPPOSITE_DIRECTION[9] = {0, S, N, 0,  E, 0, 0, 0, W};

        int MARKED = 16;
        int AVAILABLE = 32;

        vector<tuple<int, int>> markedPoints;
        
        tuple<int,int> getRandomNeighbour(int x, int y);

        void addMark(int x, int y);
        void mark(int x, int y);
        void mark();

        int direction(int x, int y, int x2, int y2);

    public:

        void run();
        void displayNumbers();
        int * getMaze();

        Prims(int w, int h);
        ~Prims(); 



};

Prims::Prims(int w, int h)
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

tuple<int,int> Prims::getRandomNeighbour(int y, int x)
{
    
    /*
     * This function gets a random valid neighbour from a given y,x coordinate
     * Retunres a single y,x coordinate as a tuple
     * A coordinate is valid if it has not been visited and it is not out of bounds
     */
    vector<tuple<int, int>> nbrs;
    if (x > 0)
    {
        if ((mazeGrid[getIndex(y,x-1)] & MARKED) != 0)
        {
            nbrs.push_back(tuple<int, int>({y, x-1}));

        }
    }
    if (x+1 < width)
    {
        if ((mazeGrid[getIndex(y,x+1)] & MARKED) != 0)
        {
            nbrs.push_back(tuple<int, int>({y, x+1}));
        }
    }
    if (y > 0)
    {
        if ((mazeGrid[getIndex(y-1,x)] & MARKED) != 0)
        {
            nbrs.push_back(tuple<int, int>({y-1, x}));
        }
    }
    if (y+1 < height)
    {
        if ((mazeGrid[getIndex(y+1,x)] & MARKED) != 0)
        {
            nbrs.push_back(tuple<int, int>({y+1, x}));
        }
    }

    tuple<int,int> ret = nbrs[(rand() % nbrs.size())];

    return ret;
}

void Prims::addMark(int x, int y)
{
    /*
     * This function takes in a y, x coordinate and if that coordinate is valid
     * marks that position as availabe for the algorithim
     * also adds that point to a markedPoints vector
     */
    if ((x >= 0) && (y >= 0) && (x < width) && (y < height))
    {
        if (mazeGrid[getIndex(y,x)] == 0)
        {
            mazeGrid[getIndex(y,x)] |= AVAILABLE;
            markedPoints.push_back(tuple<int,int>(y,x));
        }
    }

}

void Prims::mark()
{
    mark((rand() % width), (rand() % height));
}

void Prims::mark(int x, int y)
{
    /*
     * Markes the given y,x coordinate and all neighbours
     */
    mazeGrid[getIndex(y,x)] |= MARKED;
    addMark(x-1, y);
    addMark(x+1, y);
    addMark(x, y-1);
    addMark(x, y+1);
}

void Prims::run()
{

    mark(); // marks a random point to start from
    while (markedPoints.size() != 0)
    {
        int x,y,x2,y2;
        
        // put a random point of available points to the back
        swap(markedPoints[(rand() % markedPoints.size())], markedPoints.back());

        // get the random point
        tuple<int, int> point = markedPoints.back();

        markedPoints.pop_back();

        tie(y,x) = point;

        // get a random neighbour from that point
        tuple<int, int> rNbr = getRandomNeighbour(y, x);

        tie(y2,x2) = rNbr;


        int dir = direction(x, y, x2, y2);

        // mark the current point's direction
        mazeGrid[getIndex(y, x)] |= dir;
        // mark the neighbours direction as the opposite direction
        mazeGrid[getIndex(y2, x2)] |= OPPOSITE_DIRECTION[dir];

        pathGrid[getIndex(y, x)] = 1;
        pathGrid[getIndex(y2, x2)] = 1;

        // mark the current point (making valid neighbours available)
        mark(x,y);
        
        if ( DISPLAY )
            {
                printGrid();
                Sleep(DELAY);
            }


        pathGrid[getIndex(y, x)] = 0;
        pathGrid[getIndex(y2, x2)] = 0;
    }
    if ( DISPLAY )
    {
        printGrid();
        Sleep(DELAY);
    }


}

int Prims::direction(int x, int y, int x2, int y2)
{
    if( x < x2 ){return E;}
    if ( x > x2){return W;}
    if ( y < y2){return S;}
    else{return N;}
}


int * Prims::getMaze()
{
    return mazeGrid;
}

Prims::~Prims()
{
    delete [] mazeGrid;
    delete [] pathGrid;

}




