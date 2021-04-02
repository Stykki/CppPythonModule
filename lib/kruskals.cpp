#include <iostream>
#include <Windows.h>
#include <string>
#include <random>
#include <algorithm>
#include <random>
#include <vector>
#include "mazeC.cpp"


using namespace std;

int myrandom (int i) { return std::rand()%i;}

class kTree
{
    private:
        kTree* parent = nullptr;

    public:
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

        int * mazeGrid;
        bool * pathGrid;
        kTree * sets; 

    public:

        Kruskals(int w, int h);
        ~Kruskals();
        void run(bool display);
        void printGrid();
        void printSetId();
        void printDigits();



};

Kruskals::Kruskals(int w, int h)
{
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


void Kruskals::printDigits()
{
for ( int i = 0; i < 10; i ++ )
    {

        for ( int y = 0; y < 10; y ++ )
        {
            cout << "["<<  mazeGrid[getIndex(i, y)] << "]";

        }
        cout << endl;
    }


}

void Kruskals::printGrid()
{
    SetConsoleOutputCP(CP_UTF8);
    string mazeString = "";
    mazeString += "╔";

    for (int x = 0 ; x < width-1; x++)
    {

        mazeString += "═══";

        if (((mazeGrid[getIndex(0,x)] & S) != 0 && ((mazeGrid[getIndex(0,x)] & E) == 0)) || (mazeGrid[getIndex(0,x)] == 0))
        {
             mazeString += "╦";
        }
        else
        {
            mazeString += "═";

        }
    }
    mazeString += "═══╗\n";


    for ( int y = 0; y < height; y++)
    {

        string firstLine = "║";
        string secondLine = "";
        if (y == height-1)
        {

            secondLine += "╚";
        }
        else
        {
            if(((mazeGrid[getIndex(y,0)] & E) != 0 && (mazeGrid[getIndex(y,0)] & S) == 0))
            {
                secondLine += "╠";
            }
            else
            {
                secondLine += "║";
            }

        }
        for (int x = 0; x < width; x++)
        {
            char pathChar;
            if (pathGrid[getIndex(y,x)])
            {
                pathChar = '#';
            }
            else
            {
                pathChar = ' ';
            }

            // FIRST LINE OF EACH SPOT
            if (pathGrid[getIndex(y,x)])
            {

                if ( ((mazeGrid[getIndex(y,x)] & E) != 0) && (mazeGrid[getIndex(y,x)] & W) != 0) 
                {
                    firstLine += pathChar;
                    firstLine += pathChar;
                    firstLine += pathChar;
                    firstLine += pathChar;
                }
                else if(((mazeGrid[getIndex(y,x)] & (N+S)) != 0 && (mazeGrid[getIndex(y,x)] & (E+W)) == 0))
                {
                    firstLine += " ";
                    firstLine += pathChar;
                    firstLine += " ";
                    firstLine += "║";
                }
                else if((mazeGrid[getIndex(y,x)] & E) != 0 )
                {
                    firstLine += " ";
                    firstLine += pathChar;
                    firstLine += pathChar;
                    firstLine += pathChar;
                }
                else
                {
                    firstLine += pathChar;
                    firstLine += pathChar;
                    firstLine += " ";
                    firstLine += "║";

                }
            }

            else
            {
                if ((mazeGrid[getIndex(y,x)] & E) == 0)
                {
                    firstLine += pathChar;
                    firstLine += pathChar;
                    firstLine += pathChar;
                    firstLine += "║";
                }
                else
                {
                    firstLine += pathChar;
                    firstLine += pathChar;
                    firstLine += pathChar;
                    firstLine += pathChar;
                }


            }
            //SECOND LINE OF EACH SPOT

            // for grid numbers 0, 1, 4, 5 N AND W
            if ((mazeGrid[getIndex(y,x)] & (S+E)) == 0)
            {

                if (x+1 == width || y+1 == height)
                {
                    if ( y == height -1 && x == width-1)
                    {
                        secondLine += "═══╝";
                    }
                    else if ( y == height -1)
                    {
                        secondLine += "═══╩";
                    }
                    else
                    {
                        secondLine += "═══╣";
                    }

                }


                else if(((mazeGrid[getIndex(y,x+1)] & S) == 0) && (mazeGrid[getIndex(y+1,x)] & E) == 0) 
                {
                    secondLine += "═══╬";
                }
                else if (((mazeGrid[getIndex(y,x+1)] & S) == 0) && (mazeGrid[getIndex(y+1,x)] & E) != 0) 
                {
                    secondLine += "═══╩";
                }
                else if (((mazeGrid[getIndex(y,x+1)] & S) != 0) && (mazeGrid[getIndex(y+1,x)] & E) != 0) 
                {
                    secondLine += "═══╝";
                }

                else
                {

                    if ( y == height -1 && x == width-1)
                    {
                        secondLine += "═══╝";
                    }
                    else if ( y == height -1)
                    {
                        secondLine += "═══╩";
                    }
                    else
                    {
                        secondLine += "═══╣";
                    }


                }
            }
            else if ((mazeGrid[getIndex(y,x)] & (E)) == 0)
            {
                if (x+1 == width || y+1 == height)
                {
                    secondLine += " ";
                    secondLine += pathChar;
                    secondLine += " ";
                    secondLine += "║";

                }
                else if(((mazeGrid[getIndex(y,x+1)] & S) == 0) && (mazeGrid[getIndex(y+1,x)] & E) == 0) 
                {
                    secondLine += " ";
                    secondLine += pathChar;
                    secondLine += " ";
                    secondLine += "╠";
                }
                else if((mazeGrid[getIndex(y,x+1)] & S) == 0) 
                {
                    secondLine += " ";
                    secondLine += pathChar;
                    secondLine += " ";
                    secondLine += "╚";
                }
                else
                {
                    secondLine += " ";
                    secondLine += pathChar;
                    secondLine += " ";
                    secondLine += "║";

                }

            }
            else if ((mazeGrid[getIndex(y,x)] & (S)) == 0)
            {
                if (x+1 == width || y+1 == height)
                {
                    secondLine += "════";
                }
                else if(((mazeGrid[getIndex(y+1,x)] & E) == 0) && (mazeGrid[getIndex(y,x+1)] & S) == 0) 
                {
                    secondLine += "═══╦";
                }
                else if((mazeGrid[getIndex(y+1,x)] & E) == 0)
                {
                    secondLine += "═══╦";
                }
                else 
                {
                    secondLine += "════";
                }

            }
            else
            {

                if (x+1 == width || y+1 == height)
                {
                    secondLine += " ";
                    secondLine += pathChar;
                    secondLine += " ";
                    secondLine += "═";
                }
                else if(((mazeGrid[getIndex(y+1,x)] & E) == 0) && (mazeGrid[getIndex(y,x+1)] & S) == 0) 
                {
                    secondLine += " ";
                    secondLine += pathChar;
                    secondLine += " ";
                    secondLine += "╔";
                }
                else if(((mazeGrid[getIndex(y+1,x)] & E) == 0) && (mazeGrid[getIndex(y,x+1)] & S) != 0) 
                {
                    secondLine += " ";
                    secondLine += pathChar;
                    secondLine += " ";
                    secondLine += "║";
                }
                else
                {
                    secondLine += " ";
                    secondLine += pathChar;
                    secondLine += " ";
                    secondLine += "═";
                }
            }

        }
    
        mazeString += firstLine;
        mazeString += "\n";
        mazeString += secondLine;
        mazeString += "\n";


    }

    cout << mazeString << endl;

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
            set_1.connectTrees(&set_2);
            mazeGrid[getIndex(y,x)] |= direction;
            mazeGrid[getIndex(ny,nx)] |= OPPOSITE_DIRECTION[direction];

            pathGrid[getIndex(y,x)] = 1;
            pathGrid[getIndex(ny,nx)] = 1;
            // PRINT GRID
            _sleep(2);
            printGrid();

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




int main(){

    Kruskals T = Kruskals(20, 20);
    T.printGrid();
    T.run(1);
    return 0;
}

