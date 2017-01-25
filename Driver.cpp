//
// Created by maor on 01/12/16.
//

#include "Driver.h"

//constructor
Driver::Driver() {
    this->satisfactionAv = 0;
    this->customers = 0;
}
Driver::Driver(int id, int age, char status, int experience, Cab* taxi, Intersection* startP) {
    this->id =id;
    this->age=age;
    switch(status){
        case 'S':
            this->status=maritalStatus{S} ;
            break;
        case 'M':
            this->status=maritalStatus{M} ;
            break;
        case 'D':
            this->status=maritalStatus{D} ;
            break;
        case 'W':
            this->status=maritalStatus{W} ;
            break;
        default:
            break;

    }
    this->yearsExper= experience;
    this->taxi=taxi;
    this->location = startP;
    this->satisfactionAv = 0;
    this->customers = 0;
    this->busy = false;
    this->curentTrip = NULL;
    //  this->pathToGo= NULL;
}

Driver::Driver(int id, int age, char status, int experience, int idVehicle, Intersection *startP) {
    this->id =id;
    this->age=age;
    switch(status){
        case 'S':
            this->status=maritalStatus{S} ;
            break;
        case 'M':
            this->status=maritalStatus{M} ;
            break;
        case 'D':
            this->status=maritalStatus{D} ;
            break;
        case 'W':
            this->status=maritalStatus{W} ;
            break;
        default:
            break;

    }
    this->yearsExper= experience;
    this->idVehicle=idVehicle;
    this->taxi=NULL;
    this->location = startP;
    this->satisfactionAv = 0;
    this->customers = 0;
    this->busy = false;
    this->curentTrip = NULL;
}

// getters

int Driver::getId() const {
    return id;
}

int Driver::getAge() const {
    return age;
}

int Driver::getYearsExper() const {
    return yearsExper;
}

double Driver::getSatisfactionAv() const {
    return satisfactionAv;
}

int Driver::getNumCustomers() const {
    return customers;
}

Cab *Driver::getTaxi() const {
    return taxi;
}

maritalStatus Driver::getStatus() const {
    return status;
}

Intersection *Driver::getLocation() {
    return location;
}

Trip *Driver::getCurentTrip() const {
    return curentTrip;
}

int Driver::getIDVehicle() const {
    return this->idVehicle;
}


// setters


void Driver::setSatisfactionAv(double satisfactionAv) {
    Driver::satisfactionAv = satisfactionAv;
}

void Driver::setTaxi(Cab *taxi) {
    Driver::taxi = taxi;
}

void Driver::setStatus(maritalStatus status) {
    Driver::status = status;
}

void Driver::setLocation(Intersection *location) {
    Driver::location = location;
}

// methods

//change the driver's location
//temper method. we want change it acoording the plan!!
void Driver::driveTo(Intersection * inter) {
    this->setLocation(inter);
}

Driver::~Driver() {

}

bool Driver::isBusy() {
    return this->busy;
}

void Driver::updateBusy(Trip* trip, stack<Intersection*> pathStack) {
    this->busy = true;
    this->curentTrip = trip;
    this->pathToGo = pathStack;
    //pop the start point-- this is the current location
    pathToGo.pop();

}

void Driver::available() {
    this->busy = false;

}

void Driver::goOn() {
    if(this->taxi->getSpeed()== 2 && this->pathToGo.size() > 1) {
        this->pathToGo.pop();
    }
    this->setLocation(this->pathToGo.top());
    this->pathToGo.pop();
    this->taxi->updateKmPassed(this->taxi->getSpeed());
    this->curentTrip->updateMeters(this->taxi->getSpeed());
    if(this->pathToGo.empty()){
        this->available();
        //this->pathToGo = NULL;
    }
}

int Driver::getClDescriptor() const {
    return clDescriptor;
}

void Driver::setClDescriptor(int clDescriptor) {
    Driver::clDescriptor = clDescriptor;
}
