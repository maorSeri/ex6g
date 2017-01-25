//
// Created by maor on 01/12/16.
//

#include "TaxiCenter.h"
//THREAD
struct thread_data{
    int  thread_id;
    TaxiCenter* taxiCenter;
    Tcp* socket;
};


TaxiCenter::TaxiCenter(Map* map) {
    this->map = map;
    this->time = 0;
}


void TaxiCenter::createGrid(int m, int n) {
    Grid2D(m,n);
}

//getters
vector<Driver*>TaxiCenter:: getVecDrivers(){
    return this->drivers;
}
vector<Cab*>TaxiCenter:: getVecCabs(){
    return this->cabs;
}
vector<Trip*>TaxiCenter:: getVecTrips(){
    return this->trips;
}

/*
 * adds a new driver to the taxi station.
 */
void TaxiCenter::insertDriver(Tcp* socket) {
    cout<<"server: task 1"<<endl;
    //get amount of cabs.
    //int clDescriptor;
    int amount;
    int rc;
    cin>>amount;

    //THREADS
    pthread_t threadArr[amount];
   // struct thread_data td[amount];


    //receive driver from cline.
    for(int i=0;i<amount;i++) {
        //THREADS
        thread_data* td = new thread_data();
        td->thread_id = i;
        td->taxiCenter = this;
        td->socket = socket;
        cout << "server : creating thread: " << i << endl;
        rc = pthread_create(&threadArr[i], NULL, OpenThread, (void *)td);

        if (rc){
            cout << "Error:unable to create thread," << rc << endl;
            exit(-1);
        }


/*
        clDescriptor = socket->acceptOneClient();
        socket->sendData("server: waiting for driver.",clDescriptor);
        Driver *driver = this->receiveDriver(socket, clDescriptor);
        driver->setClDescriptor(clDescriptor);
        cout << "server: driver received" << endl;
        socket->sendData("server: sending cab driver.",clDescriptor);
        this->waitForCl(socket, clDescriptor);
        this->sendTaxi(driver, socket, clDescriptor);
        cout << "server: cab sent" << endl;

*/

    }
    for (int i=0;i<amount;i++) {
        pthread_join(threadArr[i], NULL);
    }
  //  pthread_exit(NULL);

}

/*
 * adds a new trip to the taxi station
 */
void TaxiCenter::insertTrip() {
    int id,x_start,y_start,x_end,y_end,num_passengers,tripTime;
    double tariff;
    char buff;//buffer
    Point startP, endP;
    Intersection *start, *end;
    //gets the rides details from the consul
    cin>>id>>buff>>x_start>>buff>>y_start>>buff>>x_end>>buff>>y_end>>buff
       >>num_passengers>>buff>>tariff>>buff>>tripTime;
    startP = Point(x_start,y_start);
    endP = Point(x_end, y_end);
    start = (*this->map).getIntersect(&startP);
    end = (*this->map).getIntersect(&endP);
    Trip* trip = new Trip(id,start,end,num_passengers,tariff,tripTime);
    //adds trip to the taxi station.
    this->trips.push_back(trip);
}

/*
 * adds a new cab to the taxi station.
 */
void TaxiCenter::insertCab() {
    int id, taxi_type;
    char manufacturer,color;
    char buff;
    Cab* cab = NULL;
    //gets the cabs details from the consul
    cin>>id>>buff>>taxi_type>>buff>>manufacturer>>buff>>color;
    if(taxi_type == 1){
        cab = new StandartCab(id, manufacturer, color);
    } else if(taxi_type == 2){
        cab = new LuxuryCab(id, manufacturer, color);
    }
    //adds the cab to the taxi station.
    this->cabs.push_back(cab);
}

/*
 *gets a drivers id from the consul and returns the matching driver location.
 */
void TaxiCenter::driverLocation() {
    int id_driver;
    //gets the id of driver from the consul
    cin>>id_driver;
    //returns the drivers loction
    cout<<this->getDriver(id_driver)->getLocation()<<endl;
}

/*
*gets a drivers id from the consul and returns the matching driver.
*/
Driver *TaxiCenter::getDriver(int id_driver) {
    int i = 0;
    while(drivers[i]->getId() != id_driver){
        i++;
    }
    return drivers[i];
}

/*
 *does a ride.
 */
