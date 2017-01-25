//
// Created by maor on 25/01/17.
//

#ifndef EX5_INPUT_H
#define EX5_INPUT_H

#include "Cab.h"
#include "Driver.h"
#include "Trip.h"
#include "Map.h"
#include <vector>
using namespace std;

class InputValidtion {
public:
    string inptString(int length);
    Cab cabValid();
    vector splitInput(string input);
    bool lengthValidation(string input);
};


#endif //EX5_INPUT_H
