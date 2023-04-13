/** @file Application.cpp
 *  @brief Contains the Application Class implementation.
 *  @author -
 *  @bug No known bugs.
 */

#include "Application.h"

void Application::start(){

    state.push(WELCOME_MENU);
    getMenu();
}

void Application::welcomeMenu(){

    std::cout << "---------------------------------------------------------------" << std::endl;
    std::cout << " Welcome to the Analysis Tool for Railway Network Management!" << std::endl;
    std::cout << "---------------------------------------------------------------" << std::endl;
    std::cout << "Click ENTER for the options";
    std::cin.ignore(1000,'\n');

    state.push(READ_MENU);
    getMenu();
}

void Application::readMenu(){

    railwayNetwork = Graph();
    stations = {};

    do{
        std::cout << std::endl << std::endl << std::endl;
        std::cout << "------------------------------------------------------" << std::endl;
        std::cout << "    Analysis Tool for Railway Network Management" << std::endl;
        std::cout << "------------------------------------------------------" << std::endl;
        std::cout << "1. Use default files" << std::endl;
        std::cout << "2. Read files" << std::endl;
        std::cout << "0. Quit" << std::endl << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> stringChoice;
        std::cin.ignore(1000,'\n');

        if(!(stringChoice=="1" ||stringChoice=="2" ||stringChoice=="0")){
            std::cout << "Invalid option number!";
        }
    }
    while(!(stringChoice=="1" ||stringChoice=="2" ||stringChoice=="0"));

    choice = std::stoi(stringChoice);

    switch(choice){
        case 1: {
            fileReader.reset();
            fileReader.read(stations, railwayNetwork);
            state.push(INITIAL_MENU);
            std::cout << "Successfully read!";
            break;
        }
        case 2:{
            std::string file1;
            std::string file2;
            std::cout << "Name of the stations file: ";
            std::cin >> file1;
            std::cin.ignore(1000,'\n');
            std::cout << "Name of the network file: ";
            std::cin >> file2;
            std::cin.ignore(1000,'\n');

            fileReader.setFiles(file1, file2);

            if (fileReader.read(stations, railwayNetwork)) {
                fileReader.reset();
                std::cout << std::endl;
                std::cout << "Files specified not found.\n";
                break;
            }

            state.push(INITIAL_MENU);
            std::cout << "Successfully read!";
            break;
        }
        case 0:
            exit(0);
    }
    getMenu();
}
void Application::initialMenu(){
    do{
        std::cout << std::endl << std::endl << std::endl;
        std::cout << "------------------------------------------------------" << std::endl;
        std::cout << "    Analysis Tool for Railway Network Management" << std::endl;
        std::cout << "------------------------------------------------------" << std::endl;
        std::cout << "1. Basic Service Metrics" << std::endl;
        std::cout << "2. Operation Cost Optimization" << std::endl;
        std::cout << "3. Reliability and Sensitivity to Line Failures" << std::endl;
        std::cout << "9. Go back" << std::endl;
        std::cout << "0. Quit" << std::endl << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> stringChoice;
        std::cin.ignore(1000,'\n');

        if(!(stringChoice=="1" ||stringChoice=="2" ||stringChoice=="3" || stringChoice=="9" ||stringChoice=="0")){
            std::cout << "Invalid option number!";
        }
    }
    while(!(stringChoice=="1" ||stringChoice=="2" ||stringChoice=="3" || stringChoice=="9" ||stringChoice=="0"));

    choice = std::stoi(stringChoice);

    switch(choice){
        case 1:
            state.push(SERVICES_MENU);
            break;
        case 2:
            state.push(COST_MENU);
            break;
        case 3: {
            state.push(FAILURE_MENU);
            break;
        }
        case 9: {
            state.push(READ_MENU);
            break;
        }
        case 0:
            exit(0);
    }
    getMenu();
}

