//
// Created by Ramos on 3/13/2023.
//

#ifndef PROJ1_DA_2022_2023_SOURCEREADER_H
#define PROJ1_DA_2022_2023_SOURCEREADER_H

#include <map>
#include <unordered_map>
#include "../station/Station.h"
#include "../../data-structure/Graph.h"

class SourceReader {

    void readStations(std::unordered_map<std::string, std::shared_ptr<Station>> &stations, Graph &railwayNetwork);

    void readNetwork(std::unordered_map<std::string, std::shared_ptr<Station>> stations, Graph &railwayNetwork);

public:

    void read(std::unordered_map<std::string, std::shared_ptr<Station>> &stations, Graph &railwayNetwork);

};


#endif //PROJ1_DA_2022_2023_SOURCEREADER_H
