//
// Created by Ramos on 4/2/2023.
//

#include <cfloat>
#include <numeric>
#include "CostOptimizer.h"
#include "../../../data-structure/Heap.h"

CostOptimizer::CostOptimizer(Graph* graph): graph(graph){}

int CostOptimizer::MaxTrainsWithMinCost(int source, int target){

    Vertex* s = graph->findVertex(source);
    Vertex* t = graph->findVertex(target);

    for (Vertex* v: graph->getVertexSet()) {
        v->setDist(DBL_MAX);
        v->setVisited(false);
    }

    s->setDist(0);

    MutablePriorityQueue<Vertex> queue;

    for (Vertex* vertex: graph->getVertexSet()){
        queue.insert(vertex);
        if (vertex == t)
            std::cout << "OEHFIOESN";
    }

    while (!queue.empty()){
        Vertex* u = queue.extractMin();
        if (u->getDist() == 30)
            std::cout << "IUNFISUNF";
        for (Edge* edge: u->getAdj()){
            Vertex* v = edge->getDest();
            if (v == t)
                std::cout << "OEHFIOESN";
            double w = edge->getService();
            if (v->getDist() > u->getDist() + w) {
                v->setDist(u->getDist() + w);
                v->setPath(edge);
                queue.decreaseKey(v);
            }
         }
    }

    int maxFlow = INT_MAX;

    while (s != t){
        if (t->getPath()->getWeight() < maxFlow)
            maxFlow = t->getPath()->getWeight();
        t = t->getPath()->getOrig();
    }

    return maxFlow;
}