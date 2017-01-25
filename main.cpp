#include <iostream>
#include "TaxiCenter.h"

#include <cstdlib>
#include <pthread.h>
#include <unistd.h>


#include "sockets/Tcp.h"
#include "sockets/Socket.h"

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
    do{
        cin >> oper;
        switch(oper){
            //insert driver.
            case 1:
                cout<<"     case 1:     insertDriver"<<endl;
                manager.insertDriver((Tcp*)socket);
                break;
                //insert a new ride.
            case 2:
                cout<<"     case 2:     insertTrip"<<endl;
                manager.insertTrip();
                break;
                //insert a vehicle.
            case 3:
                cout<<"     case 3:     insertCab"<<endl;
                manager.insertCab();
                break;
                //returns a drivers location.
            case 4:
                cout<<"     case 4:     print Location"<<endl;
                manager.driverLocation();
                break;
                //starts a ride.
            case 6:
                manager.startRide();
                break;
                //exit program.
            case 7:
                cout<<"     case 7:     close"<<endl;
                break;
                //advance the clock time
            case 9:
                cout<<"     case 9:     activate clock"<<endl;
                manager.activateClock((Tcp*)socket);
                break;

            default:
                break;

        }
    }while(oper!=7);


    manager.closeClients((Tcp*)socket);

    delete socket;
    return 0;
    /*::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();*/
}