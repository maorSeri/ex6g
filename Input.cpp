//
// Created by maor on 25/01/17.
//
#include "Input.h"
#include "BFS.h"
#include <vector>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

/*
 * chick that the amount of "," is machine the kind of string.
 */
bool lengthValidation(int amount,string input,char spleter) {
    int start=0;
    int count=0;
    int index = input.find(spleter,start);
    while(index>=0 && (start+1<input.length())){
        start=index+1;
        count++;
        index=input.find(spleter,start);
    }
    //bagging of validation of input
    if(count==amount)
    {
        return true;
    }
    return false;
}

/*
 * splits the string by ",".
 */
vector<string> splitInput( string input,char spliter) {
    int i=0;
    int start=0;
    vector<string> split;
    while(i<input.length()){
        if(input[i]==spliter){
            split.push_back(input.substr(start,i-start));
            start=i+1;
        }
        i++;
    }
    split.push_back(input.substr(start,i-start));
    return split;
}
/*
 * chick driver
 * if valid ret driver
 * else null.
 */
Driver* driversValidation(){
    string input;
    getline(cin,input);
    vector<string> vInput;
    int id,age,experience,vehicleID;
    char status;
    if(!lengthValidation(4, input,',')){
        return NULL;
    }
    vInput=splitInput(input,',');
    //id chick.
    id=positiveNumber(vInput.at(0));
    if(id<0){
        return NULL;
    }
    //age chick
    age=positiveNumber(vInput.at(1));
    if(age<0){
        return NULL;
    }
    //status chick
    char satuses[4]={'S','M', 'D', 'W'};
    status=letterValid(vInput.at(2),satuses,4);
    if(status=='#'){
        return NULL;
    }
    //experience chick
    experience= positiveNumber(vInput.at(3));
    if(experience<0){
        return NULL;
    }
    //vehicle ID chick.
    vehicleID=positiveNumber(vInput.at(4));
    if(vehicleID<0){
        return NULL;
    }
    Intersection* start=new Point(0,0);
    Driver* d=new Driver(id, age,status,experience,vehicleID,start);
    return d;
}

Cab* cabsValidation(vector<Cab*> cabs) {
    string input;
    //getline(cin, input);
    getline(cin, input);
    vector<string> vInput;
    if (!lengthValidation(3, input,',')) {
        return NULL;
    }
    vInput = splitInput(input,',');
    int id, taxi_type;
    char manufacturer, color;
    id = positiveNumber(vInput.at(0));
    if (id < 0) {
        return NULL;
    }
    int i=0;
    while(i<cabs.size()){
        if(id==(cabs.at(i))->getId()){
            return NULL;
        }
        i++;
    }
    taxi_type = cabTayp(vInput.at(1));
    if (taxi_type != 1 && taxi_type != 2) {
        return NULL;
    }
    char manufacturers[4] = {'H', 'S', 'T', 'F'};
    manufacturer = letterValid(vInput.at(2), manufacturers, 4);
    if (manufacturer == '#') {
        return NULL;
    }
    char myColors[5] = {'R', 'B', 'G', 'P', 'W'};
    color = letterValid(vInput.at(3), myColors, 5);
    if (color == '#') {
        return NULL;
    }
    Cab *c=NULL;
    if (taxi_type == 1) {
        c = new StandartCab(id, manufacturer, color);

    }
    else if (taxi_type == 2){
        c = new LuxuryCab(id, manufacturer, color);
    }
    return c;
}

