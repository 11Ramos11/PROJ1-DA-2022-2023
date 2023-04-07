/** @file Graph.h
 *  @brief Contains the Graph class declaration.
 *  @author João Ramos e Matilde Simões
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

/** @brief Graph class to represent implementations that uses a graph directly.
 *
 */
class Graph {

public:

    /** @brief Creates a new Graph.
     *
     */
    Graph();

    /** @brief Creates a new Graph.
     *
     * @param graph of Graph * type.
     */
    Graph(Graph *graph);

    /** @brief Auxiliary function to find a vertex with a given ID.
     *
     * @param id of int type.
     * @return Corresponding vertex.
     */
    Vertex * findVertex(int id) const;

    /** @brief Adds a vertex with a given content to a graph.
     *
     * @param id of const int type, by reference.
     * @param station of std::shared_ptr<Station> type.
     * @return True if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(const int &id, std::shared_ptr<Station> station);

    /** @brief Adds an edge to a graph, given the contents of the source and
     * destination vertices and the edge weight.
     *
     * @param sourc of const int type, by reference.
     * @param dest of const int type, by reference.
     * @param w of double type.
     * @param service of ServiceType type.
     * @return True if successful, and false if the source or destination vertex does not exist
     */
    bool addEdge(const int &sourc, const int &dest, double w, ServiceType service);

    /** @brief Adds a bidirectional edge to a graph, given the contents of the source and
     * destination vertices and the edge weight.
     *
     * @param sourc of const int type, by reference.
     * @param dest of const int type, by reference.
     * @param w of double type.
     * @param service of ServiceType type.
     * @return True if successful, and false if the source or destination vertex does not exist
     */
    bool addBidirectionalEdge(const int &sourc, const int &dest, double w, ServiceType service);

    /** @brief Represents the number of vertex of a graph.
     *
     * @return Number of vertex.
     */
    int getNumVertex() const;

    /** @brief Represents the VertexSet.
     *
     * @return All vertex.
     */
    std::vector<Vertex *> getVertexSet() const;

    /** @brief Represents the Depth First Search algorithm.
     *
     * @param source of int type.
     * @return Void.
     */
    void dfs(int source);

    /** @brief Remove the vertex from the graph.
     *
     * @param id of int type.
     * @return Void.
     */
    void removeVertex(int id);

protected:

    //! @brief Holds the vertexSet.
    std::vector<Vertex *> vertexSet;
};

#endif /* DA_TP_CLASSES_GRAPH */