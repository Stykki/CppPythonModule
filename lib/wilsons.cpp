#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include "mazeC.cpp"
#include <string>


class Wilsons: public Maze 
{
    protected:
        int N = 1;
        int S = 2;
        int W = 4;
        int E = 8;
        int remaining;
        //                         0    N  S  3   W  5  6  7  E
        int MOVE_X_DIRECTION[9] = {0 ,  0, 0, 0, -1, 0, 0, 0, 1};
        int MOVE_Y_DIRECTION[9] = {0 , -1, 1, 0,  0, 0, 0, 0, 0};
        int OPPOSITE_DIRECTION[9] = {0, S, N, 0,  E, 0, 0, 0, W};
        int currX;
        int currY;
        int in = 16;
        bool *availableCells;
        bool isPosValid(int x, int y);
        // unordered_map<pair<int, int>, int> visits;
        int *visits;
        vector<int> getXgetY();


    public:
        Wilsons(int w, int h);
        void run(bool display);
        vector<vector<int>> walk();

};

Wilsons::Wilsons(int w, int h)
{
    int NSWE[4] = {N,S,W,E};
    Maze::setDirections(NSWE);
    width = w;
    height = h;

    mazeGrid = new int[width * height];
    pathGrid = new bool[width * height];
    availableCells = new bool[width * height];
    visits = new int[width * height];
    for (int i = 0; i < width*height; i++)
    {
        mazeGrid[i] = 0;
        pathGrid[i] = 0;
        availableCells[i] = 1;
        visits[i] = -1;
    }
    // currX = rand() % width;
    // currY = rand() % height;
    remaining = width * height - 1;
}


void Wilsons::run(bool display)
{
    cout << "in run" << endl;
    int direction;
    vector<int> XandY = getXgetY();
    int x = XandY[0];
    int y = XandY[1];
    availableCells[getIndex(y, x)] = 0;
    mazeGrid[getIndex(y, x)] |= in;     // add direction to grid
    pathGrid[getIndex(y, x)] = false;   // mark grid

    cout << "while remaining" << endl;
    while (remaining > 0) 
    {
        vector<vector<int>> path = walk();
        cout << "out of walk" << endl;
        for (int i = 0; i < path.size() - 1; i++)
        {
            x = path[i][0];
            y = path[i][1];
            direction = path[i][2];
            int newX = x + MOVE_X_DIRECTION[direction];
            int newY = y + MOVE_Y_DIRECTION[direction];
            mazeGrid[getIndex(y, x)] |= direction;
            mazeGrid[getIndex(newY, newX)] |= OPPOSITE_DIRECTION[direction];
            
            // display maze
            pathGrid[getIndex(y, x)] = true;
            printGrid();
            pathGrid[getIndex(y, x)] = false;
            remaining--;
            
        }
    }
    // currX = -1;
    // currY = -1;
    // display maze
    printGrid();
}

vector<vector<int>> Wilsons::walk()
{
    vector<int> XandY = getXgetY();
    currX = XandY[0];
    currY = XandY[1];
    // pair<int,int> xyPair;
    // xyPair.first = currX;
    // xyPair.second = currY;
    // visits[xyPair] = 0;
    visits[getIndex(currY, currX)] = 0;
    
    int startX = currX;
    int startY = currY,

    walking = true;
    vector<int> dir = { N,S,E,W };

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            cout << "[" << mazeGrid[getIndex(i, j)] << "] "; 
        }
        cout << endl;
    }

    while (walking)
    {
        // display maze
        printGrid();
        // sleep
        Sleep(200);
        walking = false;
        random_shuffle(dir.begin(), dir.end());
        for (int i = 0; i< 4; i++)
        {
            int newX = currX + MOVE_X_DIRECTION[dir[i]];
            int newY = currY + MOVE_Y_DIRECTION[dir[i]];
            if (isPosValid(newX, newY))
            {
                // pair<int,int> newPair;
                // newPair.first = currX;
                // newPair.second = currY;
                // visits[newPair] = dir[i];
                visits[getIndex(currY, currX)] = dir[i];

                if (mazeGrid[getIndex(newY, newX)] != 0)
                {
                    cout << "in if" << endl;
                    cout << "Curr x " << currX << " Curr y " << currY << endl;
                    break;
                }
                else 
                {
                    currX = newX;
                    currY = newY;
                    cout << "Curr x " << currX << " Curr y " << currY << endl;
                    walking = true;
                    break;
                }
            }
        }
    }
    vector<vector<int>> path;
    vector<int> eachPath;
    int x = startX;
    int y = startY;
    // pair<int,int> coordPair;
    // coordPair.first = x;
    // coordPair.second = y;
    int direction;
    cout << "before while" << endl;
    while (true) 
    {   
        cout << "x is: " << x << " y is: " << y << endl;
    //     for (int i = 0; i < width; i++) {
    //         for (int j = 0; j < height; j++) {
    //             cout << "[" << visits[getIndex(i, j)] << "] "; 
    //     }
    //     cout << endl;
    // }
        if (visits[getIndex(y, x)] != -1)
        {
            // cout << "getting directions" << endl;
            direction = visits[getIndex(y, x)];
        }
        else 
        {
            break;
        }
        availableCells[getIndex(y,x)] = 0;
        eachPath.push_back(x);
        eachPath.push_back(y);
        eachPath.push_back(direction);
        path.push_back(eachPath);
        x = x + MOVE_X_DIRECTION[direction];
        y = y + MOVE_Y_DIRECTION[direction];
        cout << "new x: " << x << " new y: " << y << endl;
    }
    return path;
}

vector<int> Wilsons::getXgetY() 
{
    vector<int> ret;
    // int ret[2] = {rand() % width, rand() % height};
    int randX = rand() % width;
    int randY = rand() % height;
    
    ret.push_back(randX);
    ret.push_back(randY);
    return ret; 

}

bool Wilsons::isPosValid(int x, int y)
{
    if ((x >= 0) && (y >= 0) && (x < height) && (y < width))
    {
       
        
        return 1;
        
    }
    return 0;
}


int main() {
    Wilsons w = Wilsons(3, 3);
    cout << "gonna run" << endl;
    w.run(1);
    w.printGrid();

    return 0;
}