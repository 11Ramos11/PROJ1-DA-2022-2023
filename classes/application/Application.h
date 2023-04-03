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

    //! @brief Creates the initial menu options.
    enum States{
        WELCOME_MENU,
        INITIAL_MENU,
        SERVICES_MENU,
        COST_MENU,
        FAILURE_MENU
    };

    //! @brief Initialization of the user choice.
    int choice;

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
};

#endif //PROJ1_DA_2022_2023_APPLICATION_H
