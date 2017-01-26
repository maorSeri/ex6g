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
bool lengthValidation(int amount,string input) {
    int start=0;
    int count=0;
    while(input.find(",",start)>=0&&(start+1<input.length())){
        start=input.find(",",start)+1;
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
vector<string> splitInput( string input) {
    int i=0;
    int start=0;
    vector<string> split;
    while(i<input.length()){
        if(input[i]==','){
            split.push_back(input.substr(start,i-start));
            start=i+1;
        }
        i++;
    }
    split.push_back(input.substr(start,i-start));
    return split;
}

/*bool inputValidation(char expected){
    string input;
    getline(cin,input);
    vector<string> vInput;
    switch(expected){
        case 'D':
            int id, age;
            if(lengthValidation(4,input)==false){
                return false;
            }
            vInput=splitInput(input);
            //id chick.
            id=positiveNumber(vInput.at(0));
            if(id<0){
                return false;
            }
            age=positiveNumber(vInput.at(1));
            if(age<0){
                return false;
            }



    }

}*/

int positiveNumber(string numS){
    int num;
    int i=0;
    //id of driver
    while(i<(numS).length()){
        if(!(isdigit(numS[i]))){
            return false;
        }
        i++;
    }
    num=stoi(numS);
    if(num<0){
        return -1;
    }
    return num;
}