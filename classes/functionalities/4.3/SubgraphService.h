//
// Created by joaof on 04/04/2023.
//

#ifndef PROJ1_DA_2022_2023_SUBGRAPHSERVICE_H
#define PROJ1_DA_2022_2023_SUBGRAPHSERVICE_H


#include "../../../data-structure/Graph.h"

class SubgraphService {

    const Graph* originalGraph;
    Graph* subGraph;

public:

    SubgraphService(Graph* graph);

    void resetSubgraph();

    void deleteStation(int id);

    void deleteEdge(int orig, int dest);

    void deleteService(ServiceType serviceType);

    int maxFlow(int source, int target);

    std::vector<Vertex *> mostAffectedStations(int source, int target, int k);
};


#endif //PROJ1_DA_2022_2023_SUBGRAPHSERVICE_H
