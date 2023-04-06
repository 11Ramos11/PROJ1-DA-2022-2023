/** @file FileReader.h
 *  @brief Contains the FileReader class declaration.
 *  @author João Ramos e Matilde Simões
 *  @bug No known bugs.
 */

#ifndef PROJ1_DA_2022_2023_FILEREADER_H
#define PROJ1_DA_2022_2023_FILEREADER_H

#include <map>
#include <unordered_map>
#include "../station/Station.h"
#include "../../data-structure/Graph.h"

/** @brief FileReader class to deal with data set files.
 *
 */
class FileReader {

    //! @brief Holds the default stations file.
    std::string stationsFileName = "../resources/stations.csv";

    //! @brief Holds the default network file.
    std::string networkFileName = "../resources/network.csv";

    /** @brief Reads stations input file and stores them accordingly.
     *
     *  Reads the file specified by the attribute stationsFileName and, for each line,
     *  it reads a station name, its district, municipality, township and
     *  line name.
     *  If the station corresponds to a new station,
     *  it creates a new station object and adds it to the unordered_map of stations.
     *
     *  @param stations of std::unordered_map<std::string, std::shared_ptr<Station>> type, by reference.
     *  @param railwayNetwork of Graph type, by reference.
     *  @return 0 on success, -1 if file not found
     */
    int readStations(std::unordered_map<std::string, std::shared_ptr<Station>> &stations, Graph &railwayNetwork);

    /** @brief Reads network input file and stores them accordingly.
     *
     *  Reads the file specified by the attribute networkFileName and, for each line,
     *  it reads the name of two stations, its capacity and service.
     *
     * @param stations of std::unordered_map<std::string, std::shared_ptr<Station>> type, by reference.
     * @param railwayNetwork of Graph type, by reference.
     * @return 0 on success, -1 if file not found
     */
    int readNetwork(std::unordered_map<std::string, std::shared_ptr<Station>> &stations, Graph &railwayNetwork);

public:

    /**@brief Creates a new FileReader.
     *
     */
    FileReader();

    /** @brief Stores all the information of the database.
     *
     * @param stations of std::unordered_map<std::string, std::shared_ptr<Station>> type, by reference.
     * @param railwayNetwork of Graph type, by reference.
     * @return 0 on success, -1 if one or mores files not found
     */
    int read(std::unordered_map<std::string, std::shared_ptr<Station>> &stations, Graph &railwayNetwork);

    /** @brief resets attributes stationsFileName and networkFileName to the default files paths
     */
    void reset();

    /** @brief Sets both station file and network file
     *
     * @param stationsFileName, path for the stations file
     * @param networkFileName, path for the network file
     */
    void setFiles(std::string stationsFileName, std::string networkFileName);
};

#endif //PROJ1_DA_2022_2023_FILEREADER_H
