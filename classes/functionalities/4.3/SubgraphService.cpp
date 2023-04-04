//
// Created by joaof on 04/04/2023.
//

#include "SubgraphService.h"


SubgraphService::SubgraphService(Graph *graph): originalGraph(graph){
    resetSubgraph();
}

void SubgraphService::resetSubgraph() {
    *subGraph = *originalGraph;
}

void SubgraphService::deleteStation(int id) {

    subGraph.
}

void SubgraphService::deleteEdge(int orig, int dest) {

}

void SubgraphService::deleteService(ServiceType serviceType) {

    for (Vertex* v: subGraph->getVertexSet()){
        for (Edge* e: v->getAdj()){
            if (e->getService() == serviceType){
                v->removeEdge(e->getDest()->getId());
            }
        }
    }
}