//////////////////////////////////////////////////////////////////////////
Trip *TripValidation(Map* map) {
    Trip * trip = NULL;
    string input;
    getline(cin,input);
    vector<string> vInput;
    int id,x_start,y_start,x_end,y_end,num_passengers,tripTime;
    double tariff;
    Point startP, endP;
    Intersection *start, *end;
    if (!lengthValidation(7, input,',')) {
        cout << "9" << endl;
        return NULL;
    }
    vInput = splitInput(input,',');
    id = positiveNumber(vInput.at(0));
    if (id < 0) {
        cout << "8" << endl;
        return NULL;
    }
    x_start = positiveNumber(vInput.at(1));
    y_start = positiveNumber(vInput.at(2));
    if (x_start < 0 || y_start < 0){
        cout << "7" << endl;
        return NULL;
    }
    startP = Point(x_start,y_start);
    start = map->getIntersect(&startP);
    if(start == NULL || start->isObstacle()){
        cout << "6" << endl;
        return NULL;
    }

    x_end = positiveNumber(vInput.at(3));
    y_end = positiveNumber(vInput.at(4));
    if (x_end < 0 || y_end < 0){
        cout << "5" << endl;
        return NULL;
    }
    endP = Point(x_end, y_end);
    end = map->getIntersect(&endP);
    if(end == NULL || end->isObstacle()){
        cout << "4" << endl;
        return NULL;
    }

    BFS* bfs = new BFS(map, start, end);
    bfs->algorithm();
    stack<Intersection *> path = bfs->getStackPath();
    if (path.size() <= 0){
        cout << "3" << endl;
        return NULL;
    }
    map->reworld();
    delete bfs;
    num_passengers = positiveNumber(vInput.at(5));
    if (num_passengers <= 0){
        cout << "2" << endl;
        return NULL;
    }
    tariff=positiveDoubleNumber(vInput.at(6));
    if(tariff<0){
        return  NULL;
    }
    tripTime = positiveNumber(vInput.at(7));
    if (tripTime < 0){
        cout << "1" << endl;
        return NULL;
    }


    trip = new Trip(id, start, end, num_passengers, tariff, tripTime);
    return trip;

}
/////////////////////////////////////////////////////////////////////////


Grid2D* gridsValidation(){
    string input;
    getline(cin, input);
    vector<string> vInput;
    vInput=splitInput(input,' ');
    if(vInput.size()!=2){
        return NULL;
    }
    int m,n;
    m=positiveNumber(vInput.at(0));
    if(m<=0){
        return NULL;
    }
    n=positiveNumber(vInput.at(1));
    if(n<=0){
        return NULL;
    }
    //creat empty grid.
    Grid2D* grid= new Grid2D(m,n);
    //obstacles
    int numOfObst;
    getline(cin, input);
    numOfObst=positiveNumber(input);
    if(numOfObst<0){
        delete grid;
        return NULL;
    }
    //set obstacles
    for(int i=0; i < numOfObst; i++){
        getline(cin, input);
        vInput=splitInput(input,',');
        if(vInput.size()!=2){
            delete grid;
            return NULL;
        }
        int x,y;
        x=positiveNumber(vInput.at(0));
        if(x<0||x>=m){
            delete grid;
            return NULL;
        }
        y=positiveNumber(vInput.at(1));
        if(y<0||y>=n){
            delete grid;
            return NULL;
        }
        grid->addObstacle(x,y);
    }
    return grid;
}


/*
 * chick that numS is positive number
 */
int positiveNumber(string numS){
    int num;
    int i=0;
    //id of driver
    while(i<(numS).length()){
        if(!(isdigit(numS[i]))){
            return -1;
        }
        i++;
    }
    num=stoi(numS);
    if(num<0){
        return -1;
    }
    return num;
}

double positiveDoubleNumber(string numS){
    int pointIndex=numS.find('.',0);
    int r,l;
    if(pointIndex<0){
        return positiveNumber(numS);
    }
    else{
        string s1=numS.substr(0,pointIndex);
        string s2=numS.substr(pointIndex+1,numS.size());
        int k=s2.find('.',0);
        if(k>=0){
            return -1;
        }
        int l=positiveNumber(s1);
        if(l<0){
            return -1;
        }
        int r=positiveNumber(s2);
        if(r<0){
            return -1;
        }
        double d=10;
        for(int i=0;i<(s2.size()-1);i++){
            d=d*10;
        }
        double tariff;
        tariff=l*d;
        tariff+=r;
        tariff=tariff/d;
        return tariff;
    }
}


int cabTayp(string numS){
    int kined=positiveNumber(numS);
    if(kined!=1&&kined!=2){
        return -1;
    }
    return kined;
}

/*
 * chics that letter is one of the letters in options.
 */
char letterValid(string letter,char options[],int size){
    if(letter.size()!=1){
        return '#';
    }
    char c=letter[0];
    int i=0;
    while(i<size){
        if(c==options[i]){
            return c;
        }
        i++;
    }
    return '#';
}

