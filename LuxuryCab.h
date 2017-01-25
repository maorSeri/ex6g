//
// Created by maor on 01/12/16.
//

#ifndef AP_EX2_LUXURYCAB_H
#define AP_EX2_LUXURYCAB_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include <boost/serialization/export.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>

#include "Cab.h"
class LuxuryCab : public Cab{
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        //every derived
        ar & boost::serialization::base_object<Cab>(*this);
    }
public:
    LuxuryCab();
    LuxuryCab(int id, char manufac, char color);
    //destructor
    virtual ~LuxuryCab();

};


#endif //AP_EX2_LUXURYCAB_H