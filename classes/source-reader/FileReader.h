/** @file FileReader.h
 *  @brief Contains the FileReader class declaration.
 *  @author -
 *  @bug No known bugs.
 */

#ifndef PROJ1_DA_2022_2023_FILEREADER_H
#define PROJ1_DA_2022_2023_FILEREADER_H

#include <map>
#include <unordered_map>
#include "../station/Station.h"
#include "../../data-structure/Graph.h"

class FileReader {

    //! @brief Holds the default stations file.
    std::string stationsFileName = "../resources/stations.csv";

    //! @brief Holds the default network file.
    std::string networkFileName = "../resources/network.csv";

    /** @brief Reads stations input file and stores them accordingly.
     *
     *  Reads the file "stations.csv" and for each line
     *  it reads a station name, its district, municipality, township and
     *  line name.
     *  If the station corresponds to a new station,
     *  it creates a new station object and adds it to the unordered_map of stations.
     *
     *  @param stations of std::unordered_map<std::string, std::shared_ptr<Station>> type, by reference.
     *  @param railwayNetwork of Graph type, by reference.
     *  @return Void.
     */
    void readStations(std::unordered_map<std::string, std::shared_ptr<Station>> &stations, Graph &railwayNetwork);

    /** @brief Reads network input file and stores them accordingly.
     *
     *  Reads the file "network.csv" and for each line
     *  it reads the name of two stations, its capacity and service.
     *
     * @param stations of std::unordered_map<std::string, std::shared_ptr<Station>> type, by reference.
     * @param railwayNetwork of Graph type, by reference.
     * @return Void.
     */
    void readNetwork(std::unordered_map<std::string, std::shared_ptr<Station>> &stations, Graph &railwayNetwork);

public:

    /**@brief Creates a new FileReader.
     *
     */
    FileReader();

    /** @brief Creates a new FileReader.
     *
     * @param stationsFileName of std::string type.
     * @param networkFileName of std::string type.
     */
    FileReader(std::string stationsFileName, std::string networkFileName);

    /** @brief Stores all the information of the database.
     *
     * @param stations of std::unordered_map<std::string, std::shared_ptr<Station>> type, by reference.
     * @param railwayNetwork of Graph type, by reference.
     * @return Void.
     */
    void read(std::unordered_map<std::string, std::shared_ptr<Station>> &stations, Graph &railwayNetwork);
};

#endif //PROJ1_DA_2022_2023_FILEREADER_H
