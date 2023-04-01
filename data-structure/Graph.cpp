/** @file Graph.cpp
 *  @brief Contains the Graph Class implementation.
 *  @author -
 *  @bug No known bugs.
 */

#include "Graph.h"

Graph::Graph(){}

Graph::Graph(Graph *graph){

    for (Vertex* vertex: graph->getVertexSet())
        this->addVertex(vertex->getId(), vertex->getStation());

    for (Vertex* vertex: graph->getVertexSet()){
        for (Edge* edge: vertex->getAdj()){
            Vertex* origin = findVertex(edge->getOrig()->getId());
            Vertex* dest = findVertex(edge->getDest()->getId());
            origin->addEdge(dest, edge->getWeight(), edge->getService());
        }
    }
}

int Graph::getNumVertex() const {
    return vertexSet.size();
}

std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

void Graph::setVertexSet(std::vector<Vertex *> vertexSet) {
    this->vertexSet = vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
Vertex * Graph::findVertex(int id) const {

    id--;

    if (id < 0 || id >= vertexSet.size())
        return nullptr;

    return vertexSet[id];
}

void Graph::dfs(int source){

    Vertex* vertex = findVertex(source);
    vertex->setVisited(true);

    for (Edge* edge: vertex->getAdj()){
        if (!edge->getDest()->isVisited())
            dfs(edge->getDest()->getId());
    }
}

/*
 * Finds the index of the vertex with a given content.
 */
int Graph::findVertexIdx(const int &id) const {
    for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->getId() == id)
            return i;
    return -1;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
bool Graph::addVertex(const int &id, std::shared_ptr<Station> station) {
    if (findVertex(id) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(id, station));
    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
bool Graph::addEdge(const int &sourc, const int &dest, double w, std::string service) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w, service);
    return true;
}

bool Graph::addBidirectionalEdge(const int &sourc, const int &dest, double w, std::string service) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w, service);
    auto e2 = v2->addEdge(v1, w, service);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

void deleteMatrix(int **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

void deleteMatrix(double **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

Graph::~Graph() {
    deleteMatrix(distMatrix, vertexSet.size());
    deleteMatrix(pathMatrix, vertexSet.size());
}