void TaxiCenter::startRide() {
    Trip* tempForDelete = NULL;
    Driver* driver = NULL;
    unsigned long int i = 0;
    while((i < this->drivers.size())&&(!trips.empty())){
        driver = this->whosAt(this->trips[0]->getStart());
      //  driver->updateBusy();
        driver->driveTo(this->trips.at(0)->getEnd());
        tempForDelete = this->trips[0];
        this->trips.erase(this->trips.begin());
        delete tempForDelete;
        i++;
    }
    for(int j = 0; j < this->drivers.size(); j++){
        this->drivers[j]->available();
    }
}


TaxiCenter::~TaxiCenter() {
    for (int i = 0; i < cabs.size(); i++) {
        delete cabs[i];
    }
    for (int i = 0; i < trips.size(); i++) {
        delete trips[i];
    }
    for (int i = 0; i < drivers.size(); i++) {
        delete drivers[i];
    }
    delete this->map;
}

Driver *TaxiCenter::whosAt(Intersection * inter) {
    int i = 0;
    while (this->drivers[i]->getLocation()!= this->map->getIntersect(inter) || this->drivers[i]->isBusy()){
        i++;
    }
    if(i<drivers.size()){
        return drivers[i];
    }
    else{
        return NULL;
    }

}

void TaxiCenter::activateClock(Tcp* socket) {
    pthread_mutex_t mtx;
    pthread_mutex_init(&mtx, 0);
    Trip* iTrip = NULL;
    Driver* driver = NULL;
    int i = 0;
    //erase from the vector the trips that already "start driving"
    for(int i = 0; i < this->trips.size(); i++){
        if(this->trips[i]->getTripTime() < this->time ){
            this->trips.erase(this->trips.begin() + i);
            i--;
        }
    }
    //find the trip at current time.
    cout<<"activateClock: after erasing trip"<<endl;
    while (i < this->trips.size()) {
        iTrip = this->trips[i];
        //fined the driver in loucaiton of the trip.
        if (iTrip->getTripTime() == this->time) {
            driver = this->whosAt(iTrip->getStart());
            if (!driver->isBusy()) {
                pthread_mutex_lock(&mtx);
                BFS* bfs = new BFS(this->map,iTrip->getStart(),iTrip->getEnd());
                bfs->algorithm();
                driver->updateBusy(iTrip, bfs->getStackPath() );
                // clean the world from any data(visited/father)
                this->map->reworld();
                delete bfs;
                pthread_mutex_unlock(&mtx);
            } else {
                //case when there are 2 drivers in the same point, one drive is
                //busy and the other one available(maybe we need change the
                // method "whosAt"
            }
        }
        i++;
    }
    //active the clock!.
    this->time++;
    cout<<"activateClock: get hear"<<endl;
    //THREAD
    int rc;
    pthread_t threadArr[this->drivers.size()];

    //move one step all the busy drivers
    int numThread = 0;
    int j = 0;
    for( j = 0; j < this->drivers.size(); j++){
        if(this->drivers[j]->isBusy()){
            this->drivers[j]->goOn();
            numThread++;

            //THREAD
            thread_data* td = new thread_data();
            td->thread_id = j;
            td->taxiCenter = this;
            td->socket = socket;



            cout << "server : (want send location "<<  this->drivers[j]->getLocation() << ") creating thread: " << j << endl;
            rc = pthread_create(&threadArr[j], NULL, SLocThread, (void *)td);

            if (rc){
                cout << "Error:unable to create thread," << rc << endl;
                exit(-1);
            }

            /*
            socket->sendData("server: sending location.",this->drivers[j]->getClDescriptor());
            this->waitForCl(socket, this->drivers[j]->getClDescriptor());
            this->sendDriverLocation(drivers[j]->getLocation(),socket,this->drivers[j]->getClDescriptor());
            cout<<"server: location sent"<<endl;
             */
            //if the driver finish the trip-- delete the trip
            if(!this->drivers[j]->isBusy()){
                delete this->drivers[j]->getCurentTrip();
            }

        }

    }
cout<<"aaa"<<endl;
    for (int i=0;i<numThread;i++) {
        cout<<"bbb"<<endl;
        //pthread_mutex_lock(&myMutex);
        pthread_join(threadArr[i], NULL);
        //pthread_mutex_unlock(&myMutex);
        cout<<"ccc"<<endl;
    }
    cout << "** after join  **" << endl;



}