void Application::servicesMenu(){
    do{
        std::cout << std::endl << std::endl << std::endl;
        std::cout << "------------------------------------------------------" << std::endl;
        std::cout << "              Basic Services Metrics" << std::endl;
        std::cout << "------------------------------------------------------" << std::endl;
        std::cout << "1. Maximum number of trains between two specific stations" << std::endl;
        std::cout << "2. Pairs of stations that require the most amount of trains" << std::endl;
        std::cout << "3. Top-k municipalities" << std::endl;
        std::cout << "4. Top-k districts" << std::endl;
        std::cout << "5. Maximum number of trains that arrive at a given station" << std::endl;
        std::cout << "9. Go Back" << std::endl;
        std::cout << "0. Quit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> stringChoice;
        std::cin.ignore(1000,'\n');

        if(stringChoice < "0" || stringChoice == "6" || stringChoice =="7" || stringChoice == "8" || stringChoice >"9"){
            std::cout << "Invalid option number!";
        }
    }
    while(stringChoice < "0" || stringChoice == "6" || stringChoice =="7" || stringChoice == "8" || stringChoice >"9");

    choice = std::stoi(stringChoice);

    switch(choice){
        case 1: {
            std::string source;
            std::string target;

            std::cout << "Name of the source station: ";
            getline(std::cin, source);
            std::cout << "Name of the target station: ";
            getline(std::cin, target);

            auto sourceID = stations[source];
            auto targetID = stations[target];
            if(sourceID== nullptr || targetID== nullptr){
                std::cout<< "Invalid station names!";
                break;
            }
            double maxFlow = basicServices.maxFlow(sourceID->getId(), targetID->getId());
            if(maxFlow == -1){
                std::cout << "Inaccessible stations!";
            }
            else{
                std::cout << "The maximum amount of trains: " << maxFlow;
            }

            break;
        }
        case 2: {
            std::cout << "Calculating the pairs..." << std::endl;
            for (auto p: basicServices.optimalPairs()) {
                std::cout << p.first->getStation()->getName() << ", " << p.second->getStation()->getName() << std::endl;
            }
            break;
        }
        case 3: {
            int k_mun;
            int index=1;
            std::cout << "Insert the number of municipalities: ";
            std::cin >> k_mun;
            std::cin.ignore();
            auto top = basicServices.topMunicipalitiesOrDistricts(true, k_mun);
            std::cout << "The top " << k_mun << " municipalities: " << std::endl;
            for (auto m: top) {
                std::cout << index++ << ". " << m << std::endl;
            }
            break;
        }
        case 4: {
            int k_dist;
            int index =1;
            std::cout << "Insert the number of districts: ";
            std::cin >> k_dist;
            std::cin.ignore();
            auto top = basicServices.topMunicipalitiesOrDistricts(false, k_dist);
            std::cout << "The top " << k_dist << " districts: " << std::endl;
            for (auto d: top) {
                std::cout << index++ << ". " << d << std::endl;
            }
            break;
        }
        case 5: {
            std::string target;
            std::cout << "Name of the target station: ";
            getline(std::cin, target);

            int targetID=0;
            for (auto s: stations) {
                if (s.first == target) {
                    targetID = s.second->getId();
                }
            }
            if(targetID==0){
                std::cout<< "Invalid station name!";
                break;
            }
            int answer = basicServices.max_trains_target( targetID);
            std::cout << "The maximum amount of trains: " << answer;
            break;
        }
        case 9: {
            state.pop();
            break;
        }
        case 0:
            exit(0);
    }
    getMenu();
}

