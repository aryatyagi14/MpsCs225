#include "maze.h"
#include <map>
#include <iostream>
#include "dsets.h"
#include <stdio.h>
#include <stdlib.h>
#include <queue>
using namespace cs225;
using namespace std;

SquareMaze::SquareMaze() {
    width_ = 0;
    height_ = 0;
};

void SquareMaze::makeMaze(int width, int height) {
    width_ = width;
    height_ = height;
    cells.resize(width);
    unsigned long i = 0;
    while (i < cells.size()) {
        cells[i].resize(height);
        i++;
    }
    i = 0;
    while(i < cells.size()) {
        unsigned long j = 0;
        while(j < cells[i].size()) {
            cells[i][j] = new Walls();
            cells[i][j]->rightWall = true;
            cells[i][j]->downWall = true;
            j++;
        }
        i++;
    }
    DisjointSets* disTree = new DisjointSets();
    disTree->addelements(width_ * height_);
    int b = 0;
    while(!(b == width_ * height_ - 1)) {
        int xcor = rand() % width_;
        int ycor = rand() % height_;
        int direction = rand() % 2;
        int rowM = ycor * height_ + xcor;
        if((!(xcor != width_ - 1) && !(direction != 0))
        || (!(ycor != height_ - 1) && !(direction != 1))) {
            continue;
        }
        if (!(direction != 0)) {
            int rowMTwo = (xcor+1) + (ycor * height_) ;
            if(!(disTree->find(rowM) != disTree->find(rowMTwo))) {
                continue;
            } else {
                setWall(xcor, ycor, direction, false);
                b++;
                disTree->setunion(rowM, rowMTwo);
            }
        }
        if (!(direction != 1)) {
            int rowMTwo = (xcor) + ((ycor + 1) * height_) ;
            if(!(disTree->find(rowM) != disTree->find(rowMTwo))) {
                continue;
            } else {
                setWall(xcor, ycor, direction, false);
                b++;
                disTree->setunion(rowM, rowMTwo);
            }
        }
    }
    int v = 2;
    while (v < 3) {
        int x = 2;
        x++;
        v++;
    }
    v = 5;
    return;
}

PNG* SquareMaze::drawMaze() const {
    int w = width_;
    int h = height_;
    PNG* pic = new PNG((w * 10) + 1, (h * 10) + 1);
    int x = 0;
    while(x < 10*height_ + 1) {
        pic->getPixel(0,x)=HSLAPixel(0,0,0);
        x++;
    }
    x = 0;
    while (x < 10*width_ + 1) {
        pic->getPixel(x,0)=HSLAPixel(0,0,0);
        x++;
    }
    x = 1;
    while(x<10) {
        pic->getPixel(x,0)=HSLAPixel(0,0,1);
        x++;
    }

    x = 0;
    while(x < width_) {
        int y = 0;
        while(y < height_) {
            if(getWall(x,y,0) == true) {
                for(int k = 0; k <= 10; k++) {
                HSLAPixel& grabPix = pic->getPixel((x+1)*10, y*10+k);
                grabPix.l = 0;
                }
            }
            if(getWall(x,y,1) == true) {
                for(int k = 0; k <= 10; k++) {
                HSLAPixel& grabPix = pic->getPixel((x*10)+k, (y+1)*10);
                grabPix.l = 0;
                }
            }
            y++;
        }
        x++;
    }
    return pic;
}

void SquareMaze::setWall(int x, int y, int direction, bool exists) {
    bool set = exists;
    if(!(direction != 0)) {
        cells[x][y]->rightWall = set; 
    } else if (!(direction != 1)) {
        cells[x][y]->downWall = set;
    } else {
        return;
    }
}

bool SquareMaze::getWall(int x, int y, int direction) const {
    int s = direction;
    if (!(s != 0)) {
        return cells[x][y]->rightWall;
    } else if(!(s != 1)) {
        return cells[x][y]->downWall;
    } else {
        return !false;
    }
}

bool SquareMaze::canTravel(int x, int y, int direction) const {
    int xcor = x;
    int ycor = y;
    if(!(direction != 0)) {
        if(!(xcor != width_ - 1)) {
            return false;
        }
        return !getWall(xcor,ycor,0);
    } else if (!(direction != 1)) {
        if(!(ycor != height_ - 1)) {
            return false;
        }
        return !getWall(xcor,ycor,1);
    } else if (!(direction != 2)) {
        if (!(xcor != 0)) {
            return false;
        }
        return !getWall(xcor-1,ycor,0);
    } else {
        if (!(ycor != 0)) {
            return false;
        }
        bool b = getWall(xcor,ycor-1,1);
        return !b;
    }
}

