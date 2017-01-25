//
// Created by maor on 22/11/16.
//
#include <iostream>
#include <vector>
#include "Grid2D.h"
using namespace std;
//constructors.
Grid2D::Grid2D() {

}
Grid2D::Grid2D(int width, int height) {
    width_x = width;
    height_y = height;
    vector<vector<Point*> > matrix;
    matrix.resize(width_x);
    //create matrix2D
    for(int i = 0 ; i < width_x; i++) {
        (matrix.at(i)).resize(height_y);
        for(int j = 0 ; j < height_y; j++){
            matrix[i][j] =  new Point(i,j);
        }
    }
    theGrid = matrix;
}
int Grid2D::getHeight_y() {
    return this->height_y;
}

int Grid2D::getWidth_x() {
    return this->width_x;
}

vector<vector<Point*> > Grid2D::getMatrix() {
    return this->theGrid;
}



//check if the point in the grid's range
bool Grid2D ::isInRange(Intersection* inter) {
    Point* point = (Point*)inter;
    return !(point->getX() < 0 || point->getX() >= this->width_x
             || point->getY() < 0 || point->getY() >= this->height_y);

}

//returns array of neighbors intersections
vector<Intersection*> Grid2D::neighbors(Intersection* inter) {
    Point* point = (Point*)inter;
    int x = point->getX();
    int y = point->getY();
    vector<Point> arrayPoints;
    arrayPoints.resize(4);
    vector<Intersection*> realNeighbors;
    arrayPoints[0] = Point(x - 1, y);
    arrayPoints[1] = Point(x, y+1);
    arrayPoints[2] = Point(x + 1, y);
    arrayPoints[3] = Point(x, y - 1);
    for(int i = 0; i < 4; i++){
        if(isInRange(&arrayPoints[i])){
            int tempx = arrayPoints[i].getX();
            int tempy = arrayPoints[i].getY();
            if(!(this->theGrid[tempx][tempy]->isObstacle())) {
                realNeighbors.push_back(this->theGrid[tempx][tempy]);
            }
        }
    }
    return realNeighbors;
}

//clean the world from any data
void Grid2D::reworld() {
    for(int i = 0 ; i < height_y; i++) {
        for(int j = 0 ; j < width_x; j++){
            this->theGrid[j][i]->clean();
        }
    }

}
//get the intersection from the map.
Intersection *Grid2D::getIntersect(Intersection * inter) {
    if(this->isInRange(inter)){
        Point* point = (Point*)inter;
        int x = point->getX();
        int y = point->getY();
        return this->theGrid[x][y];
    }
    cout << "->->->ERROR point not in range!<-<-<-" << endl;
    return NULL;
}
//destructor
Grid2D::~Grid2D() {
    for(int i = 0 ; i < width_x; i++) {
        for(int j = 0 ; j < height_y; j++){
            delete theGrid.at(i).at(j);
        }
    }
}
//add an obstacle to the grid at the given point.
void Grid2D::addObstacle(int m, int n) {
    (this->theGrid[m][n])->updateObstacle();
}

