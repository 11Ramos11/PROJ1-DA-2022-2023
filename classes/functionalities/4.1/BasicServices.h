/** @file BasicServices.h
 *  @brief Contains the BasicServices class declaration.
 *  @author -
 *  @bug No known bugs.
 */

#ifndef PROJ1_DA_2022_2023_BASICSERVICES_H
#define PROJ1_DA_2022_2023_BASICSERVICES_H

#include "../../../data-structure/VertexEdge.h"
#include "../../../data-structure/Graph.h"
#include "../../source-reader/FileReader.h"
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

    /** @brief Checks all paths between source and target in the residual graph.
     *
     * @param s of Vertex* type.
     * @param t of Vertex* type.
     * @return True if there is a path or false if otherwise.
     */
    bool path(Vertex * s, Vertex * t);

    /** @brief Represents the edmondsKarp algorithm.
     *
     * It uses path, find_Bottleneck and augmentPath methods.
     *
     * @param source of int type.
     * @param target of int type.
     * @return Void.
     */
    void edmondsKarp(int source, int target);

    /** @brief Checks if there is a path between two stations.
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

    /** @brief Calculates the maximum number of trains between two stations.
     *
     * It uses edmondsKarp algorithm.
     *
     * @param source of int type.
     * @param target of int type.
     * @return The maximum flow.
     */
    double maxFlow(int source, int target);

    /** @brief Returns the all pairs of stations that require the
     * most amount of trains when taking full advantage of the network.
     *
     * @return Pair of stations.
     */
    std::vector<std::pair<Vertex*, Vertex*>> optimalPairs();

    /** @brief Calculates the top k municipalities or districts, regarding their transportation needs.
     *
     * The category can be a municipality (if byMunicipality is true) or a district (if byMunicipality is false).
     * Creates a source node that is linked to all nodes that do not belong to the destination municipality or district
     * and creates a sink node that is linked to all nodes that belong to the destination municipality or district.
     * It uses the maxFlow method.
     *
     * @param byMunicipality of bool type.
     * @param k of int type.
     * @return The top municipalities or districts names.
     */
    std::vector<std::string> getMunicipalitiesOrDistricts(bool byMunicipality, int k);

    /** @brief Calculates the maximum number of trains that can simultaneously arrive at specific station.
     *
     * Creates a source node that is linked to all nodes except the source and sink ones.
     * It uses maxFlow method.
     *
     * @param target of int type.
     * @return Number of trains.
     */
    double max_trains_target(int target);

    /** @brief Find the minimum flow to augment in found path.
     *
     * @param s of Vertex* type.
     * @param t of Vertex* type.
     * @return The minimum flow.
     */
    double find_Bottleneck(Vertex *s, Vertex * t);

    /** @brief Augments the flow by "bottleneck" units in found path.
     *
     * @param s of Vertex* type.
     * @param t of Vertex* type.
     * @param bottleneck of double type.
     * @return Void.
     */
    void augmentPath(Vertex * s, Vertex * t, double bottleneck);
};

#endif //PROJ1_DA_2022_2023_BASICSERVICES_H
