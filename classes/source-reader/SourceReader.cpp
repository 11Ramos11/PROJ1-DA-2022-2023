//
// Created by Ramos on 3/13/2023.
//

#include <fstream>
#include <iostream>
#include "SourceReader.h"

void SourceReader::read(std::unordered_map<std::string, Station> &stations, Graph &railwayNetwork){

    readStations(stations, railwayNetwork);
    readNetwork(stations, railwayNetwork);
}

void SourceReader::readStations(std::unordered_map<std::string, Station> &stations, Graph &railwayNetwork) {

    std::ifstream stationsFile("../resources/stations.csv");
    std::string entry;

    getline(stationsFile, entry);

    std::string name, district, municipality, township, line;

    int id = 1;

    do {
        getline(stationsFile, name, ',');
        if (name == "") break;
        getline(stationsFile, district, ',');
        getline(stationsFile, municipality, ',');
        getline(stationsFile, township, ',');
        getline(stationsFile, line);

        Station station = Station(id, name, district, municipality, township, line);
        stations.insert(std::make_pair(name, station));

        railwayNetwork.addVertex(id);

        id++;

    } while (true);
}

void SourceReader::readNetwork(std::unordered_map<std::string, Station> stations, Graph &railwayNetwork) {

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

        double capacityDouble = stod(capacity);

        railwayNetwork.addEdge(
                stations.at(stationA).getId(), stations.at(stationB).getId(),
                capacityDouble, service);

    } while (true);
}