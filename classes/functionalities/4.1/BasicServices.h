/** @file BasicServices.h
 *  @brief Contains the BasicServices class declaration.
 *  @author -
 *  @bug No known bugs.
 */

#ifndef PROJ1_DA_2022_2023_BASICSERVICES_H
#define PROJ1_DA_2022_2023_BASICSERVICES_H

#include "../../../data-structure/VertexEdge.h"
#include "../../../data-structure/Graph.h"
#include "../../source-reader/SourceReader.h"
#include "../../station/Station.h"

#include <set>
#include <string>

/** @brief BasicServices class to represent all basic services of a network
 * and all implementations that uses a graph directly.
 *
 */
class BasicServices {

private:

    //! @brief Holds the graph.
    Graph* graph;

public :

    /** Creates a new BasicServices with the respective graph.
     *
     * @param graph of Graph* type.
     */
    BasicServices(Graph* graph);

    /** @brief Checks all paths between source and target in the residual graph.
     *
     * @param s of Vertex* type.
     * @param t of Vertex* type.
     * @return True if there is a path or false if otherwise.
     */
    bool path(Vertex * s, Vertex * t);

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
    void augmentsPath(Vertex * s, Vertex * t, double bottleneck);

    /** @brief Represents the edmondsKarp algorithm.
     *
     * It uses path, find_Bottleneck and augmentsPath methods.
     *
     * @param source of int type.
     * @param target of int type.
     * @return Void.
     */
    void edmondsKarp(int source, int target);

    /** @brief Calculates the maximum number of trains between two stations.
     *
     * It uses edmondsKarp algorithm.
     *
     * @param source of int type.
     * @param target of int type.
     * @return The maximum flow.
     */
    double maxFlow(int source, int target);

    /** @brief Checks if there is a path between two stations.
     *
     * @param s of Vertex* type.
     * @param t of Vertex* type.
     * @return True if there is a path or false if otherwise.
     */
    bool exitsPath(Vertex * s, Vertex * t);
    std::vector<std::pair<Vertex*, Vertex*>> stationspair();

    std::vector<std::string> municipalities(int k);
    std::vector<std::string> districts(int k);

    double max_trains_target(int target);


};

#endif //PROJ1_DA_2022_2023_BASICSERVICES_H