void Application::costMenu(){
    do{
        std::cout << std::endl << std::endl << std::endl;
        std::cout << "------------------------------------------------------" << std::endl;
        std::cout << "             Operation Cost Optimization" << std::endl;
        std::cout << "------------------------------------------------------" << std::endl;
        std::cout << "1. Maximum number of trains between two specific stations with minimum cost" << std::endl;
        std::cout << "9. Go Back" << std::endl;
        std::cout << "0. Quit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> stringChoice;
        std::cin.ignore(1000,'\n');

        if(!(stringChoice=="1" || stringChoice=="9" || stringChoice =="0")){
            std::cout << "Invalid option number!";
        }
    }
    while(!(stringChoice=="1" || stringChoice=="9" || stringChoice =="0"));

    choice = std::stoi(stringChoice);

    switch(choice) {
        case 1: {
            std::string source;
            std::string target;

            std::cout << "Name of the source station: ";
            getline(std::cin, source);
            std::cout << "Name of the target station: ";
            getline(std::cin, target);

            auto sourceID = stations[source];
            auto targetID = stations[target];
            if(sourceID== nullptr || targetID== nullptr){
                std::cout<< "Invalid station names!";
                break;
            }

            std::pair<int,int> answer;
            answer = costOptimizer.MaxTrainsWithMinCost(sourceID->getId(), targetID->getId());
            std::cout << std::endl;
            std::cout << "The maximum amount of trains: " << answer.first << std::endl;
            std::cout << "Minimum cost: " << answer.second;
            break;
        }
        case 9: {
            state.pop();
            break;
        }
        case 0:
            exit(0);

    }
    getMenu();
}

void Application::failureMenu(){
    do{
        std::cout << std::endl << std::endl << std::endl;
        std::cout << "------------------------------------------------------" << std::endl;
        std::cout << "     Reliability and Sensitivity to Line Failures" << std::endl;
        std::cout << "------------------------------------------------------" << std::endl;
        std::cout << "1. Maximum number of trains between two specific stations" << std::endl;
        std::cout << "2. Top-k most affected stations for a segment" << std::endl;
        std::cout << "9. Go Back" << std::endl;
        std::cout << "0. Quit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> stringChoice;
        std::cin.ignore(1000,'\n');

        if(!(stringChoice=="1" ||stringChoice=="2" ||stringChoice=="0" ||stringChoice=="9")){
            std::cout << "Invalid option number!";
        }
    }
    while(!(stringChoice=="1" ||stringChoice=="2" ||stringChoice=="0" ||stringChoice=="9"));

    choice = std::stoi(stringChoice);

    switch(choice){
        case 1:{

            subgraphService.resetSubgraph();
            state.push(GRAPHS_MENU);
            break;
        }
        case 2: {

            subgraphService.resetSubgraph();
            std::string source;
            std::string target;

            std::cout << "Name of the source station of the segment: ";
            getline(std::cin, source);
            std::cout << "Name of the target station of the segment: ";
            getline(std::cin, target);

            auto sourceID = stations[source];
            auto targetID = stations[target];
            if(sourceID== nullptr || targetID== nullptr){
                std::cout<< "Invalid station names!";
                break;
            }

            int k;
            int index=1;
            std::cout << "Insert the number of stations: ";
            std::cin >> k;
            std::cin.ignore();
            std::cout << "Calculating the most affected stations... " << std::endl;
            auto topAffected = subgraphService.mostAffectedStations(
                    sourceID->getId(),targetID->getId(), k);
            std::cout << std::endl;
            std::cout << "Removed the segment " << source << "->" << target << std::endl;
            std::cout << std::endl;

            if (topAffected.size() == 0){
                std::cout << "No stations were affected";
            }
            else if (topAffected.size() < k) {
                std::cout << "There were only " << topAffected.size() << " affected stations:" << std::endl;
                for (auto m: topAffected) {
                    std::cout << index++ << ". " << m->getStation()->getName() << std::endl;
                }
            }
            else {
                std::cout << "Top " << k << " most affected stations:" << std::endl;
                for (auto m: topAffected) {
                    std::cout << index++ << ". " << m->getStation()->getName() << std::endl;
                }
            }
            break;
        }
        case 9: {
            state.pop();
            break;
        }
        case 0:
            exit(0);
    }
    getMenu();
}

