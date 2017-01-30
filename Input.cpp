//
// Created by maor on 25/01/17.
//
#include "Input.h"
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
    while(input.find(spleter,start)>=0&&(start+1<input.length())){
        start=input.find(spleter,start)+1;
        count++;
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

Cab* cabsValidation() {
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

