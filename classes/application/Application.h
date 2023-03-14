//
// Created by Ramos on 3/13/2023.
//

#ifndef PROJ1_DA_2022_2023_APPLICATION_H
#define PROJ1_DA_2022_2023_APPLICATION_H

#include <unordered_map>
#include <string>
#include "../source-reader/SourceReader.h"
#include "../functionalities/4.1/BasicServices.h"

class Application {

    std::unordered_map<std::string, std::shared_ptr<Station>> stations;

    Graph railwayNetwork;

    BasicServices basicServices = BasicServices(&railwayNetwork);

public:

    void start();
};


#endif //PROJ1_DA_2022_2023_APPLICATION_H
