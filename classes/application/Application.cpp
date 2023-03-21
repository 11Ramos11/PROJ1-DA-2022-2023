/** @file Application.cpp
 *  @brief Contains the Application Class implementation.
 *  @author -
 *  @bug No known bugs.
 */

#include <iostream>
#include "Application.h"

void Application::start(){

    SourceReader().read(stations, railwayNetwork);

    std::cout << "Max Flow: " << basicServices.maxFlow(1,2) << std::endl;
    std::cout << "Max Flow: " << basicServices.maxFlow(1,2);
}