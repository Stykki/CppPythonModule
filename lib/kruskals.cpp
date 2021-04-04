#include <iostream>
#include <Windows.h>
#include <string>
#include <random>
#include <algorithm>
#include <random>
#include <vector>

#ifndef Maze
#include "mazeC.cpp"
#endif


using namespace std;

int myrandom (int i) { return std::rand()%i;}

class kTree
{
    private:

    public:
        kTree* parent = nullptr;
        int id;
        kTree();
        void setParent(kTree* newP);
        kTree* root();
        bool sameParent(kTree* otherP);
        void connectTrees(kTree* otherT);
        void setId(int d);
};

kTree::kTree()
{
    return;
}

void kTree::setId(int d)
{
    id = d;
}

void kTree::setParent(kTree* newP)
{
    parent = newP;
}

kTree* kTree::root()
{
    if (parent == nullptr)
    {
        return this;
    }
    else
    {
        return parent->root();
    }
}

bool kTree::sameParent(kTree* otherP)
{
    if(root()->id == otherP->root()->id)
    {
        return 1;
    }
    return 0;
}


void kTree::connectTrees(kTree* otherT)
{
    otherT->root()->setParent(this);
}


class Kruskals: public Maze
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
        vector<vector<int>>* edges = new vector<vector<int>>;

        kTree * sets; 

    public:

        Kruskals(int w, int h);
        ~Kruskals();
        void run(bool display);
        void printSetId();
        void printDigits();
        int * getMaze();



};

Kruskals::Kruskals(int w, int h)
{
    int NSWE[4] = {N,S,W,E};
    Maze::setDirections(NSWE);
    width = w;
    height = h;
    mazeGrid = new int[width * height];
    pathGrid = new bool[width * height];
    sets = new kTree[width * height]; 
    for (int i = 0; i < width*height; i++)
    {
        mazeGrid[i] = 0;
        pathGrid[i] = 0;
        sets[i] = kTree();
        sets[i].setId(i);
    }
    for(int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (y > 0)
            {
                vector<int> b = {x, y, N};
                edges->push_back(b);
            }
            if (x > 0)
            {
                vector<int> b = {x, y, W};
                edges->push_back(b);

            }
        }

    }
    random_shuffle(edges->begin(), edges->end(), myrandom);
}



void Kruskals::run(bool display)
{
    while(edges->size() > 0)
    {
        int x = edges->back()[0];
        int y = edges->back()[1];
        int direction = edges->back()[2];
        edges->pop_back();

        int nx = x + MOVE_X_DIRECTION[direction];
        int ny = y + MOVE_Y_DIRECTION[direction];

        kTree set_1 = sets[getIndex(y,x)];
        kTree set_2 = sets[getIndex(ny,nx)];
        
        if(!set_1.sameParent(&set_2))
        {
            int s1Parent = set_1.root()->id;
            int s2Parent = set_2.root()->id;

            sets[s1Parent].parent = &sets[s2Parent];

            mazeGrid[getIndex(y,x)] |= direction;
            mazeGrid[getIndex(ny,nx)] |= OPPOSITE_DIRECTION[direction];

                pathGrid[getIndex(y,x)] = 1;
                pathGrid[getIndex(ny,nx)] = 1;
                // PRINT GRID
        if ( DISPLAY )
        {
            printGrid();
            Sleep(DELAY);
        }

                pathGrid[getIndex(y,x)] = 0;
                pathGrid[getIndex(ny,nx)] = 0;
        }
    }
}

Kruskals::~Kruskals()
{
    delete edges;
    delete [] mazeGrid;
    delete [] pathGrid;
    delete [] sets;
}

int * Kruskals::getMaze()
{
    return mazeGrid;
}
