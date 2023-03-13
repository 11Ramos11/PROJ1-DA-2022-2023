//
// Created by Ramos on 3/13/2023.
//

#ifndef PROJ1_DA_2022_2023_STATION_H
#define PROJ1_DA_2022_2023_STATION_H

#include "string"


class Station {

    const int id;
    const std::string name;
    const std::string district;
    const std::string municipality;
    const std::string township;
    const std::string line;

public:

    Station(const int id, const std::string &name, const std::string &district,
            const std::string &municipality, const std::string &township, const std::string &line);

    const int &getId() const;

    const std::string &getName() const;

    const std::string &getDistrict() const;

    const std::string &getMunicipality() const;

    const std::string &getTownship() const;

    const std::string &getLine() const;
};


#endif //PROJ1_DA_2022_2023_STATION_H
