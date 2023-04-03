/** @file Application.cpp
 *  @brief Contains the Application Class implementation.
 *  @author -
 *  @bug No known bugs.
 */

#include "Application.h"

void Application::start(){

    SourceReader().read(stations, railwayNetwork);

    state.push(WELCOME_MENU);
    getMenu();
}

void Application::welcomeMenu(){

    std::cout << "---------------------------------------------------------------" << std::endl;
    std::cout << " Welcome to the Analysis Tool for Railway Network Management!" << std::endl;
    std::cout << "---------------------------------------------------------------" << std::endl;
    std::cout << "Click ENTER for the options";
    std::cin.ignore(1000,'\n');

    state.push(INITIAL_MENU);
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
        std::cout << "4. Quit" << std::endl << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(1000,'\n');
        if(choice >=5 || choice <=0){
            std::cout << "Invalid option number!";
        }
    }
    while(choice >=5 || choice <= 0);

    switch(choice){
        case 1:
            state.push(SERVICES_MENU);
            break;
        case 2:
            state.push(COST_MENU);
            break;
        case 3:
            state.push(FAILURE_MENU);
            break;
        case 4:
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
        std::cout << "6. Go Back" << std::endl;
        std::cout << "7. Quit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(1000,'\n');
        if(choice >=8 || choice <=0){
            std::cout << "Invalid option number!";
        }
    }
    while(choice >=8 || choice <= 0);

    switch(choice){
        case 1: {
            std::string source;
            std::string target;

            std::cout << "Name of the source station: ";
            getline(std::cin, source);
            std::cout << "Name of the target station: ";
            getline(std::cin, target);

            int sourceID=0;
            int targetID=0;
            for (auto s: stations) {
                if (s.first == source) {
                    sourceID = s.second->getId();
                }
                if(s.first == target) {
                    targetID = s.second->getId();
                }
            }
            if(sourceID==0 || targetID==0){
                std::cout<< "Invalid stations names!";
                break;
            }
            std::cout << basicServices.maxFlow(sourceID, targetID);
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
            std::cout << "Insert the number of municipalities: ";
            std::cin >> k_mun;
            std::cin.ignore();
            for (auto m: basicServices.getMunicipalitiesOrDistricts(true, k_mun)) {
                std::cout << m << std::endl;
            }
            break;
        }
        case 4: {
            int k_dist;
            std::cout << "Insert the number of districts: ";
            std::cin >> k_dist;
            std::cin.ignore();
            for (auto d: basicServices.getMunicipalitiesOrDistricts(false, k_dist)) {
                std::cout << d << std::endl;
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
            std::cout << basicServices.max_trains_target( targetID);
            break;
        }
        case 6: {
            state.pop();
            break;
        }
        case 7:
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
        std::cout << "1. Maximum number of trains between two specific stations" << std::endl;
        std::cout << "2. Go Back" << std::endl;
        std::cout << "3. Quit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(1000,'\n');
        if(choice >=3 || choice <=0){
            std::cout << "Invalid option number!";
        }
    }
    while(choice >=3 || choice <=0);

    switch(choice) {
        case 1: {
            std::string source;
            std::string target;

            std::cout << "Name of the source station: ";
            getline(std::cin, source);
            std::cout << "Name of the target station: ";
            getline(std::cin, target);

            int sourceID=0;
            int targetID=0;
            for (auto s: stations) {
                if (s.first == source) {
                    sourceID = s.second->getId();
                }
                if (s.first == target) {
                    targetID = s.second->getId();
                }
            }
            if (sourceID == 0 || targetID == 0) {
                std::cout << "Invalid stations names!";
            }
            //std::cout << basicServices.maxFlow(sourceID, targetID);
            break;
        }
        case 2: {
            state.pop();
            break;
        }
        case 3:
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
        std::cout << "2. Top-k most affected stations for each segment" << std::endl;
        std::cout << "3. Go Back" << std::endl;
        std::cout << "4. Quit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(1000,'\n');
        if(choice >=4 || choice <=0){
            std::cout << "Invalid option number!";
        }
    }while(choice >=4 || choice <=0);

    switch(choice){
        case 1:{
            std::string source;
            std::string target;

            std::cout << "Name of the source station: ";
            getline(std::cin, source);
            std::cout << "Name of the target station: ";
            getline(std::cin, target);

            int sourceID=0;
            int targetID=0;
            for (auto s: stations) {
                if (s.first == source) {
                    sourceID = s.second->getId();
                }
                if(s.first == target) {
                    targetID = s.second->getId();
                }
            }
            if(sourceID==0 || targetID==0){
                std::cout<< "Invalid stations names!";
                break;
            }
            //std::cout << basicServices.maxFlow(sourceID, targetID);
            break;
        }
        case 2: {
            int k_mun;
            std::cout << "Insert the number of stations: ";
            std::cin >> k_mun;
            std::cin.ignore();
            /*for (auto m: basicServices.getMunicipalitiesOrDistricts(true, k_mun)) {
                std::cout << m << std::endl;
            }*/
            break;
        }
        case 3: {
            state.pop();
            break;
        }
        case 4:
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
        }
    }
}

