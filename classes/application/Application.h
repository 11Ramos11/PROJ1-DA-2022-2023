/** @file Application.h
 *  @brief Contains the Application class declaration.
 *  @author -
 *  @bug No known bugs.
 */

#ifndef PROJ1_DA_2022_2023_APPLICATION_H
#define PROJ1_DA_2022_2023_APPLICATION_H

#include <unordered_map>
#include <string>
#include "../source-reader/SourceReader.h"
#include "../functionalities/4.1/BasicServices.h"
#include "../functionalities/4.2/CostOptimizer.h"

/** @brief Initializes and manages all the components of the application.
 *
 * Intended to be instanced once.
 * Manages the interaction between the user and the application.
 */
class Application {

    //! @brief Initialization of the stations.
    std::unordered_map<std::string, std::shared_ptr<Station>> stations;

    //! @brief Initialization of the graph.
    Graph railwayNetwork;

    //! @brief Initialization of the basicServices.
    BasicServices basicServices = BasicServices(&railwayNetwork);
    CostOptimizer costOptimizer = CostOptimizer(&railwayNetwork);

public:

    /** @brief Starts the project.
     *
     * @return Void.
     */
    void start();
};

#endif //PROJ1_DA_2022_2023_APPLICATION_H