void Application::graphsMenu(){
    do{
        std::cout << std::endl << std::endl << std::endl;
        std::cout << "------------------------------------------------------" << std::endl;
        std::cout << "     Reliability and Sensitivity to Line Failures" << std::endl;
        std::cout << "------------------------------------------------------" << std::endl;
        std::cout << "1. Delete a station" << std::endl;
        std::cout << "2. Delete an edge" << std::endl;
        std::cout << "3. Delete a service" << std::endl;
        std::cout << "4. Reset alternate graph" << std::endl;
        std::cout << "5. Process" << std::endl;
        std::cout << "9. Go Back" << std::endl;
        std::cout << "0. Quit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> stringChoice;
        std::cin.ignore(1000,'\n');

        if(!(stringChoice=="1" ||stringChoice=="2" ||stringChoice=="0" ||stringChoice=="9"
                || stringChoice =="3" || stringChoice == "4" || stringChoice == "5")){
            std::cout << "Invalid option number!";
        }
    }
    while(!(stringChoice=="1" ||stringChoice=="2" ||stringChoice=="0" ||stringChoice=="9"
            || stringChoice =="3" || stringChoice == "4" || stringChoice == "5"));

    choice = std::stoi(stringChoice);

    switch(choice){
        case 1: {
            std::string station;
            std::cout << "Name of the station: ";
            getline(std::cin, station);

            auto stationID= subgraphService.getID(station);
            if(stationID== -1){
                std::cout<< "Invalid station name!";
                break;
            }

            subgraphService.deleteStation(stationID);
            std::cout << "Successfully deleted!";
            break;
        }
        case 2:{
            std::string source;
            std::string target;

            std::cout << "Name of the source station: ";
            getline(std::cin, source);
            std::cout << "Name of the target station: ";
            getline(std::cin, target);

            auto sourceID= subgraphService.getID(source);
            auto targetID = subgraphService.getID(target);
            if(sourceID== -1 || targetID== -1){
                std::cout<< "Invalid station names!";
                break;
            }

            subgraphService.deleteEdge(sourceID, targetID);
            std::cout << "Successfully deleted!";
            break;
        }
        case 3:{
            std::string service;
            std::cout << "Service type (\"STANDARD\" or \"ALFA PENDULAR\"): ";
            getline(std::cin, service);

            if(service != "STANDARD" && service != "ALFA PENDULAR"){
                std::cout<< "Invalid service type!";
                break;
            }
            if(service == "STANDARD")
                subgraphService.deleteService(STANDARD);
            else
                subgraphService.deleteService(ALFA_PENDULAR);

            std::cout << "Successfully deleted!";
            break;
        }
        case 4:
            subgraphService.resetSubgraph();
            std::cout << "Successfully reset!";
            break;
        case 5: {
            std::string source;
            std::string target;

            std::cout << "Name of the source station: ";
            getline(std::cin, source);
            std::cout << "Name of the target station: ";
            getline(std::cin, target);

            auto sourceID= subgraphService.getID(source);
            auto targetID = subgraphService.getID(target);
            if(sourceID== -1 || targetID== -1){
                std::cout<< "Invalid station names!";
                break;
            }

            int answer = subgraphService.maxFlow(sourceID, targetID);
            std::cout << "The maximum amount of trains: " << answer << std::endl;
            break;
        }
        case 9: {
            state.pop();
            break;
        }
        case 0:
            exit(0);
    }
    getMenu();
}

void Application::getMenu(){
    if(!state.empty()){
        States states = state.top();
        switch(states){
            case WELCOME_MENU:
                welcomeMenu();
                break;
            case READ_MENU:
                readMenu();
                break;
            case INITIAL_MENU:
                initialMenu();
                break;
            case SERVICES_MENU:
                servicesMenu();
                break;
            case COST_MENU:
                costMenu();
                break;
            case FAILURE_MENU:
                failureMenu();
                break;
            case GRAPHS_MENU:
                graphsMenu();
                break;
        }
    }
}
