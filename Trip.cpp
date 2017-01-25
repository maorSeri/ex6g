//
// Created by maor on 01/12/16.
//

#include "Trip.h"
using namespace std;

Trip::Trip() {
    this->meterPassed = 0;

}

Trip::Trip(int id, Intersection *start, Intersection *end, int num_passengers,
           double tariff, int time) {
    this->id = id;
    this->start = start;
    this->end = end;
    this->numOfPassengers = num_passengers;
    this->tariff = tariff;
    this->meterPassed = 0;
    this->tripTime = time;
}


//getters
int Trip::getId() const {
    return id;
}

double Trip::getMeterPassed(){
    return meterPassed;
}

Intersection *Trip::getStart() const {
    return start;
}

Intersection *Trip::getEnd() const {
    return end;
}

int Trip::getNumOfPassengers() const {
    return numOfPassengers;
}

double Trip::getTariff() const {
    return tariff;
}

//setters

void Trip::setId(int id) {
    Trip::id = id;
}

void Trip::setStart(Intersection *start) {
    Trip::start = start;
}

void Trip::setEnd(Intersection *end) {
    Trip::end = end;
}

void Trip::setNumOfPassengers(int numOfPassengers) {
    Trip::numOfPassengers = numOfPassengers;
}

void Trip::setTariff(double tariff) {
    Trip::tariff = tariff;
}

//methods

void Trip::updateMeters(int meter) {
    this->meterPassed += meter;
}

Trip::~Trip() {

}

int Trip::getTripTime() const {
    return this->tripTime;
}
