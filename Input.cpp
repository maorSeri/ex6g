//
// Created by maor on 25/01/17.
//

#include "Input.h"

string InputValidtion::inptString() {
    string input;
    getline(cin,input);
    //chick that the length of the string matches the wanted object.
}

vector InputValidtion::splitInput(int length, string input) {

    vector split=NULL;
    char i;
    while()
    return vector();
}

/*
 * chick the amount of the "," in the string.
 */
bool InputValidtion::lengthValidation(int length, string input) {
    int start=0;
    int count=0;
    while(input.find(",",start)>=0){
        start=input.find(",",start)+1;
        count++;
    }
    if(count==length)
    {
       return true;
    }
    return false;
}
