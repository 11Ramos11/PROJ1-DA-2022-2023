cmake_minimum_required(VERSION 3.24)
project(PROJ1_DA_2022_2023)

set(CMAKE_CXX_STANDARD 14)

add_executable(PROJ1_DA_2022_2023 main.cpp classes/file-reader/FileReader.cpp
        classes/file-reader/FileReader.h classes/application/Application.cpp classes/application/Application.h
        classes/station/Station.cpp classes/station/Station.h data-structure/Graph.h data-structure/Graph.cpp
        data-structure/VertexEdge.cpp data-structure/VertexEdge.h classes/functionalities/4.1/BasicServices.cpp
        classes/functionalities/4.1/BasicServices.h classes/functionalities/4.2/CostOptimizer.cpp
        classes/functionalities/4.2/CostOptimizer.h classes/functionalities/4.3/SubgraphService.cpp classes/functionalities/4.3/SubgraphService.h)

