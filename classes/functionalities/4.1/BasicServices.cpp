/** @file BasicServices.cpp
 *  @brief Contains the BasicServices Class implementation.
 *  @author -
 *  @bug No known bugs.
 */

#include <unordered_set>
#include "BasicServices.h"

BasicServices::BasicServices(Graph *graph): graph(graph){}

struct Category {
    std::string name;
    double maxFlow;
};

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

double BasicServices::findBottleneck(Vertex *s, Vertex * t){
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

void BasicServices::augmentPath(Vertex * s, Vertex * t, double bottleneck){
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
        bottleneck = findBottleneck(s, t);
        augmentPath(s, t, bottleneck);
    }
}

double BasicServices::maxFlow(int source, int target) {

    edmondsKarp(source, target);

    double max_flow = 0;

    for (auto edge: graph->findVertex(source)->getAdj())
        max_flow += edge->getFlow();

    return max_flow;
}

bool BasicServices::existsPath(Vertex * s, Vertex * t){

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

std::vector<std::pair<Vertex*, Vertex*>> BasicServices::optimalPairs(){

    std::vector<std::pair<Vertex*, Vertex*>> optimalPairs;
    double full_advantage=INT_MIN;
    double maxflow;
    std::set<std::pair<int, int>> visitedPairs;

    for(auto station1: graph->getVertexSet()){
        for(auto station2: graph->getVertexSet()){
            if(station1 != station2 && existsPath(station1, station2)){
                int station1ID = station1->getId();
                int station2ID = station2->getId();
                if (station1ID < station2ID) {
                    if (visitedPairs.count({station1ID, station2ID}) > 0)
                        continue;
                    visitedPairs.insert({station1ID, station2ID});
                }
                else if (station2ID < station1ID) {
                    if (visitedPairs.count({station2ID, station1ID}) > 0)
                        continue;
                    visitedPairs.insert({station2ID, station1ID});
                }
                else continue;

                maxflow = maxFlow(station1ID, station2ID);
                if (maxflow == full_advantage)
                    optimalPairs.push_back(std::make_pair(station1, station2));
                if(maxflow > full_advantage) {
                    full_advantage = maxflow;
                    optimalPairs = {std::make_pair(station1, station2)};
                }
            }
        }
    }
    return optimalPairs;
}

std::vector<std::string> BasicServices::topMunicipalitiesOrDistricts(bool byMunicipality, int k) {

    std::unordered_set<std::string> categoriesNames;
    for (Vertex* vertex : graph->getVertexSet()) {
        if (byMunicipality)
            categoriesNames.insert(vertex->getStation()->getMunicipality());
        else
            categoriesNames.insert(vertex->getStation()->getDistrict());
    }

    std::vector<Category> categories;
    for (std::string name : categoriesNames)
        categories.push_back({name, 0});

    if (k > categories.size())
        k = categories.size();

    for (auto& c : categories) {
        Graph tempGraph = Graph(graph);

        int targetID = tempGraph.getNumVertex() + 1;
        tempGraph.addVertex(targetID, nullptr);

        int sourceID = tempGraph.getNumVertex() + 1;
        tempGraph.addVertex(sourceID, nullptr);

        for (Vertex* vertex : tempGraph.getVertexSet()) {
            if (vertex->getId() == targetID || vertex->getId() == sourceID)
                continue;

            if (byMunicipality && vertex->getStation()->getMunicipality() == c.name ||
                !byMunicipality && vertex->getStation()->getDistrict() == c.name) {
                tempGraph.addEdge(vertex->getId(), targetID, INT_MAX, none);
            }
            else {
                tempGraph.addEdge(sourceID, vertex->getId(), INT_MAX, none);
            }
        }

        c.maxFlow = BasicServices(&tempGraph).maxFlow(sourceID, targetID);
    }

    std::sort(categories.begin(), categories.end(),
              [](Category c1, Category c2) { return c1.maxFlow > c2.maxFlow; });

    std::vector<std::string> result;
    for (int i = 0; i < k; i++) {
        result.push_back(categories[i].name);
    }
    return result;
}

double BasicServices::max_trains_target(int target){

    Graph tempG = Graph(graph);

    int sourceID = tempG.getNumVertex() + 1;
    tempG.addVertex(sourceID, nullptr);

    for (Vertex* v : tempG.getVertexSet()) {
        if (v->getId() == target || v->getId() == sourceID)
            continue;

        tempG.addEdge(sourceID, v->getId(), INT_MAX, none);
    }

    return BasicServices(&tempG).maxFlow(sourceID, target);
}