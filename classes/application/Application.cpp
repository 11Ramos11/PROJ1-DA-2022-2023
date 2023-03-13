//
// Created by Ramos on 3/13/2023.
//

#include "Application.h"
#include "../source-reader/SourceReader.h"


void Application::start(){

    SourceReader().read();
}