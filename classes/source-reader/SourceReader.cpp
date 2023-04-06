/** @file SourceReader.cpp
 *  @brief Contains the SourceReader Class implementation.
 *  @author -
 *  @bug No known bugs.
 */

#include <fstream>
#include <iostream>
#include "SourceReader.h"

SourceReader::SourceReader()= default;

SourceReader::SourceReader(std::string stationsFileName, std::string networkFileName):
    stationsFileName(stationsFileName), networkFileName(networkFileName){}

void SourceReader::read(std::unordered_map<std::string, std::shared_ptr<Station>> &stations, Graph &railwayNetwork){

    readStations(stations, railwayNetwork);
    readNetwork(stations, railwayNetwork);
}

void SourceReader::readStations(std::unordered_map<std::string, std::shared_ptr<Station>> &stations, Graph &railwayNetwork) {

    std::ifstream stationsFile(stationsFileName);
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

        std::shared_ptr<Station> stationPTR = std::make_shared<Station>(id, name, district, municipality, township, line);
        stations.insert(std::make_pair(name, stationPTR));

        railwayNetwork.addVertex(id, stationPTR);

        id++;

    } while (true);
}

void SourceReader::readNetwork(std::unordered_map<std::string, std::shared_ptr<Station>>& stations, Graph &railwayNetwork) {

    networkFileName = "../resources/network.csv";
    std::ifstream networkFile(networkFileName);
    std::string entry;

    getline(networkFile, entry);

    std::string stationA, stationB, capacity, service;

    do {
        getline(networkFile, stationA, ',');
        if (stationA == "") break;
        getline(networkFile, stationB, ',');
        getline(networkFile, capacity, ',');
        getline(networkFile, service);

        ServiceType serviceType;

       if (service == "STANDARD")
            serviceType = STANDARD;
       else if (service == "ALFA PENDULAR")
            serviceType = ALFA_PENDULAR;
       else
           continue;

       double capacityDouble = stod(capacity);

       railwayNetwork.addBidirectionalEdge(
                stations.at(stationA)->getId(), stations.at(stationB)->getId(),
                capacityDouble, serviceType);

    } while (true);
}