Driver* TaxiCenter::receiveDriver(Tcp *socket, int clientDescriptor) {
    char buffer[1024];
    //get the drive.
    socket->receiveData(buffer, sizeof(buffer), clientDescriptor);
    Driver* driver;
    //deserialization.
    string serial_driver(buffer, sizeof(buffer));
    boost::iostreams::basic_array_source<char> device(serial_driver.c_str(), serial_driver.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s(device);
    boost::archive::binary_iarchive ia(s);
    ia >> driver;
    delete driver->getLocation();
    driver->setLocation(this->map->getIntersect(driver->getLocation()));
    return driver;
}

void TaxiCenter::sendTaxi(Driver *driver,Tcp* socket, int clientDescriptor) {
    //finds the matching taxi.
    int i=0;
    while((*this->cabs[i]).getId()!=driver->getIDVehicle()){
        i++;
    }
    //add driver to list
    driver->setTaxi(cabs[i]);
    this->drivers.push_back(driver);
    //serialization..
    string serial_cab;
    boost::iostreams::back_insert_device<string> inserter(serial_cab);
    boost::iostreams::stream<boost::iostreams::back_insert_device<string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << this->cabs[i];
    s.flush();
    //here !!!!!
    socket->sendData(serial_cab, clientDescriptor);
}

void TaxiCenter::sendDriverLocation(Intersection *location, Tcp* socket, int clientDescriptor) {
    string serial_intersection;
    boost::iostreams::back_insert_device<std::string> inserter(serial_intersection);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << location;
    s.flush();
    //send the next iocation of the taxi.
    // here !!!!
    socket->sendData(serial_intersection, clientDescriptor);
}

void TaxiCenter::closeClients(Tcp *socket) {
    for(int j = 0; j < this->drivers.size(); j++) {
        socket->sendData("server: closing server.", this->drivers[j]->getClDescriptor());
    }
}

void TaxiCenter::waitForCl(Tcp *socket, int clDescriptor) {
    char buffer[1024];
    socket->receiveData(buffer, sizeof(buffer), clDescriptor);
    string message(buffer);
    unsigned long i = message.find_first_of('.');
    message.assign(message.substr(0, i));
    if(message.compare("client: I'm in receive state")!=0){
        cout<<"server: ERROR: in waitForCl"<<endl;
    }
}

//THREADS
void * TaxiCenter::OpenThread(void* data) {
    int clDescriptor;
    struct thread_data* my_data;
    my_data = (struct thread_data*)data;
    Tcp* my_socket = my_data->socket;
    int id = my_data->thread_id;
    TaxiCenter* taxiCenter = my_data->taxiCenter;

    clDescriptor = my_socket->acceptOneClient();
    //sleep (5);
    my_socket->sendData("server: waiting for driver." ,clDescriptor);
    Driver *driver = taxiCenter->receiveDriver(my_socket, clDescriptor);
    driver->setClDescriptor(clDescriptor);
    cout << "server: driver received. (thread "<< id <<")"<< endl;
    my_socket->sendData("server: sending cab driver.",clDescriptor);
    taxiCenter->waitForCl(my_socket, clDescriptor);
    taxiCenter->sendTaxi(driver, my_socket, clDescriptor);
    cout << "server: cab sent. (thread "<< id <<")"<< endl;

}

void * TaxiCenter::SLocThread(void* data) {

    struct thread_data* my_data;
    my_data = (struct thread_data*)data;
    Tcp* my_socket = my_data->socket;
    int id = my_data->thread_id;
    TaxiCenter* taxiCenter = my_data->taxiCenter;

    int clDescriptor = taxiCenter->drivers[id]->getClDescriptor();


    taxiCenter->waitForCl(my_socket, clDescriptor);
    my_socket->sendData("server: sending location.",clDescriptor);
    taxiCenter->waitForCl(my_socket, clDescriptor);
    taxiCenter->sendDriverLocation(taxiCenter->drivers[id]->getLocation(),my_socket, clDescriptor);
    cout<<"server: "<<taxiCenter->drivers[id]->getLocation() <<" sent. (thread "<< id <<")"<< endl;

}