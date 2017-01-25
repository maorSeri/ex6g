//
// Created by maor on 22/11/16.
//

#ifndef EX1_ADVANCED_PROGRAMING_RBS_H
#define EX1_ADVANCED_PROGRAMING_RBS_H

#include "Map.h"
#include <queue>
#include <iostream>
#include <stack>

/*
 * BFS class.
 * print the path between 2 intersections by using the bfs algorithm
 */
class BFS {
    Map* myMap;
    Intersection* start;
    Intersection* end;
    stack<Intersection *> stackPath;
public:
    //bfs constructors
    BFS();

    virtual ~BFS();

    BFS(Map*,Intersection*,Intersection*);

    stack<Intersection *> getStackPath();
    //runs the bfs algorithm.
    void algorithm();
    //print the path (intersections).
    void printPath();
    //connect the 2 funcs. algorithm + print.
    void runBFS();

};


#endif //EX1_ADVANCED_PROGRAMING_RBS_H
