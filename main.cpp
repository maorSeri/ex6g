#include <iostream>
#include "TaxiCenter.h"
#include "Input.h"

#include <cstdlib>
#include <pthread.h>
#include <unistd.h>


#include "sockets/Tcp.h"
#include "sockets/Socket.h"

#include <cstring>


using namespace std;
int main(int argc, char *argv[]){
    Grid2D* grid = NULL;
    while(grid==NULL){
       grid=gridsValidation();
        if(grid==NULL){
            cout<<"-1"<<endl;
        }
    }
    TaxiCenter manager = TaxiCenter(grid);
    Socket* socket = new Tcp(1,atoi(argv[1]));
    socket->initialize();
    int oper;
    do{
        cin >> oper;
        switch(oper){
            //insert driver.
            case 1:
                manager.insertDriver((Tcp*)socket);
                break;
                //insert a new ride.
            case 2:
                manager.insertTrip();
                break;
                //insert a vehicle.
            case 3:
                manager.insertCab();
                break;
                //returns a drivers location.
            case 4:
                manager.driverLocation();
                break;
                //starts a ride.
            case 6:
                manager.startRide();
                break;
                //exit program.
            case 7:
                break;
                //advance the clock time
            case 9:
                manager.activateClock((Tcp*)socket);
                break;

            default:
                    cout<<"-1"<<endl;
                break;
        }
    }while(oper!=7);


    manager.closeClients((Tcp*)socket);

    delete socket;
    return 0;
    /*::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();*/
}
