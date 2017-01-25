//
// Created by maor on 01/12/16.
//

#ifndef AP_EX2_CAB_H
#define AP_EX2_CAB_H
#include <iostream>
#include <map>
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
#include <boost/serialization/map.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>

using namespace std;
enum manufacturer{ HONDA, SUBARO, TESLA, FIAT};
enum colors{ RED, BLUE, GREEN, PINK, WHITE};

class Cab {
protected:
    map<char, manufacturer> mapMFactor;
    map<char, colors > mapColor;
    int id;
    double kmPassed;
    double tariff;
    double speed;
    manufacturer manFac;
    colors colorCab;

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        //ar & mapMFactor;
        //ar & mapColor;
        ar & id;
        ar & kmPassed;
        ar & tariff;
        ar & speed;
        ar & manFac;
        ar & colorCab;
    }


public:
    Cab();
    Cab(int id, char manufac, char color);
//destructor
    virtual ~Cab();


    int getId() ;
    double getKmPassed();
    double getTariff();
    double getSpeed();
    manufacturer getManFac();
    colors getColor();

    void setId(int id);

    void updateKmPassed(int);

    void setTariff(double tariff) ;

    void setSpeed(double speed);

    void setManFac(manufacturer manFac);

    void setColorCab(colors colorCab);


};
BOOST_SERIALIZATION_ASSUME_ABSTRACT(Cab)

#endif //AP_EX2_CAB_H