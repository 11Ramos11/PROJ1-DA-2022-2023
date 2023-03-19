/** @file Application.cpp
 *  @brief Contains the Application Class implementation.
 *  @author -
 *  @bug No known bugs.
 */

#include <iostream>
#include "Application.h"

void Application::start(){

    SourceReader().read(stations, railwayNetwork);

    for(auto p :basicServices.districts(4))
        std::cout << p;
}