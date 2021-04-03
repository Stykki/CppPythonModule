#include <iostream>
#include <random>
#include <vector>
#include <tuple>
#include "mazeC.cpp"


using namespace std;


class Prims: public Maze

{
    protected:
        int N = 1;
        int S = 2;
        int W = 4;
        int E = 8;
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

        void run(bool display);
        void displayNumbers();

        Prims(int w, int h);

};

Prims::Prims(int w, int h)
{
    int NSWE[4] = {N,S,W,E};
    width = w;
    height = h;
    Maze::setDirections(NSWE);
    width = w;
    height = h;
    mazeGrid = new int[width * height];
    pathGrid = new bool[width * height];

    for (int i = 0; i < width*height; i++)
    {
        mazeGrid[i] = 0;
        pathGrid[i] = 0;
    }

}

tuple<int,int> Prims::getRandomNeighbour(int y, int x)
{
    
    vector<tuple<int, int>> nbrs;
    if (x > 0)
    {
        if ((mazeGrid[getIndex(y,x-1)] & MARKED) != 0)
        {
            nbrs.push_back(tuple<int, int>({y, x-1}));

        }
    }
    if (x+1 < height)
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
    if (y+1 < width)
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
    if ((x >= 0) && (y >= 0) && (x < height) && (y < width))
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
    mazeGrid[getIndex(y,x)] |= MARKED;
    addMark(x-1, y);
    addMark(x+1, y);
    addMark(x, y-1);
    addMark(x, y+1);
}

void Prims::run(bool display)
{
    mark();
    cout << "MARKED SIZE " << markedPoints.size() << endl;
    while (markedPoints.size() != 0)
    {
        int x,y,x2,y2;
        
        swap(markedPoints[(rand() % markedPoints.size())], markedPoints.back());

        tuple<int, int> point = markedPoints.back();

        markedPoints.pop_back();

        tie(y,x) = point;

        tuple<int, int> rNbr = getRandomNeighbour(y, x);

        tie(y2,x2) = rNbr;


        int dir = direction(x, y, x2, y2);
        cout << "Pos normal y " << y << " x " << x << endl;
        cout << "Pos nbr    y " << y2 << " x " << x2 << endl;
        cout << "Directon   " << dir << endl;

        mazeGrid[getIndex(y, x)] |= dir;
        mazeGrid[getIndex(y2, x2)] |= OPPOSITE_DIRECTION[dir];

        pathGrid[getIndex(y, x)] = 1;
        pathGrid[getIndex(y2, x2)] = 1;

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
void Prims::displayNumbers()
{
    for (int i = 0; i<10; i++){
        for (int d = 0; d<10; d++){
            cout << "[" << mazeGrid[getIndex(i,d)] << "]";
        }
        cout << endl;
    }

}

int main(){
    
    Prims T = Prims(10, 10);
    T.run(1);
    // T.displayNumbers();
    

    return 0;
}

