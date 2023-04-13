/** @file SubgraphService.cpp
 *  @brief Contains the SubgraphService Class implementation.
 *  @author -
 *  @bug No known bugs.
 */

#include "SubgraphService.h"
#include "../4.1/BasicServices.h"

SubgraphService::SubgraphService(Graph *graph): originalGraph(graph){}

void SubgraphService::resetSubgraph() {
    subGraph = Graph(originalGraph);
}

void SubgraphService::deleteStation(int id) {

    for (Edge* e: subGraph.findVertex(id)->getAdj())
        subGraph.findVertex(e->getDest()->getId())->removeEdge(id);

    subGraph.removeVertex(id);
}

void SubgraphService::deleteEdge(int orig, int dest) {

    Vertex* o = subGraph.findVertex(orig);
    o->removeEdge(dest);

    Vertex* d = subGraph.findVertex(dest);
    d->removeEdge(orig);
}

void SubgraphService::deleteService(ServiceType serviceType) {

    for (Vertex* v: subGraph.getVertexSet()){
        for (Edge* e: v->getAdj()){
            if (e->getService() == serviceType){
                v->removeEdge(e->getDest()->getId());
            }
        }
    }
}

int SubgraphService::maxFlow(int source, int target) {

    return BasicServices(&subGraph).maxFlow(source, target);
}

std::vector<Vertex*> SubgraphService::mostAffectedStations(int orig, int dest, int k){

    resetSubgraph();

    BasicServices basicServices(&subGraph);

    std::map<Vertex*, double> og_averages, new_averages;

    for(Vertex* s: subGraph.getVertexSet()){

        double maxFlowSum = 0;
        int count = 0;
        for(Vertex* t: subGraph.getVertexSet()){
            if (s == t)
                continue;

            int maxFlow = basicServices.maxFlow(s->getId(), t->getId());
            if (maxFlow == -1)
                continue;
            maxFlowSum += maxFlow;
            count++;
        }
        og_averages.insert(std::make_pair(s, maxFlowSum/count));
    }

    deleteEdge(orig, dest);

    for(Vertex* s: subGraph.getVertexSet()){

        double maxFlowSum = 0;
        int count = 0;
        for(Vertex* t: subGraph.getVertexSet()){
            if (s == t)
                continue;
            int maxFlow = basicServices.maxFlow(s->getId(), t->getId());
            if (maxFlow == -1)
                continue;
            maxFlowSum += maxFlow;
            count++;
        }
        new_averages.insert(std::make_pair(s, maxFlowSum/count));
    }

    int maxDiff = INT_MIN;
    std::vector<Vertex*> affected = subGraph.getVertexSet();

    std::sort(affected.begin(), affected.end(),
              [&og_averages, &new_averages](Vertex* v1, Vertex* v2){
        return (og_averages[v1]-new_averages[v1]) > (og_averages[v2]-new_averages[v2]);
    });

    std::vector<Vertex*> topAffected;

    for(int i = 0; i < k; i++) {

        Vertex* v = affected[i];
        if (og_averages[v]-new_averages[v] == 0)
            continue;
        topAffected.push_back(v);
    }
    return topAffected;
}

int SubgraphService::getID(std::string stationName) {

    for(Vertex* v: subGraph.getVertexSet())
        if (v->getStation()->getName() == stationName)
            return v->getId();
    return -1;
}
