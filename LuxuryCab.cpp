//
// Created by maor on 01/12/16.
//

#include "LuxuryCab.h"
#include <boost/serialization/export.hpp>
LuxuryCab::LuxuryCab(int id, char manufac, char color) : Cab(id, manufac, color) {
    this->speed = 2;
}

LuxuryCab::~LuxuryCab() {

}

LuxuryCab::LuxuryCab() {

}
BOOST_CLASS_EXPORT(LuxuryCab);