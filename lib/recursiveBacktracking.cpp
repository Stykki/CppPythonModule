#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include "mazeC.cpp"

using namespace std;
int myrandom (int i) { return std::rand()%i;}

class RecursiveBacktracking: public Maze {

    protected:
        int N = 1;
        int S = 2;
        int W = 4;
        int E = 8;
                    //         N S    W       E
        int moveX[9] =      {0,0,0,0,-1,0,0,0,1};
        int moveY[9] =      {0,-1,1,0,0,0,0,0,0};
        int opposite[9] =   {0,S,N,0,E,0,0,0,W};
        int cX;
        int cY;
        int width;
        int height;
        int getNewXCoord(int x, int directions);
        int getNewYCoord(int y, int directions);
        bool isMarked(int y, int x);
        bool markGrid(int y, int x, bool markBool);
        bool withinBounds(int y, int x);
        void addDirectionToGrid(int y, int x, int direction);

    public:
        void run(bool display);
        void fillMaze();
        void makeWayForMaze(int y, int x, bool display);
        void displayNumbers();
        void displayPath();
        RecursiveBacktracking(int h, int w);

    
};

RecursiveBacktracking::RecursiveBacktracking(int h, int w) {
    cX = rand() % w;
    cY = rand() % h;
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

void RecursiveBacktracking::displayNumbers()
{
    for (int i = 0; i<height; i++){
        for (int d = 0; d<width; d++){
            cout << "[" << mazeGrid[getIndex(i,d)] << "]";
        }
        cout << endl;
    }
}

void RecursiveBacktracking::displayPath()
{
    for (int i = 0; i<height; i++){
        for (int d = 0; d<width; d++){
            cout << "[" << pathGrid[getIndex(i,d)] << "]";
        }
        cout << endl;
    }
}

void RecursiveBacktracking::run(bool display) {
    makeWayForMaze(cY, cX, display);
    cX = -1;
    cY = -1;
    // display maze

}

void RecursiveBacktracking::makeWayForMaze(int y, int x, bool display) {
    vector<int> directions = {N,S,W,E};
    random_shuffle(directions.begin(), directions.end(), myrandom);
    bool marked = markGrid(y, x, true);
    // dipslay maze
    // displayNumbers();
    displayPath();
    cout << "aaaaa" << endl;
    // printGrid();

    for (int i = 0; i < directions.size(); i++) {
        cout << "getting new coords" << endl;
        int newX = getNewXCoord(x, directions[i]);
        int newY = getNewYCoord(y, directions[i]);

        
        if (withinBounds(newY, newX)) {
            if (!isMarked(newY, newX)) {
                addDirectionToGrid(cY, cX, directions[i]);
                addDirectionToGrid(newY, newX, opposite[directions[i]]);
                cX = newX;
                cY = newY;
                makeWayForMaze(newY, newX, display);
                cX = x;
                cY = y;
                // display maze
                // displayNumbers();
                displayPath();
                cout << "aaaaa" << endl;
                // printGrid();
            }
        }
    }
    markGrid(y, x, false);
}

bool RecursiveBacktracking::markGrid(int y, int x, bool markBool) {
    if (withinBounds(y, x)) {
        pathGrid[getIndex(y, x)] = markBool;
        return true;
    }
    return false;
}

bool RecursiveBacktracking::withinBounds(int y, int x) {
    if (((x >= 0) && (x < width)) && (y >= 0) && (y < height)) {
        return true;
    }
    return false;
}

int RecursiveBacktracking::getNewXCoord(int x, int direction) {
    return x + moveX[direction];
}

int RecursiveBacktracking::getNewYCoord(int y, int direction) {
    return y + moveY[direction];
}

bool RecursiveBacktracking::isMarked(int y, int x) {
    if (mazeGrid[getIndex(y, x)] == 0) {
        return false;
    }
    return true;
}

void RecursiveBacktracking::addDirectionToGrid(int y, int x, int direction) {
    if (withinBounds(y, x)) {
        mazeGrid[getIndex(y, x)] |= direction;
    }
}

int main() {
    RecursiveBacktracking R = RecursiveBacktracking(10, 10);
    R.run(1);
    R.displayNumbers();

    return 0;
}