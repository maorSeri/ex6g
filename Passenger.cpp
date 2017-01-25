//
// Created by maor on 01/12/16.
//

#include "Passenger.h"
using namespace std;
Passenger::Passenger() {}

Passenger::Passenger(Intersection* source, Intersection* destination) {
    this->source = source;
    this->destination = destination;
}

Intersection* Passenger::getSource() {
    return this->source;
}

Intersection *Passenger::getDestination() {
    return this->destination;
}

int Passenger::retRide() {
    return 0;
}

Passenger::~Passenger() {

}




