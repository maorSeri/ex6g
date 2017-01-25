//
// Created by maor on 01/12/16.
//

#include "Cab.h"


Cab::Cab() {
}
Cab::Cab(int id, char manufac, char color) {
    this->kmPassed = 0;
    mapMFactor['H'] = HONDA;
    mapMFactor['S'] = SUBARO;
    mapMFactor['T'] = TESLA;
    mapMFactor['F'] = FIAT;
    mapColor['R'] = RED;
    mapColor['B'] = BLUE;
    mapColor['G'] = GREEN;
    mapColor['P'] = PINK;
    mapColor['W'] = WHITE;
    this->id = id;
    this->manFac = mapMFactor [manufac];
    this->colorCab = mapColor[color];
}

int Cab::getId() {
    return Cab::id;
}

double Cab::getKmPassed() {
    return Cab::kmPassed;
}

double Cab::getTariff() {
    return Cab::tariff;
}

double Cab::getSpeed() {
    return Cab::speed;
}

manufacturer Cab::getManFac() {
    return Cab::manFac;
}

colors Cab::getColor() {
    return Cab::colorCab;
}

void Cab::setId(int id) {
    Cab::id=id;
}

void Cab::updateKmPassed(int km) {
    Cab::kmPassed += km;
}

void Cab::setTariff(double tariff) {
    Cab::tariff = tariff;
}

void Cab::setSpeed(double speed) {
    Cab::speed=speed;
}

void Cab::setManFac(manufacturer manFac) {
    Cab::manFac=manFac;
}

void Cab::setColorCab(colors a){

}

Cab::~Cab() {

}