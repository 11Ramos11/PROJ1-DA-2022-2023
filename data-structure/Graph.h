/** @file Graph.h
 *  @brief Contains the Graph class declaration.
 *  @author -
 *  @bug No known bugs.
 */

#ifndef DA_TP_CLASSES_GRAPH
#define DA_TP_CLASSES_GRAPH

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "MutablePriorityQueue.h"

#include "VertexEdge.h"

class Graph {
public:

    ~Graph();
    /*
    * Auxiliary function to find a vertex with a given ID.
    */
    Vertex * findVertex(int id) const;
    /*
     *  Adds a vertex with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(const int &id, std::shared_ptr<Station> station);

    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * Returns true if successful, and false if the source or destination vertex does not exist.
     */
    bool addEdge(const int &sourc, const int &dest, double w, std::string service);
    bool addBidirectionalEdge(const int &sourc, const int &dest, double w, std::string service);

    int getNumVertex() const;
    std::vector<Vertex *> getVertexSet() const;

    void dfs(int source);

protected:

    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall

    /*
     * Finds the index of the vertex with a given content.
     */
    int findVertexIdx(const int &id) const;

    std::vector<Vertex *> vertexSet;
};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);

#endif /* DA_TP_CLASSES_GRAPH */