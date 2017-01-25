//
// Created by maor on 01/12/16.
//

#ifndef AP_EX2_PASSENGER_H
#define AP_EX2_PASSENGER_H

#include "Point.h"

class Passenger {
    Passenger();
//destructor
public:
    virtual ~Passenger();

private:
    Intersection* source;
    Intersection* destination;
public:
    Passenger(Intersection* source, Intersection* destination);
    Intersection* getSource() ;
    Intersection* getDestination() ;
    int retRide();




};


#endif //AP_EX2_PASSENGER_H
