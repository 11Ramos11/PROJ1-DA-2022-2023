/** @file VertexEdge.h
 *  @brief Contains the VertexEdge class declaration.
 *  @author João Ramos e Matilde Simões
 *  @bug No known bugs.
 */

#ifndef DA_TP_CLASSES_VERTEX_EDGE
#define DA_TP_CLASSES_VERTEX_EDGE

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <memory>
#include "MutablePriorityQueue.h"
#include "../classes/station/Station.h"

//! Holds the ServiceType options.
enum ServiceType {STANDARD = 2, ALFA_PENDULAR = 4, none = 0};

/** @brief Edge class to represent the edge from the graph.
 *
 */
class Edge;

/************************* Vertex  **************************/

/** @brief Vertex class to represent the vertex from the graph.
 *
 */
class Vertex {

public:

    /** @brief Creates a new Vertex.
     *
     * @param id of int type.
     * @param station of std::shared_ptr<Station> type.
     */
    Vertex(int id, std::shared_ptr<Station> station);

    /** @brief Operator overloading.
     *
     * @param vertex of Vertex type, by reference.
     * @return Bool type.
     */
    bool operator<(Vertex & vertex) const;

    /** @brief Represents the id of the vertex.
     *
     * @return Id of the vertex.
     */
    int getId() const;

    /** @brief Represents the station.
     *
     * @return Station.
     */
    std::shared_ptr<Station> getStation() const;

    /** @brief Represents the adjacent edges.
     *
     * @return Edges.
     */
    std::vector<Edge *> getAdj() const;

    /** @brief Represents if the vertex was visited or not.
     *
     * @return True if the vext
     */
    bool isVisited() const;

    /** @brief Represents the distance.
     *
     * @return Distance.
     */
    double getDist() const;

    /** @brief Represents the path.
      *
      * @return Edge.
      */
    Edge *getPath() const;

    /** @brief Represents the incoming edges.
     *
     * @return Edges.
     */
    std::vector<Edge *> getIncoming() const;

    /** @brief Updates if the vertex was visited or not.
     *
     * @param visited of bool type.
     * @return Void.
     */
    void setVisited(bool visited);

    /** @brief Updates the vertex distance.
     *
     * @param dist of double type.
     * @return Void.
     */
    void setDist(double dist);

    /** @brief Updates the vertex path.
     *
     * @param dist of Edge* type.
     * @return Void.
     */
    void setPath(Edge *path);

    /** @brief Adds an outgoing edge to a vertex,
     * with a given destination vertex and edge weight.
     *
     * @param dest of Vertex* type.
     * @param w of double type.
     * @param service of ServiceType type.
     * @return Edge.
     */
    Edge * addEdge(Vertex *dest, double w, ServiceType service);

    /** @brief Removes an outgoing edge from a vertex.
     *
     * @param destID of int type.
     * @return true if successful, and false if such edge does not exist.
     */
    bool removeEdge(int destID);

    //! @brief Friend declaration.
    friend class MutablePriorityQueue<Vertex>;

protected:

    //! @brief Holds the id of the vertex.
    int id;

    //! @brief Holds the station pointer.
    std::shared_ptr<Station> station;

    //! @brief Holds the adjacent edges.
    std::vector<Edge *> adj;

    //! @brief Holds the visited truth.
    bool visited = false;

    //! @brief Holds the distance of the vertex.
    double dist = 0;

    //! @brief Holds the path of the vertex.
    Edge *path = nullptr;

    //! @brief Holds the incoming edges.
    std::vector<Edge *> incoming;

    //! @brief Holds the index of the queue.
    int queueIndex = 0;
};

/********************** Edge  ****************************/

/** @brief Edge class to represent the edge from the graph.
 *
 */
class Edge {

public:

    /** @brief Creates a new Edge.
     *
     * @param orig of Vertex* type.
     * @param dest of Vertex* type.
     * @param w of double type.
     * @param service of ServiceType type.
     */
    Edge(Vertex *orig, Vertex *dest, double w, ServiceType service);

    /** @brief Gets the destination of the edge.
     *
     * @return Destination vertex.
     */
    Vertex * getDest() const;

    /** @brief Gets the weight of the edge.
     *
     * @return Weight.
     */
    double getWeight() const;

    /** @brief Gets the original vertex.
     *
     * @return Original vertex.
     */
    Vertex * getOrig() const;

    /** @brief Gets the flow of the edge.
     *
     * @return Flow.
     */
    double getFlow() const;

    /**@brief Gets the minimum residual capacity
     *
     * @return maxResidual
     */
    double getMinResidual();

    /** @brief Gets the destination of the edge.
     *
     * @return Destination vertex.
     */
    ServiceType getService() const;

    /** @brief Sets the reverse edge.
     *
     * @param reverse of Edge* type.
     * @return Void.
     */
    void setReverse(Edge *reverse);

    /** @brief Updates the flow of the edge.
     *
     * @param flow of double type.
     * @return Void.
     */
    void setFlow(double flow);

    /** @brief Updates the minimum residual.
     *
     * @param int of int type.
     * @return Void.
     */
    void setMinResidual(int minResidual);

protected:

    //! @brief Holds the destination of the edge.
    Vertex * dest;

    //! @brief Holds the weight of the edge.
    double weight;

    //! @brief Holds the service of the edge.
    ServiceType service;

    //! @brief Holds the original vertex.
    Vertex *orig;

    //! @brief Holds the reverse edge.
    Edge *reverse = nullptr;

    //! @brief Holds the minimum residual capacity along the path.
    int maxResidual;

    //! @brief Holds the flow of the edge.
    double flow;
};

#endif /* DA_TP_CLASSES_VERTEX_EDGE */