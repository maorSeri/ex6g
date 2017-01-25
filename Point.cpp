//
// Created by yuval on 20/11/16.
//
#include <iostream>
#include "Point.h"
//every derived cpp
#include <boost/serialization/export.hpp>
using namespace std;
//costructors.
Point::Point() {

}
Point::Point(int x, int y) {
    px = x;
    py = y;

}

//return the x value
int Point::getX() {
    return px;
}
//return the y value
int Point::getY() {
    return py;
}
// set the x value.
void Point::setX(int x) {
    px = x;
}
// set the y value.
void Point::setY(int y) {
    py = y;
}


//true if the points have the same values (x,y) . not adress!
bool Point::operator==(const Intersection &inter1)const {
    Point &p1 = (Point&)(inter1);
    return ((px==p1.px)&&(py==p1.py));
}

//overloading the printing.
void Point::printInter(ostream &os) const {
    os <<"(" << this->px << "," << this->py << ")";
}
const Point Point::operator+(const Point& point) const{
    return Point(px+point.px, py+point.py);
}

bool Point::operator!=(const Intersection& inter1) const{
    Point& p1 = (Point&)(inter1);
    return !(*this == p1);
}

Point::~Point() {}
//every derived cpp
BOOST_CLASS_EXPORT(Point)