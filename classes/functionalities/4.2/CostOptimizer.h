/** @file CostOptimizer.h
 *  @brief Contains the CostOptimizer class declaration.
 *  @author -
 *  @bug No known bugs.
 */

#ifndef PROJ1_DA_2022_2023_COSTOPTIMIZER_H
#define PROJ1_DA_2022_2023_COSTOPTIMIZER_H

#include "../../../data-structure/Graph.h"

/** @brief CostOptimizer class to represent all Operation Cost Optimization of a network
 * and all implementations that uses a graph directly.
 *
 */
class CostOptimizer {

private:

    //! @brief Holds the graph.
    Graph *graph;

public:

    /** @brief Creates a new CostOptimizer for the respective graph.
     *
     * @param graph of Graph* type.
     */
    CostOptimizer(Graph *graph);

    /** @brief Checks if there is a path between two stations.
     *
     * Time Complexity: O(|V + E| * log(V)), in which V is the number of Vertexes and E is the number of Edges, in the graph.
     *
     * @param s of type Vertex*.
     * @param t of type Vertex*.
     * @return True if there is a path, false if otherwise.
     */
    bool dijkstra(Vertex *s, Vertex *t);

    /** @brief Calculates the maximum amount of trains that can simultaneously travel between
     * two specific stations with minimum cost for the company.
     *
     * Time Complexity: O(|V + E| * log(V)), in which V is the number of Vertexes and E is the number of Edges, in the graph.
     *
     * @param source of int type.
     * @param target of int type.
     * @return Pair of the maximum flow and the minimum cut.
     */
    std::pair<int, int> MaxTrainsWithMinCost(int source, int target);
};

#endif //PROJ1_DA_2022_2023_COSTOPTIMIZER_H
