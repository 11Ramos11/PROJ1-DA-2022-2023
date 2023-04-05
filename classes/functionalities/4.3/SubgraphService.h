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
    Graph* subGraph;

public:

    /** @brief Creates a new SubgraphService for the respective graph.
     *
     * @param graph of Graph* type.
     */
    SubgraphService(Graph* graph);

    /** @brief
     *
     * @return Void.
     */
    void resetSubgraph();

    void deleteStation(int id);

    void deleteEdge(int orig, int dest);

    void deleteService(ServiceType serviceType);

    int maxFlow(int source, int target);

    std::vector<Vertex *> mostAffectedStations(int source, int target, int k);
};

#endif //PROJ1_DA_2022_2023_SUBGRAPHSERVICE_H
