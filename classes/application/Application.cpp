/** @file Application.cpp
 *  @brief Contains the Application Class implementation.
 *  @author -
 *  @bug No known bugs.
 */

#include <iostream>
#include "Application.h"

void Application::start(){

    SourceReader().read(stations, railwayNetwork);

    for (int i = 25; i < 80; i++)
        std::cout << "Max Flow: " << basicServices.maxFlow(i,i / 2) << std::endl;
}