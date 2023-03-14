//
// Created by Matilde on 14/03/2023.
//

#ifndef PROJ1_DA_2022_2023_METHODS_H
#define PROJ1_DA_2022_2023_METHODS_H


#include "VertexEdge.h"
#include "Graph.h"

class Methods {

    bool path(Vertex * s, Vertex * t){


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

    double find_Bottleneck(Vertex *s, Vertex * t){
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

    void augmentsPath(Vertex * s, Vertex * t, double bottleneck){
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

    void Graph::edmondsKarp(int source, int target) {
        Vertex * s = findVertex(source);
        Vertex * t = findVertex(target);
        double bottleneck;

        for (auto v : vertexSet) {
            v->setPath(0);
            v->setVisited(false);
        }
        for(auto edge: s->getAdj()){
            edge->setFlow(0);
        }

        while(path(s, t)){
            bottleneck = find_Bottleneck(s, t);
            augmentsPath(s, t, bottleneck);
        }
    }

};


#endif //PROJ1_DA_2022_2023_METHODS_H
