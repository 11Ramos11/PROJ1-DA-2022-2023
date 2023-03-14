//
// Created by Matilde on 14/03/2023.
//

#ifndef PROJ1_DA_2022_2023_BASICSERVICES_H
#define PROJ1_DA_2022_2023_BASICSERVICES_H

#include "../../../data-structure/VertexEdge.h"
#include "../../../data-structure/Graph.h"
#include "../../source-reader/SourceReader.h"
#include "../../station/Station.h"


class BasicServices {

private:

    Graph* graph;

public :

    BasicServices(Graph* graph);

    bool path(Vertex * s, Vertex * t);
    double find_Bottleneck(Vertex *s, Vertex * t);
    void augmentsPath(Vertex * s, Vertex * t, double bottleneck);
    void edmondsKarp(int source, int target);

    double maxFlow(int source, int target);
};


#endif //PROJ1_DA_2022_2023_BASICSERVICES_H
