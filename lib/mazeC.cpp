#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

class Maze
{
    protected:


        int DELAY = 200;
        bool DISPLAY = 1;


        int * cMaze;

        int width;
        int height;
        int N,S,E,W;

        void print();

        int * mazeGrid;
        bool * pathGrid;


    public:

        void setDirections(int *NSEW);
        void run(bool display);
        void printGrid();

        int getIndex(int x, int y);

        void toggleDisplay();

        void setDelay(int del);

        Maze();

};

void Maze::toggleDisplay()
{

    DISPLAY = ! DISPLAY;
}

void Maze::setDelay(int del)
{
    DELAY = del;
}


void Maze::printGrid()
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

int Maze::getIndex(int y, int x)
{
        return (y * width + x) ;
}

Maze::Maze(){};




void Maze::setDirections(int *NSWE )
{
    N = NSWE[0];
    S = NSWE[1];
    W = NSWE[2];
    E = NSWE[3];
    return;
}


