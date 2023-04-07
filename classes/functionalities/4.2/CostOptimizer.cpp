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
        for (Edge* e: v->getAdj()){
            e->setMinResidual(0);
        }
    }

    s->setDist(0);

    MutablePriorityQueue<Vertex> queue;

    for (Vertex* vertex: graph->getVertexSet()){
        queue.insert(vertex);
    }

    while (!queue.empty()){
        Vertex* u = queue.extractMin();
        for (Edge* edge: u->getAdj()){
            Vertex* v = edge->getDest();
            if (!v->isVisited()) {
                double d = edge->getService();
                int residualCapacity = edge->getWeight() - edge->getFlow();
                if (residualCapacity > 0) {
                    if (v->getDist() > u->getDist() + d) {
                        relaxEdge(queue, u, edge, v, d, residualCapacity);
                        v->setPath(edge);
                    }
                    else if (v->getDist() == u->getDist() + d && v->getPath() != nullptr) {
                        relaxEdge(queue, u, edge, v, d, residualCapacity);
                        if (v->getPath()->getMinResidual() < edge->getMinResidual())
                            v->setPath(edge);
                    }
                }
            }
        }

        for (Edge* edge: u->getIncoming()){
            Vertex* v = edge->getDest();
            if (!v->isVisited()) {
                double w = edge->getService();
                if (v->getDist() > u->getDist() + w && edge->getFlow() > 0) {
                    v->setDist(u->getDist() + w);
                    v->setPath(edge);
                    queue.decreaseKey(v);
                }
            }
        }

        u->setVisited(true);
    }
    return t->getDist() != INF;
}

void CostOptimizer::relaxEdge(MutablePriorityQueue<Vertex> &queue, const Vertex *u, Edge *edge, Vertex *v, double d,
                              int residualCapacity) const {
    v->setDist(u->getDist() + d);

    edge->setMinResidual(residualCapacity);

    if (u->getPath() != nullptr) {
        if (residualCapacity < u->getPath()->getMinResidual())
            edge->setMinResidual(residualCapacity);
        else
            edge->setMinResidual(u->getPath()->getMinResidual());
    }
    queue.decreaseKey(v );
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