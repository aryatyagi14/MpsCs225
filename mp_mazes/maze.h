#pragma once
#include "cs225/PNG.h"
#include <vector>
#include <map>
using namespace cs225;
using namespace std;

struct Walls {
	bool rightWall;
	bool downWall;
};
class SquareMaze
{
	//storing all vectors as 1 dimensional
	public:
	    SquareMaze();
	    void makeMaze(int w,int h);
        bool canTravel(int x, int y, int dir) const;
        void setWall(int x, int y, int dir, bool exists);
		bool getWall(int x, int y, int dir) const;
        vector<int> solveMaze();
        PNG * drawMaze() const;
        PNG* drawMazeWithSolution();
        
    private:
        vector<vector<Walls*>> cells;
        int width_;
        int height_;
};
