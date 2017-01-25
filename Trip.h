//
// Created by maor on 01/12/16.
//

#ifndef AP_EX2_TRIP_H
#define AP_EX2_TRIP_H

#include "Point.h"
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
#include <boost/serialization/access.hpp>


class Trip {
    int id;
    double meterPassed;
    Intersection* start;
    Intersection* end;
    int numOfPassengers;
    double tariff;
    int tripTime;

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & id;
        ar & meterPassed;
        ar & start;
        ar & end;
        ar & numOfPassengers;
        ar & tariff;
        ar & tripTime;
    }

public:
    Trip();
//destructor
    virtual ~Trip();

    Trip(int id, Intersection *start, Intersection *end, int num_passengers,
         double tariff, int time);

    //getters

    int getId() const;

    double getMeterPassed();

    Intersection *getStart() const;

    Intersection *getEnd() const;

    int getNumOfPassengers() const;

    double getTariff() const;

    int getTripTime() const;

    //setters

    void setId(int id);

    void setStart(Intersection *start);

    void setEnd(Intersection *end);

    void setNumOfPassengers(int numOfPassengers);

    void setTariff(double tariff);

    //methods
    void updateMeters(int);



};


#endif //AP_EX2_TRIP_H