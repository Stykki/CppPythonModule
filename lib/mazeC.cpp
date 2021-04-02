#include <iostream>


class Maze
{
    protected:

        int * cMaze;

        int width;
        int height;
        int N,S,E,W;

        void print();

    public:

        int getIndex(int x, int y);
        void run(bool display);
        int * getMaze();

        Maze();


};


int Maze::getIndex(int x, int y)
{
        return (x * height + y) ;
}

Maze::Maze()
{
    return;
}


