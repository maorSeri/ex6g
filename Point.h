//
// Created by yuval on 20/11/16.
//

#ifndef MAIN_POINT_H
#define MAIN_POINT_H

#include "Intersection.h"
#include <iostream>

#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
//every derived
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>

using namespace std;
using namespace boost::archive;
/*
 * Point class
 * inheritance from Intersection.
 * present a intersection in grid2d.
 */
class Point : public Intersection {
    int px, py;

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        //every derived
        ar & boost::serialization::base_object<Intersection>(*this);
        ar & px;
        ar & py;
    }
public:
    //costructors.
    Point ();
    Point (int x, int y);

    virtual ~Point();

    //return the x value
    int getX();
    //return the y value
    int getY();
    // set the x value.
    void setX(int);
    // set the y value.
    void setY(int);
    //overloading the operator == . compares between two points.
    bool operator==(const Intersection &inter1) const;
    //overloading the printing.
    void printInter (ostream& os) const;
    const Point operator+(const Point& point) const;
    bool operator!=(const Intersection& inter1) const;
};


#endif //MAIN_POINT_H