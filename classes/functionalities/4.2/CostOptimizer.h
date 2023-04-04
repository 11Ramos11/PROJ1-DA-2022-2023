//
// Created by Ramos on 4/2/2023.
//

#ifndef PROJ1_DA_2022_2023_COSTOPTIMIZER_H
#define PROJ1_DA_2022_2023_COSTOPTIMIZER_H


#include "../../../data-structure/Graph.h"

class CostOptimizer {

private:

    //! @brief Holds the graph.
    Graph* graph;

public:

    /** @brief Creates a new CostOptimizer for the respective graph.
     *
     * @param graph of Graph* type.
     */
    CostOptimizer(Graph* graph);

    int MaxTrainsWithMinCost(int source, int target);
};


#endif //PROJ1_DA_2022_2023_COSTOPTIMIZER_H
