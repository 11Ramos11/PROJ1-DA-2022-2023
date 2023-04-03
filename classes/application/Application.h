/** @file Application.h
 *  @brief Contains the Application class declaration.
 *  @author -
 *  @bug No known bugs.
 */

#ifndef PROJ1_DA_2022_2023_APPLICATION_H
#define PROJ1_DA_2022_2023_APPLICATION_H

#include <unordered_map>
#include <string>
#include <stack>
#include "../source-reader/SourceReader.h"
#include "../functionalities/4.1/BasicServices.h"

enum MenuState{
    WELCOMEMENU,
    INITIAL_MENU,
    BASICSERVICESMENU,
    COSTMENU,
    FAILURESMENU
};

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

    int choice;

    std::stack<MenuState> menuState;

public:

    Application();

    /** @brief Starts the project.
     *
     * @return Void.
     */
    void start();

    void getMenu();
    void welcomeMenu();
    void failuresMenu();
    void costOptimizationMenu();
    void basicServicesMenu();
    void initialMenu();
};

#endif //PROJ1_DA_2022_2023_APPLICATION_H
