//
// Created by joaof on 04/04/2023.
//

#include "SubgraphService.h"
#include "../4.1/BasicServices.h"


SubgraphService::SubgraphService(Graph *graph): originalGraph(graph){
    resetSubgraph();
}

void SubgraphService::resetSubgraph() {
    *subGraph = Graph(*originalGraph);
}

void SubgraphService::deleteStation(int id) {

    for (Edge* e: subGraph->findVertex(id)->getAdj())
        subGraph->findVertex(e->getDest()->getId())->removeEdge(id);

    subGraph->removeVertex(id);
}

void SubgraphService::deleteEdge(int orig, int dest) {

    Vertex* o = subGraph->findVertex(orig);
    o->removeEdge(dest);

    Vertex* d = subGraph->findVertex(dest);
    d->removeEdge(orig);
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

int SubgraphService::maxFlow(int source, int target) {

    return BasicServices(subGraph).maxFlow(source, target);
}
