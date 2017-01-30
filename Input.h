//
// Created by maor on 25/01/17.
//

#ifndef TESTEX6_INPUT_H
#define TESTEX6_INPUT_H

#include <iostream>
#include <vector>
#include <string>
#include "Driver.h"
#include "Point.h"
#include "Cab.h"
#include "StandartCab.h"
#include "LuxuryCab.h"
#include "Grid2D.h"
#include "Map.h"
using namespace std;
Grid2D* gridsValidation();
bool lengthValidation(int amount,string input,char spleter);
Driver* driversValidation();
//
Trip * TripValidation(Map*);
//
Cab* cabsValidation(vector<Cab*> cabs);
vector<string> splitInput(string input,char spliter);
int positiveNumber(string numS);
int cabTayp(string numS);
char letterValid(string letter,char options[] ,int size);
#endif //TESTEX6_INPUT_H