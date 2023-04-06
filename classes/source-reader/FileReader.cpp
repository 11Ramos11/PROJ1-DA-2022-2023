/** @file FileReader.cpp
 *  @brief Contains the FileReader Class implementation.
 *  @author -
 *  @bug No known bugs.
 */

#include <fstream>
#include <iostream>
#include "FileReader.h"

FileReader::FileReader()= default;

FileReader::FileReader(std::string stationsFileName, std::string networkFileName):
    stationsFileName(stationsFileName), networkFileName(networkFileName){}

void FileReader::read(std::unordered_map<std::string, std::shared_ptr<Station>> &stations, Graph &railwayNetwork){

    readStations(stations, railwayNetwork);
    readNetwork(stations, railwayNetwork);
}

void FileReader::readStations(std::unordered_map<std::string, std::shared_ptr<Station>> &stations, Graph &railwayNetwork) {

    std::ifstream stationsFile(stationsFileName);
    std::string entry;

    getline(stationsFile, entry);

    std::string name, district, municipality, township, line;

    int id = 1;

    do {
        getline(stationsFile, name, ',');
        if (name.empty()) break;
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

void FileReader::readNetwork(std::unordered_map<std::string, std::shared_ptr<Station>>& stations, Graph &railwayNetwork) {

    std::ifstream networkFile(networkFileName);
    std::string entry;

    getline(networkFile, entry);

    std::string stationA, stationB, capacity, service;

    do {
        getline(networkFile, stationA, ',');
        if (stationA.empty()) break;
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