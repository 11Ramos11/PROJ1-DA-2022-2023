//
// Created by Ramos on 3/13/2023.
//

#include <iostream>
#include "Application.h"


void Application::start(){

    SourceReader().read(stations, railwayNetwork);

    basicServices.edmondsKarp(1, 97);
    std::cout << "Hello";
}