/** @file BasicServices.cpp
 *  @brief Contains the BasicServices Class implementation.
 *  @author -
 *  @bug No known bugs.
 */

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

    for(auto vertex: graph->getVertexSet()){
        for (auto edge: vertex->getAdj()){
            edge->setFlow(0);
        }
    }

    while(path(s, t)){
        bottleneck = find_Bottleneck(s, t);
        augmentsPath(s, t, bottleneck);
    }
}

double BasicServices::maxFlow(int source, int target) {

    edmondsKarp(source, target);

    double max_flow = 0;

    for (auto edge: graph->findVertex(source)->getAdj())
        max_flow += edge->getFlow();

    return max_flow;
}

bool BasicServices::exitsPath(Vertex * s, Vertex * t){

    for (auto v : graph->getVertexSet()) {
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
            if (!w->isVisited()) {
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

std::vector<std::pair<Vertex*, Vertex*>> BasicServices::stationspair(){
    std::vector<std::pair<Vertex*, Vertex*>> ans;
    double full_advantage=INT_MIN;
    double maxflow;

    for(auto station1: graph->getVertexSet()){
        for(auto station2: graph->getVertexSet()){
            if(station1 != station2 && exitsPath(station1,station2)){
                maxflow = maxFlow(station1->getId(), station2->getId());
            }
            if(maxflow > full_advantage) full_advantage = maxflow;
        }
    }

    for(auto station1: graph->getVertexSet()){
        for(auto station2: graph->getVertexSet()){
            if(station1 != station2 && exitsPath(station1,station2)){
                maxflow = maxFlow(station1->getId(), station2->getId());
            }
            if(maxflow == full_advantage) {
                ans.push_back(std::make_pair(station1, station2));
            }
        }
    }
    return ans;
}

std::vector<std::string> BasicServices::municipalities(int k){

    std::vector<std::string>ans;
    std::map<double,std::string> maxflow_mun; //increasing order of keys(by default)

    std::set<std::string> all_municipality;
    for(auto station: graph->getVertexSet()){
        all_municipality.insert(station->getStation()->getMunicipality());
    }

    double maxflow_per_mun=0;

    for(auto municipality: all_municipality){
        for (auto station1: graph->getVertexSet()) {
            if (station1->getStation()->getMunicipality() == municipality) {
                for(auto station2: graph->getVertexSet()){
                    if(station2->getStation()->getMunicipality() != municipality)
                        if(exitsPath(station1, station2))
                            maxflow_per_mun += maxFlow(station1->getId(), station2->getId());
                }
            }
        }
        maxflow_mun[maxflow_per_mun] = municipality;
    }

    auto it = maxflow_mun.begin();
    std::advance(it, maxflow_mun.size()-1);

    while(k>0){
        ans.push_back(it->second);
        it--;
    }
    return ans;
}

std::vector<std::string> BasicServices::districts(int k){

    std::vector<std::string>ans;
    std::map<double,std::string> maxflow_dist; //increasing order of keys(by default)

    std::set<std::string> all_districts;
    for(auto station: graph->getVertexSet()){
        all_districts.insert(station->getStation()->getDistrict());
    }

    double maxflow_per_dist=0;

    for(auto district: all_districts){
        for (auto station1: graph->getVertexSet()) {
            if (station1->getStation()->getDistrict() == district) {
                for(auto station2: graph->getVertexSet()){
                    if(station2->getStation()->getDistrict() != district)
                        if(exitsPath(station1, station2))
                            maxflow_per_dist += maxFlow(station1->getId(), station2->getId());
                    }
            }
        }
        maxflow_dist[maxflow_per_dist] = district;
    }

    auto it = maxflow_dist.begin();
    std::advance(it, maxflow_dist.size()-1);

    while(k>0){
        ans.push_back(it->second);
        it--;
        k--;
    }
    return ans;
}

double BasicServices::max_trains_target(int target){
    Vertex * t = graph->findVertex(target);
    double maxflow;
    double answer = INT_MIN;

    for(auto station: graph->getVertexSet()){
        if(station->getId() != t->getId() && exitsPath(station, t)){
            maxflow = maxFlow(station->getId(), t->getId());
        }
        if(maxflow > answer) answer = maxflow;
    }

    return answer;
}