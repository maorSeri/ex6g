//
// Created by maor on 01/12/16.
//

#ifndef AP_EX2_TAXICENTER_H
#define AP_EX2_TAXICENTER_H
#include <vector>
#include "Trip.h"
#include "LuxuryCab.h"
#include "StandartCab.h"
#include "Grid2D.h"
#include "Driver.h"
#include "Trip.h"
#include "sockets/Udp.h"
#include "BFS.h"
#include "sockets/Tcp.h"
#include <mutex>

using namespace std;
using namespace boost::archive;

class TaxiCenter {
private:
    Map* map;
    vector<Driver*> drivers;
    vector<Cab*> cabs;
    vector<Trip*> trips;
    int time;
public:
    TaxiCenter(Map* map);
    //getters
    vector<Driver*> getVecDrivers();
    vector<Cab*> getVecCabs();
    vector<Trip*> getVecTrips();

    Driver* getDriver(int id_driver);

    void createGrid(int m,int n);
    //reads the info from of the driver and creats a driver.
    void insertDriver(Tcp* socket);
    //reads the info from of the trip and creats a trip.
    void insertTrip();
    void insertCab();
    void driverLocation();
    void startRide();
    Driver* receiveDriver(Tcp *socket, int clientDescriptor);
    Driver* whosAt(Intersection *);
    virtual ~TaxiCenter();
    void sendTaxi(Driver* driver,Tcp* socket, int clientDescriptor);
    void sendDriverLocation(Intersection* location, Tcp* socket, int clientDescriptor);
    void activateClock(Tcp* socket);

    void closeClients(Tcp *socket);

    void waitForCl(Tcp *socket, int clDescriptor);

    static void * OpenThread(void* data);

    static void *SLocThread(void *data);
};


#endif //AP_EX2_TAXICENTER_H
