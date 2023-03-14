//
// Created by Matilde on 14/03/2023.
//

#include "BasicServices.h"

BasicServices::BasicServices(Graph *graph): graph(graph){}


bool BasicServices::path(Vertex * s, Vertex * t){

    for (auto v : graph->getVertexSet()) {
        v->setPath(0);
        v->setVisited(false);
    }

    std::queue<Vertex*> q;
    q.push(s);
    s->setVisited(true);

    while (!q.empty()) {
        auto v = q.front();
        q.pop();

        for (auto e : v->getAdj()) {
            auto w = e->getDest();
            if (!w->isVisited() && e->getWeight() > e->getFlow()) {
                w->setPath(e);
                w->setVisited(true);
                q.push(w);

                if (w->getId() == t->getId()) {
                    return true;
                }
            }
        }
        for (auto e : v->getIncoming()) {
            auto w = e->getOrig();
            if (!w->isVisited() && e->getFlow() > 0) {
                w->setPath(e);
                w->setVisited(true);
                q.push(w);

                if (w->getId() == t->getId()) {
                    return true;
                }
            }
        }
    }
    return false;
}

double BasicServices::find_Bottleneck(Vertex *s, Vertex * t){
    double bottleneck = INT_MAX;
    while(t != s){
        auto edge = t->getPath();
        double residual_capacity;
        if(edge->getDest() == t){
            residual_capacity = edge->getWeight() - edge->getFlow();
            t = edge->getOrig();
        }
        else{
            residual_capacity = edge->getFlow();
            t = edge->getDest();
        }
        bottleneck = std::min(bottleneck, residual_capacity);
    }
    return bottleneck;
}

void BasicServices::augmentsPath(Vertex * s, Vertex * t, double bottleneck){
    double new_flow;

    while(t != s){
        auto edge = t->getPath();
        if(edge->getDest() == t){
            new_flow = edge->getFlow() + bottleneck;
            edge->setFlow(new_flow);
            t = edge->getOrig();
        }
        else{
            new_flow = edge->getFlow() - bottleneck;
            edge->setFlow(new_flow);
            t = edge->getDest();
        }
    }
}

void BasicServices::edmondsKarp(int source, int target) {

    Vertex * s = graph->findVertex(source);
    Vertex * t = graph->findVertex(target);
    double bottleneck;

    for(auto edge: s->getAdj()){
        edge->setFlow(0);
    }

    while(path(s, t)){
        bottleneck = find_Bottleneck(s, t);
        augmentsPath(s, t, bottleneck);
    }
}

double BasicServices::maxFlow(int source, int target) {

    return 0;
}






