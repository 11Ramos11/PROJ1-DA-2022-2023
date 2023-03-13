//
// Created by Ramos on 3/13/2023.
//

#include <fstream>
#include "SourceReader.h"

void SourceReader::read(){

    readStations();
    readNetwork();
}

void SourceReader::readStations() {

    std::ifstream stationsFile("../resources/stations.csv");
    std::string entry;

    getline(stationsFile, entry);

    std::string name, district, municipality, township, line;

    do {
        getline(stationsFile, name, ',');
        if (name == "") break;
        getline(stationsFile, district, ',');
        getline(stationsFile, municipality, ',');
        getline(stationsFile, township, ',');
        getline(stationsFile, line);

    } while (true);
}

void SourceReader::readNetwork() {

    std::ifstream networkFile("../resources/network.csv");
    std::string entry;

    getline(networkFile, entry);

    std::string stationA, stationB, capacity, service;

    do {
        getline(networkFile, stationA, ',');
        if (stationA == "") break;
        getline(networkFile, stationB, ',');
        getline(networkFile, capacity, ',');
        getline(networkFile, service);

        int capacityInt = stoi(capacity);

    } while (true);
}