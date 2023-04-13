/** @file Application.h
 *  @brief Contains the Application class declaration.
 *  @author João Ramos e Matilde Simões
 *  @bug No known bugs.
 */

#ifndef PROJ1_DA_2022_2023_APPLICATION_H
#define PROJ1_DA_2022_2023_APPLICATION_H

#include <unordered_map>
#include <string>
#include <stack>
#include "../file-reader/FileReader.h"
#include "../functionalities/4.1/BasicServices.h"
#include "../functionalities/4.2/CostOptimizer.h"
#include "../functionalities/4.3/SubgraphService.h"


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

    //! @brief Initialization of the fileReader.
    FileReader fileReader;

    //! @brief Initialization of the basicServices.
    BasicServices basicServices = BasicServices(&railwayNetwork);

    //! @brief Initialization of the costOptimizer.
    CostOptimizer costOptimizer = CostOptimizer(&railwayNetwork);

    //! @brief Initialization of the subgraphService.
    SubgraphService subgraphService = SubgraphService(&railwayNetwork);

    //! @brief Creates the initial menu options.
    enum States{
        WELCOME_MENU,
        READ_MENU,
        INITIAL_MENU,
        SERVICES_MENU,
        COST_MENU,
        FAILURE_MENU,
        GRAPHS_MENU
    };

    //! @brief Initialization of the user choice.
    int choice;

    //! @brief Initialization of the string type user choice.
    std::string stringChoice;

    //! @brief Initialization of the stack that contains the application states.
    std::stack<States> state;

public:

    /** @brief Starts the project.
     *
     * @return Void.
     */
    void start();

    /** @brief Controls the application states.
     *
     * @return Void.
     */
    void getMenu();

    /** @brief Displays the welcome menu.
     *
     * @return Void.
     */
    void welcomeMenu();

    /** @brief Displays the read files menu.
     *
     * @return Void.
     */
    void readMenu();

    /** @brief Displays the initial menu.
     *
     * @return Void.
     */
    void initialMenu();

    /** @brief Displays the Basic Service Metrics menu and the information that the user chooses to know.
     *
     * @return Void.
     */
    void servicesMenu();

    /** @brief Displays the Operation Cost Optimization menu and the information that the user chooses to know.
     *
     * @return Void.
     */
    void costMenu();

    /** @brief Displays the Reliability and Sensitivity to Line Failures menu and the information
     * that the user chooses to know.
     *
     * @return Void.
     */
    void failureMenu();

    /** @brief Displays the Reliability and Sensitivity to Line Failures menu and the information
     * that the user chooses to know.
     *
     * @return Void.
     */
    void graphsMenu();
};

#endif //PROJ1_DA_2022_2023_APPLICATION_H