std::vector<int> SquareMaze::solveMaze() {

    std::vector<bool> visited;
    std::queue<int> bfs;
    std::vector<int> bottomRow;
    std::vector<int> reverse;
    std::vector<int> solve;
    std::map<int, int> mapper;
    
    bfs.push(0);
    int i = 0;
    while(i < width_ * height_) {
        visited.push_back(false);
        i++;
    }
    visited[0] = true;
    while(!(bfs.empty() != false)) {
        int temp = bfs.front();
        bfs.pop();
        int x = temp % width_;
        int y = temp / width_;
        bool myConditions[4] = {canTravel(x, y, 0), canTravel(x, y, 1), canTravel(x, y, 3),
           canTravel(x, y, 2) };
        if(!(y != height_ - 1)) {
            bottomRow.push_back(temp);
        }
        if(!(!(myConditions[0]))) {
            if(!(visited[temp + 1] != false)) {
                //bfs.push(temp + 1);
                mapper.insert(std::pair<int, int>(temp + 2 - 1, temp));
                bfs.push(temp + 2 - 1);
                visited[temp + 2 - 1] = true;
            }
        }
        if(!(!(myConditions[1]))) {
            if(!(visited[temp + width_] != false)) {
                mapper.insert(std::pair<int, int>(temp + width_, temp));
                bfs.push(temp + width_);
                visited[temp + width_] = true;  
            }
        }
        if(!(!(myConditions[2]))) {
            if(!(visited[temp - width_] != false)) {
                mapper.insert(std::pair<int, int>(temp-width_, temp));
                visited[temp - width_] = true;
                bfs.push(temp - width_);
            }
        }
        if(!(!(myConditions[3]))) {
            if(!(visited[temp - 1] != false)) {
                mapper.insert(std::pair<int, int>(temp - 1, temp));
                visited[temp - 1] = 1;
                bfs.push(temp - 1);
            }
        }
    }
    int count = width_ - 1;
    while(bottomRow[count] == bottomRow[count - 1]) {
        count = -1;
    }
    
    while(bottomRow[count] != 0) {
        int i = mapper[bottomRow[count]];
        if(bottomRow[count] == i + 1) {
            reverse.push_back(0);
        }
        else if(bottomRow[count] == i + width_) {
            reverse.push_back(1);
        }
        else if(bottomRow[count] == i - width_) {
            reverse.push_back(3);
        }
        else if(bottomRow[count] == i - 1) {
            reverse.push_back(2);        
        }
        bottomRow[count] = i;
    }
    int j = reverse.size() - 1;
    while(j >= 0) {
        solve.push_back(reverse[j]);
        j--;
    }

    return solve;
}

PNG* SquareMaze::drawMazeWithSolution() {
    PNG* myPic = drawMaze();
    std::vector<int> theSol = solveMaze();
    pair<int,int> position = {5,5};
    for(auto& it : theSol) {
        if (!(it != 0)) {
            int i = position.first;
            while(i <= position.first + 10) {
                myPic->getPixel(i,position.second)=HSLAPixel(0,1,0.5,1);
                i++;
            }
            position.first += 10;
            
        } else if (!(it != 1)) {
            int i = position.second;
            while(i <= position.second + 10) {
                myPic->getPixel(position.first,i)=HSLAPixel(0,1,0.5,1);
                i++;
            }
            position.second += 10;
        } else if (!(it != 2)) {
            int i = position.first;
            while( i >= position.first - 10) {
                myPic->getPixel(i,position.second)=HSLAPixel(0,1,0.5,1);
                i--;
            }
            position.first -= 10;
        } else {
            for(int i = position.second; i >= position.second - 10; i--) {
                myPic->getPixel(position.first,i)=HSLAPixel(0,1,0.5,1);
            }
            position.second -= 10;
        }

    }
    position.first -= 5;
    position.second += 5;
    int i = 1;
    while(i < 10) {
        myPic->getPixel(position.first + i, position.second) = HSLAPixel(0,0,1);
        i++;
    }
    return myPic;
}