//
// Created by maor on 22/11/16.
//

#ifndef EX1_ADVANCED_PROGRAMING_MAP_H
#define EX1_ADVANCED_PROGRAMING_MAP_H

#include "Intersection.h"
#include <vector>
using namespace std;

/*
 * map class
 * abstract class. present the world. knows its intersections.
 */
class Map {

public:
    //map constructor.
    Map(){};

    virtual ~Map() {
    }

    //returns if intersection is in map.
    virtual bool isInRange(Intersection*) = 0;
    //returns array of neighbors intersections
    virtual vector<Intersection*> neighbors(Intersection* inter) = 0;
    //clean the world from any data
    virtual void reworld() = 0;
    //get the intersection from the map.
    virtual Intersection* getIntersect(Intersection*) = 0;



};


#endif //EX1_ADVANCED_PROGRAMING_MAP_H
