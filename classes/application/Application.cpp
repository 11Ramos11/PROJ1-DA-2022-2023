/** @file Application.cpp
 *  @brief Contains the Application Class implementation.
 *  @author -
 *  @bug No known bugs.
 */

#include <iostream>
#include "Application.h"
#include "../functionalities/4.2/CostOptimizer.h"

void Application::start(){

    SourceReader().read(stations, railwayNetwork);





    for (int i = 25; i < 80; i++) {
        std::cout << "Max Flow: " << basicServices.maxFlow(i, i / 2) << std::endl;
        std::cout << "Max Flow Min Cost" << costOptimizer.MaxTrainsWithMinCost(i, i / 2) << std::endl;
        std::cout << std::endl;
    }
    /*

    std::cout << "Municipalities:\n";
    for (std::string mun: basicServices.municipalities(5)){
        std::cout << mun << std::endl;
    }*/

    /*for (auto pair: basicServices.optimalPairs()){
        std::cout << pair.first->getStation()->getName() << "," <<
                        pair.second->getStation()->getName() << std::endl;
    }*/
}