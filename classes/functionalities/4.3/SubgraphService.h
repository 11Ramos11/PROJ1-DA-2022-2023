/** @file SubgraphService.h
 *  @brief Contains the SubgraphService class declaration.
 *  @author -
 *  @bug No known bugs.
 */

#ifndef PROJ1_DA_2022_2023_SUBGRAPHSERVICE_H
#define PROJ1_DA_2022_2023_SUBGRAPHSERVICE_H

#include "../../../data-structure/Graph.h"

/** @brief SubgraphService class to represent all Reliability and Sensitivity to Line Failures of a network
 * and all implementations that uses a graph directly.
 *
 */
class SubgraphService {

    //! @brief Holds the original graph.
    Graph* originalGraph;

    //! @brief Holds the subgraph.
    Graph subGraph;

public:

    /** @brief Creates a new SubgraphService for the respective graph.
     *
     * @param graph of Graph* type.
     */
    SubgraphService(Graph* graph);

    int getID(std::string stationName);

    /** @brief Resets the subgraph to the original graph.
     *
     * Time Complexity: O(1).
     *
     * @return Void.
     */
    void resetSubgraph();

    /** @brief Deletes the specified station from the subgraph.
     *
     * Time Complexity: O(|V + E|), in which V is the number of Vertexes and E is the number of Edges, in the graph.
     *
     * @param id of int type.
     * @return Void.
     */
    void deleteStation(int id);

    /** @brief Deletes the specified edge from the subgraph.
     *
     * Time Complexity: O(E), in which E is the number of Edges, in the graph.
     *
     * @param orig of int type.
     * @param dest of int type.
     * @return Void.
     */
    void deleteEdge(int orig, int dest);

    /** @brief Deletes the all edges with a certain service from the subgraph.
     *
     * Time Complexity: O(|V + E|), in which V is the number of Vertexes and E is the number of Edges, in the graph.
     *
     * @param serviceType of ServiceType type.
     * @return Void.
     */
    void deleteService(ServiceType serviceType);

    /** @brief Calculates the maximum number of trains that can simultaneously travel between
     * two specific stations in a network of reduced connectivity.
     *
     * Time Complexity: O(|V * E^2|), in which V is the number of Vertexes and E is the number of Edges, in the graph.
     *
     * @param source of int type.
     * @param target of int type.
     * @return The maximum number of trains.
     */
    int maxFlow(int source, int target);

    /** @brief Provides the top-k stations that are the most affected by the specified segment failure.
     *
     * Time Complexity: O(|V^3 * E^2|), in which V is the number of Vertexes and E is the number of Edges, in the graph.
     *
     * @param source of type int.
     * @param target of type int.
     * @param k of type int.
     * @return The most affected stations.
     */
    std::vector<Vertex *> mostAffectedStations(int source, int target, int k);
};

#endif //PROJ1_DA_2022_2023_SUBGRAPHSERVICE_H
