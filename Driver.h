//
// Created by maor on 01/12/16.
//

#ifndef AP_EX2_DRIVER_H
#define AP_EX2_DRIVER_H
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
#include <stack>
#include "Cab.h"
#include "Intersection.h"
#include "Trip.h"

enum maritalStatus {S, M, D, W};

class Driver {
    //members
    int id;
    int age;
    int yearsExper;
    double satisfactionAv;
    int customers;
    int idVehicle;
    Cab* taxi;
    maritalStatus status;
    Intersection* location;
    bool busy;
    Trip* curentTrip;
    stack<Intersection*> pathToGo;
    int clDescriptor;
public:
    void setClDescriptor(int clDescriptor);

public:
    int getClDescriptor() const;

private:

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & id;
        ar & age;
        ar & yearsExper;
        ar & satisfactionAv;
        ar & customers;
        ar & idVehicle;
        ar & taxi;
        ar & status;
        ar & location;
        ar & busy;
    }
public:
    //constructor
    Driver();
    Driver(int id,int age,char status, int experience,Cab* taxi,Intersection* locaion);
    Driver(int id,int age,char status, int experience,int idVehicle,Intersection* locaion);
//destructor
    virtual ~Driver();


    // getters

    Intersection* getLocation();

    int getId() const;

    int getAge() const;

    int getYearsExper() const;

    double getSatisfactionAv() const;

    int getNumCustomers() const;

    int getIDVehicle() const;

    Cab *getTaxi() const;

    maritalStatus getStatus() const;

    Trip *getCurentTrip() const;

    // setters

    void setSatisfactionAv(double satisfactionAv);

    void setTaxi(Cab *taxi);

    void setStatus(maritalStatus status);

    void setLocation(Intersection *location);

    // methods

    void updateBusy(Trip*, stack<Intersection*> );

    void available();
    void driveTo(Intersection*);
    bool isBusy();

    //driver move one step for the destination
    void goOn();



};




#endif //AP_EX2_DRIVER_H