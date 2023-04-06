/** @file BasicServices.h
 *  @brief Contains the BasicServices class declaration.
 *  @author João Ramos e Matilde Simões
 *  @bug No known bugs.
 */

#ifndef PROJ1_DA_2022_2023_BASICSERVICES_H
#define PROJ1_DA_2022_2023_BASICSERVICES_H

#include "../../../data-structure/VertexEdge.h"
#include "../../../data-structure/Graph.h"
#include "../../file-reader/FileReader.h"
#include "../../station/Station.h"

#include <set>
#include <string>

/** @brief BasicServices class to represent all Basic Service Metrics of a network
 * and all implementations that uses a graph directly.
 *
 */
class BasicServices {

private:

    //! @brief Holds the graph.
    Graph* graph;

protected:

    /** @brief Checks if there is still an augmenting path between source and target in the residual graph.
     *
     * Time Complexity: O(|V + E|), in which V is the number of Vertexes and E is the number of Edges, in the graph.
     *
     * @param s of Vertex* type.
     * @param t of Vertex* type.
     * @return True if there is a path, false if otherwise.
     */
    bool path(Vertex * s, Vertex * t);

    /** @brief Runs the edmondsKarp algorithm.
     *
     * Time Complexity: O(|V * E^2|), in which V is the number of Vertexes and E is the number of Edges, in the graph.
     *
     * It runs path() to find an augmenting path.\n
     * If it finds one, it uses findBottleneck() to get the maximum flow that can be used in that path
     * and uses augmentPath() to then update the residual graph.\n
     * The function ends when path() is not longer able to find an augmenting path.
     *
     * @param source of int type.
     * @param target of int type.
     * @return Void.
     */
    void edmondsKarp(int source, int target);

    /** @brief Checks if there is a path between two stations.
     *
     * Time Complexity: O(|V + E|), in which V is the number of Vertexes and E is the number of Edges, in the graph.
     *
     * @param s of Vertex* type.
     * @param t of Vertex* type.
     * @return True if there is a path or false if otherwise.
     */
    bool existsPath(Vertex * s, Vertex * t);

public :

    /** Creates a new BasicServices for the respective graph.
     *
     * @param graph of Graph* type.
     */
    BasicServices(Graph* graph);

    /** @brief Calculates the maximum number of trains that can travel between two stations, simultaneously.
     *
     * It uses edmondsKarp().\n
     * Then it sums the flow of all the source outgoing edges, to determine the maximum flow.
     *
     * Time Complexity: O(|V * E^2|), in which V is the number of Vertexes and E is the number of Edges, in the graph.
     *
     * @param source of int type.
     * @param target of int type.
     * @return The maximum flow.
     */
    double maxFlow(int source, int target);

    /** @brief Finds the most optimal pairs of stations, which require the
     * most amount of trains when taking full advantage of the existing network capacity
     *
     * Checks for all pairs of stations in the graph, if they have the highest maximum flow.
     *
     * Time Complexity: O(|V^3 * E^2|), in which V is the number of Vertexes and E is the number of Edges, in the graph.
     *
     * @return vector with the pair or pairs of stations, that have the highest maximum flow in the graph.
     */
    std::vector<std::pair<Vertex*, Vertex*>> optimalPairs();

    /** @brief Calculates the top k municipalities or districts, regarding their transportation needs.
     *
     * The category can be a municipality (if byMunicipality is true) or a district (if byMunicipality is false).
     * Creates a source node that is linked to all nodes that do not belong to the destination municipality or district
     * and creates a sink node that is linked to all nodes that belong to the destination municipality or district.
     * It uses the maxFlow method.
     *
     * Time Complexity: O(|V^2 * E^2|), in which V is the number of Vertexes and E is the number of Edges, in the graph.
     *
     * @param byMunicipality of bool type.
     * @param k of int type.
     * @return The top municipalities or districts names.
     */
    std::vector<std::string> topMunicipalitiesOrDistricts(bool byMunicipality, int k);

    /** @brief Calculates the maximum number of trains that can simultaneously arrive at specific station.
     *
     * Creates a source node that is linked to all nodes except the source and sink ones.
     * It uses maxFlow method.
     *
     * Time Complexity: O(|V * E^2|), in which V is the number of Vertexes and E is the number of Edges, in the graph.
     *
     * @param target of int type.
     * @return Number of trains.
     */
    double max_trains_target(int target);

    /** @brief Find the minimum flow to augment in found path.
     *
     * Time Complexity: O(|V|), in which V is the number of Vertexes, in the graph.
     *
     * @param s of Vertex* type.
     * @param t of Vertex* type.
     * @return The minimum flow.
     */
    double findBottleneck(Vertex *s, Vertex * t);

    /** @brief Augments the flow by "bottleneck" units in found path.
     *
     * Time Complexity: O(|V|), in which V is the number of Vertexes, in the graph.
     *
     * @param s of Vertex* type.
     * @param t of Vertex* type.
     * @param bottleneck of double type.
     * @return Void.
     */
    void augmentPath(Vertex * s, Vertex * t, double bottleneck);
};

#endif //PROJ1_DA_2022_2023_BASICSERVICES_H
