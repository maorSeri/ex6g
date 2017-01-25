//
// Created by maor on 22/11/16.
//

#ifndef EX1_ADVANCED_PROGRAMING_GRID2D_H
#define EX1_ADVANCED_PROGRAMING_GRID2D_H

#include <vector>
#include "Map.h"
#include "Point.h"
using namespace std;
/*
 * Grid2d class.
 * inheritance from Map. present a 2D world.
 */
class Grid2D : public Map{

private:
    int width_x, height_y;
    vector<vector<Point*> > theGrid;

public:
    //constructors.
    Grid2D();
    Grid2D(int, int);
    int getWidth_x();
    int getHeight_y();
    vector<vector<Point*> > getMatrix();
    //returns if intersection is in map.
    bool isInRange(Intersection*);
    //get the intersection from the map.
    Intersection* getIntersect(Intersection*);
    //returns array of neighbors intersections
    vector<Intersection*> neighbors(Intersection* inter);
    //add an obstacle to the grid at the given point.
    void addObstacle(int m,int n);
    /*
     * if we want use them we should care about the matrix!!
     * void setWidth(int);
     * void setHeight(int);
    */

    //clean the world from any data
    void reworld();
    //destructor
    virtual ~Grid2D();

};


#endif //EX1_ADVANCED_PROGRAMING_GRID2D_H
