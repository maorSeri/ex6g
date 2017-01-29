#include <iostream>
#include "TaxiCenter.h"

#include <cstdlib>
#include <pthread.h>
#include <unistd.h>


#include "sockets/Tcp.h"
#include "sockets/Socket.h"
#include "ThreadPool.h"

#include <cstring>


using namespace std;
int main(int argc, char *argv[]){
    //grid m*n
    int m,n;
    //number of obstacles
    int numOfObst;
    //for un useful char
    char buffer;

    cin >>m >>n;
    Grid2D* grid = new Grid2D(m,n);
    cin >>numOfObst;
    TaxiCenter manager = TaxiCenter(grid);
    //blabla
    Socket* socket = new Tcp(1,atoi(argv[1]));
    socket->initialize();
    //   manager.createGrid(m,n); //no need, we did it last line.
    //add the obstacles.
    for(int i=0; i < numOfObst; i++){
        cin>> m >> buffer >> n;
        grid->addObstacle(m,n);
    }
    int oper;

    ThreadPool* tPool = new ThreadPool(5);

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

                manager.activateClock((Tcp*)socket, tPool);
                break;

            default:
                break;

        }
    }while(oper!=7);


    tPool->terminate();
    manager.closeClients((Tcp*)socket);

    delete socket;
    return 0;
    /*::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();*/
}
