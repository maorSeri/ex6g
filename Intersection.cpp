//
// Created by maor on 22/11/16.
//

#include <iostream>
#include "Intersection.h"

//constructors.
Intersection::Intersection() {
    visited = false;
    obstacle = false;
    father = NULL;
}

Intersection::Intersection(Intersection* a) {
    a->visited = visited;
    a->father = father;

}
//update the intersection father.
void Intersection::setFather(Intersection * dad) {
    this->father = dad;
}
//update a visit. changes the bool visited to true.
void Intersection::updateVisit() {
    this->visited = true;
}
//changes the bool visited to false and the father to NULL.
void Intersection::clean() {
    this->visited = false;
    this->father = NULL;
}
//update a visit. changes the bool obstacle to true.
void Intersection::updateObstacle() {
    this->obstacle = true;
}
//return if the intersection is an obstacle.
bool Intersection::isObstacle(){
    return this->obstacle;
}
//return if the intersection was visited.
bool Intersection::isVisited() {
    return this->visited;
}
//return pointer to father (intersection*)
Intersection *Intersection::getFather() {
    return this->father;
}

ostream& operator << (ostream& os, const Intersection* inter){
    inter->printInter(os);
    return os;
}

Intersection::~Intersection() {
}

BOOST_CLASS_EXPORT(Intersection)