/** @file Station.cpp
 *  @brief Contains the Station Class implementation.
 *  @author -
 *  @bug No known bugs.
 */

#include "Station.h"

Station::Station(const int id, const std::string &name, const std::string &district, const std::string &municipality,
                 const std::string &township, const std::string &line) :
                 id(id), name(name), district(district),
                 municipality(municipality), township(township),
                 line(line) {}

const int &Station::getId() const {
    return id;
}

const std::string &Station::getName() const {
    return name;
}

const std::string &Station::getDistrict() const {
    return district;
}

const std::string &Station::getMunicipality() const {
    return municipality;
}
