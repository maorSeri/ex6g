//
// Created by maor on 01/12/16.
//

#include "StandartCab.h"
#include <boost/serialization/export.hpp>
StandartCab::StandartCab(int id, char manufac, char color) : Cab(id, manufac,
                                                                 color) {
    this->speed = 1;
}

StandartCab::StandartCab() {
}

StandartCab::~StandartCab() {

}
BOOST_CLASS_EXPORT(StandartCab);