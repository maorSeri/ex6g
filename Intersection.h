//
// Created by maor on 22/11/16.
//

#ifndef EX1_ADVANCED_PROGRAMING_INTERSECTION_H
#define EX1_ADVANCED_PROGRAMING_INTERSECTION_H

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
#include <boost/serialization/export.hpp>
//every class
#include <boost/serialization/access.hpp>
//in the father i shud use this.

#include <boost/serialization/base_object.hpp>
using namespace std;
using namespace boost::archive;
/*
 * Intersection class.
 * abstract class. present a intersection in map.
 */
class Intersection {

private:
    bool visited;
    bool obstacle;
    Intersection* father;
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & visited;
        ar & obstacle;
        ar & father;
    }

public:
    //constructors
    Intersection();
    Intersection(Intersection*);
    //update a visit. changes the bool visited to true.
    void updateVisit();
    //update the intersection father.
    void setFather(Intersection*);
    //changes the bool visited to false and the father to NULL.
    void clean();
    //return if the intersection was visited.
    bool isVisited();
    //update a visit. changes the bool obstacle to true.
    void updateObstacle();
    //return if the intersection is an obstacle.
    bool isObstacle();
    //return pointer to father (intersection*)
    Intersection* getFather();
    //overloading the operator == . compares between two intersections.
    virtual bool operator==(const Intersection &inter1)const=0;

    virtual bool operator!=(const Intersection &inter1)const=0;
    //destructor
    virtual ~Intersection() ;
    //overloading the printing.
    virtual void printInter (ostream& os) const = 0 ;
    friend ostream& operator << (ostream& os, const Intersection* inter);


};
//every father
BOOST_SERIALIZATION_ASSUME_ABSTRACT(Intersection)


#endif //EX1_ADVANCED_PROGRAMING_INTERSECTION_H