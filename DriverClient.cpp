//
// Created by maor on 29/12/16.
//
#include "Driver.h"
#include "sockets/Udp.h"
#include "sockets/Tcp.h"

using namespace std;

Driver* createDriver();
void sendDriver(Driver* d,Tcp* socket);
Cab* receiveCab(Tcp* socket);
Trip* receiveTrip(Tcp* socket);
Intersection* receiveNewLocation(Tcp* socket);
char getTask(Tcp* socket);

int main(int argc, char *argv[]) {
    //creat an socket.
    //blabla
    Tcp* socket = new Tcp(0, atoi(argv[2]));
    socket->initialize();
    char task=getTask(socket);
    //DriverClient client;
    Driver* driver = NULL;
    Cab *driversCab=NULL;
    Intersection *location=NULL;
    while(task!='Q') {
        switch(task)
        {
            case 'D':
                //DriverClient client;
                driver = createDriver();
                sendDriver(driver, socket);
                cout << "client: driver sent" << endl;
                break;
            case 'C':
                //delit befor subbmition.
                cout << "bbb" << endl;
                socket->sendData("client: I'm in receive state.");
                cout << "fff" << endl;
                driversCab = receiveCab(socket);
                driver->setTaxi(driversCab);
                cout << "client: cab recived" << endl;
                break;
            case 'G':
                socket->sendData("client: I'm in receive state.");
                location = receiveNewLocation(socket);
                cout << "client: location recived" << location << endl;
                //delete driver->getLocation();
                driver->setLocation(location);
                break;
            default:
                break;
        }
        cout << "wait for task" << endl;
        socket->sendData("client: I'm in receive state.");
        task=getTask(socket);
        cout << "task:"<< task<<endl;

    }

    delete driver->getLocation();
    delete driver->getTaxi();
    delete driver->getCurentTrip();
    delete driver;
    delete socket;
    return 0;
}

//******************************************************************

Driver* createDriver() {
    //for drivers members.
    int id,age,experience,vehicleID;
    char status;
    char buff;
    Point* start = new Point(0,0);
    //gets the drivers details from the consul
    cin>>id>>buff>>age>>buff>>status>>buff>>experience>>buff>>vehicleID;
    //create a driver.
    Driver* driver = new Driver(id,age,status,experience,vehicleID,start);
    return driver;
}

void sendDriver(Driver* driver,Tcp* socket) {
    string serial_driver;
    boost::iostreams::back_insert_device<std::string> inserter(serial_driver);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << driver;
    s.flush();
    //send the id of the vehicle.
    socket->sendData(serial_driver);
}


Cab* receiveCab(Tcp* socket) {
    //receive the cab.
    char buffer[1024];
    socket->receiveData(buffer, sizeof(buffer));
    Cab* cab = NULL;
    string serial_cab(buffer, sizeof(buffer));
    boost::iostreams::basic_array_source<char> device(serial_cab.c_str(), serial_cab.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> cab;
    return cab;
}

Trip* receiveTrip(Tcp* socket) {
    Trip* trip;
    //recive trip
    char buffer[1024];
    socket->receiveData(buffer, sizeof(buffer));
    string serial_trip(buffer, sizeof(buffer));
    boost::iostreams::basic_array_source<char> device(serial_trip.c_str(), serial_trip.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> trip;
    return trip;

}
Intersection* receiveNewLocation(Tcp* socket){
    char buffer[1024];
    //get the location.
    socket->receiveData(buffer, sizeof(buffer));
    Intersection* location;
    //deserialization.
    string serial_intersection(buffer, sizeof(buffer));
    boost::iostreams::basic_array_source<char> device(serial_intersection.c_str(), serial_intersection.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s(device);
    boost::archive::binary_iarchive ia(s);
    ia >>location;
    return location;
}

char getTask(Tcp* socket){
    char buffer[1024];

    socket->receiveData(buffer, sizeof(buffer));
    string message(buffer);
    unsigned long i = message.find_first_of('.');
    message.assign(message.substr(0, i));
    if(message.compare("server: waiting for driver")==0){
        return 'D';
    }
    if(message.compare("server: sending cab driver")==0){
        return 'C';
    }
    if(message.compare("server: sending location")==0){
        return 'G';
    }
    if(message.compare("server: closing server")==0){
        return 'Q';
    }
}