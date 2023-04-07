/** @file CostOptimizer.cpp
 *  @brief Contains the CostOptimizer Class implementation.
 *  @author -
 *  @bug No known bugs.
 */

#include <cfloat>
#include "CostOptimizer.h"
#include "../4.1/BasicServices.h"

#define INF DBL_MAX

CostOptimizer::CostOptimizer(Graph* graph): graph(graph){}

bool CostOptimizer::dijkstra(Vertex* s, Vertex* t){

    for (Vertex* v: graph->getVertexSet()) {
        v->setDist(INF);
        v->setPath(nullptr);
        v->setVisited(false);
    }

    s->setDist(0);

    MutablePriorityQueue<Vertex> queue;

    for (Vertex* vertex: graph->getVertexSet()){
        queue.insert(vertex);
    }

    while (!queue.empty()){
        Vertex* u = queue.extractMin();

        u->setVisited(true);
        for (Edge* edge: u->getAdj()){
            Vertex* v = edge->getDest();
            if (!v->isVisited()) {
                double w = edge->getService();
                if (v->getDist() > u->getDist() + w && edge->getWeight() - edge->getFlow() > 0) {
                    v->setDist(u->getDist() + w);
                    v->setPath(edge);
                    queue.decreaseKey(v);
                }
            }
        }
        for (Edge* edge: u->getIncoming()){
            Vertex* v = edge->getOrig();
            if (!v->isVisited()) {
                double w = edge->getService();
                if (v->getDist() > u->getDist() + w && edge->getFlow() > 0) {
                    v->setDist(u->getDist() + w);
                    v->setPath(edge);
                    queue.decreaseKey(v);
                }
            }
        }
    }
    return t->getDist() != INF;
}

std::pair<int,int> CostOptimizer::MaxTrainsWithMinCost(int source, int target){

    BasicServices basicServices(graph);

    Vertex * s = graph->findVertex(source);
    Vertex * t = graph->findVertex(target);
    double bottleneck;

    for(auto vertex: graph->getVertexSet()){
        for (auto edge: vertex->getAdj()){
            edge->setFlow(0);
        }
    }

    while(dijkstra(s, t)){
        bottleneck = basicServices.findBottleneck(s, t);
        basicServices.augmentPath(s, t, bottleneck);
    }

    int maxFlow = 0;
    int minCost = 0;

    for (auto edge:s->getAdj())
        maxFlow += edge->getFlow();

    for(auto v : graph->getVertexSet()){
        for(auto e : v->getAdj()){
            if(e->getFlow() != 0){
                minCost += e->getService() * e->getFlow();
            }
        }
    }

    return std::make_pair(maxFlow, minCost);
}